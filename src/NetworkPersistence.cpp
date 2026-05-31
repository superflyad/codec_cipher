#include "NetworkPersistence.h"

#include <fstream>
#include <sstream>
#include <stdexcept>

namespace {

std::string escapeField(const std::string& value) {
    std::string escaped;
    for (const char character : value) {
        if (character == '\\' || character == '|') {
            escaped.push_back('\\');
        }
        escaped.push_back(character);
    }
    return escaped;
}

std::vector<std::string> splitFields(const std::string& line) {
    std::vector<std::string> fields;
    std::string current;
    bool escaping = false;

    for (const char character : line) {
        if (escaping) {
            current.push_back(character);
            escaping = false;
            continue;
        }

        if (character == '\\') {
            escaping = true;
            continue;
        }

        if (character == '|') {
            fields.push_back(current);
            current.clear();
            continue;
        }

        current.push_back(character);
    }

    fields.push_back(current);
    return fields;
}

std::string joinValues(const std::vector<double>& values) {
    std::ostringstream stream;
    for (std::size_t index = 0; index < values.size(); ++index) {
        if (index > 0) {
            stream << ",";
        }
        stream << values[index];
    }
    return stream.str();
}

std::vector<double> parseValues(const std::string& valueText) {
    std::vector<double> values;
    if (valueText.empty()) {
        return values;
    }

    std::istringstream stream(valueText);
    std::string token;
    while (std::getline(stream, token, ',')) {
        values.push_back(std::stod(token));
    }
    return values;
}

std::string readFile(const std::filesystem::path& filePath) {
    std::ifstream file(filePath);
    if (!file) {
        throw std::runtime_error("Unable to open file for reading: " + filePath.string());
    }

    std::ostringstream stream;
    stream << file.rdbuf();
    return stream.str();
}

void writeFile(const std::filesystem::path& filePath, const std::string& content) {
    std::ofstream file(filePath);
    if (!file) {
        throw std::runtime_error("Unable to open file for writing: " + filePath.string());
    }

    file << content;
}

std::vector<std::string> linesOf(const std::string& content) {
    std::vector<std::string> lines;
    std::istringstream stream(content);
    std::string line;
    while (std::getline(stream, line)) {
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }
        lines.push_back(line);
    }
    return lines;
}

} // namespace

std::string NetworkPersistence::serializeNetwork(const Network& network) {
    std::ostringstream stream;
    stream << "CCNET1\n";

    for (const auto& node : network.getNodes()) {
        stream << "NODE|" << escapeField(node.getId()) << "|" << escapeField(node.getLabel()) << "|"
               << joinValues(node.getValues()) << "\n";
    }

    for (const auto& edge : network.getEdges()) {
        stream << "EDGE|" << escapeField(edge.getId()) << "|" << escapeField(edge.getFromNodeId()) << "|"
               << escapeField(edge.getToNodeId()) << "|" << escapeField(edge.getRelationship()) << "\n";
    }

    return stream.str();
}

Network NetworkPersistence::deserializeNetwork(const std::string& content) {
    const auto lines = linesOf(content);
    if (lines.empty() || lines[0] != "CCNET1") {
        throw std::runtime_error("Invalid network serialization header.");
    }

    Network network;
    std::vector<std::vector<std::string>> edgeFields;

    for (std::size_t index = 1; index < lines.size(); ++index) {
        if (lines[index].empty()) {
            continue;
        }

        const auto fields = splitFields(lines[index]);
        if (fields[0] == "NODE" && fields.size() == 4) {
            network.addNode(fields[1], fields[2], parseValues(fields[3]));
        } else if (fields[0] == "EDGE" && fields.size() == 5) {
            edgeFields.push_back(fields);
        } else {
            throw std::runtime_error("Invalid network serialization line: " + lines[index]);
        }
    }

    for (const auto& fields : edgeFields) {
        network.addEdge(fields[1], fields[2], fields[3], fields[4]);
    }

    return network;
}

std::string NetworkPersistence::serializeSnapshot(const NetworkSnapshot& snapshot) {
    std::ostringstream stream;
    stream << "CCSNAP1\n";
    stream << "RUN|" << snapshot.runNumber << "|" << snapshot.seed << "|" << escapeField(snapshot.label) << "\n";
    stream << "BEGIN_NETWORK\n" << serializeNetwork(snapshot.network) << "END_NETWORK\n";
    stream << "BEGIN_CUBES\n";

    for (const auto& entry : snapshot.nestedCubes.inspectHierarchy()) {
        stream << "CUBE|" << escapeField(entry.cubeId) << "|"
               << (entry.parentCubeId.has_value() ? escapeField(entry.parentCubeId.value()) : "") << "\n";
    }

    stream << "END_CUBES\n";
    return stream.str();
}

NetworkSnapshot NetworkPersistence::deserializeSnapshot(const std::string& content) {
    const auto lines = linesOf(content);
    if (lines.size() < 2 || lines[0] != "CCSNAP1") {
        throw std::runtime_error("Invalid snapshot serialization header.");
    }

    const auto runFields = splitFields(lines[1]);
    if (runFields.size() != 4 || runFields[0] != "RUN") {
        throw std::runtime_error("Invalid snapshot run header.");
    }

    std::ostringstream networkContent;
    NestedCubeContainer nestedCubes;
    bool readingNetwork = false;
    bool readingCubes = false;
    std::vector<std::vector<std::string>> childCubeFields;

    for (std::size_t index = 2; index < lines.size(); ++index) {
        const std::string& line = lines[index];
        if (line == "BEGIN_NETWORK") {
            readingNetwork = true;
            continue;
        }
        if (line == "END_NETWORK") {
            readingNetwork = false;
            continue;
        }
        if (line == "BEGIN_CUBES") {
            readingCubes = true;
            continue;
        }
        if (line == "END_CUBES") {
            readingCubes = false;
            continue;
        }

        if (readingNetwork) {
            networkContent << line << "\n";
        } else if (readingCubes && !line.empty()) {
            const auto fields = splitFields(line);
            if (fields.size() != 3 || fields[0] != "CUBE") {
                throw std::runtime_error("Invalid cube serialization line: " + line);
            }

            if (fields[2].empty()) {
                nestedCubes.addRootCube(fields[1]);
            } else {
                childCubeFields.push_back(fields);
            }
        }
    }

    for (const auto& fields : childCubeFields) {
        nestedCubes.addChildCube(fields[2], fields[1]);
    }

    const std::size_t runNumber = static_cast<std::size_t>(std::stoull(runFields[1]));
    const std::uint32_t seed = static_cast<std::uint32_t>(std::stoul(runFields[2]));
    Network network = deserializeNetwork(networkContent.str());
    return NetworkSnapshot{runNumber, seed, runFields[3], network, nestedCubes};
}

std::string NetworkPersistence::serializeRunSequence(const std::vector<Run>& runs) {
    std::ostringstream stream;
    stream << "CCRUNS1\n";

    for (const auto& run : runs) {
        stream << "BEGIN_SNAPSHOT\n";
        stream << serializeSnapshot(run.snapshot);
        stream << "END_SNAPSHOT\n";
    }

    return stream.str();
}

ReplayEngine NetworkPersistence::deserializeRunSequenceToReplay(const std::string& content) {
    const auto lines = linesOf(content);
    if (lines.empty() || lines[0] != "CCRUNS1") {
        throw std::runtime_error("Invalid run sequence serialization header.");
    }

    std::vector<Run> runs;
    bool readingSnapshot = false;
    std::ostringstream snapshotContent;

    for (std::size_t index = 1; index < lines.size(); ++index) {
        if (lines[index] == "BEGIN_SNAPSHOT") {
            readingSnapshot = true;
            snapshotContent.str("");
            snapshotContent.clear();
            continue;
        }

        if (lines[index] == "END_SNAPSHOT") {
            readingSnapshot = false;
            NetworkSnapshot snapshot = deserializeSnapshot(snapshotContent.str());
            runs.push_back(Run{snapshot.runNumber, snapshot.seed, snapshot.label, snapshot});
            continue;
        }

        if (readingSnapshot) {
            snapshotContent << lines[index] << "\n";
        }
    }

    return ReplayEngine(runs);
}

void NetworkPersistence::saveNetwork(const Network& network, const std::filesystem::path& filePath) {
    writeFile(filePath, serializeNetwork(network));
}

Network NetworkPersistence::loadNetwork(const std::filesystem::path& filePath) {
    return deserializeNetwork(readFile(filePath));
}

void NetworkPersistence::saveSnapshot(const NetworkSnapshot& snapshot, const std::filesystem::path& filePath) {
    writeFile(filePath, serializeSnapshot(snapshot));
}

NetworkSnapshot NetworkPersistence::loadSnapshot(const std::filesystem::path& filePath) {
    return deserializeSnapshot(readFile(filePath));
}

void NetworkPersistence::saveRunSequence(const std::vector<Run>& runs, const std::filesystem::path& filePath) {
    writeFile(filePath, serializeRunSequence(runs));
}

ReplayEngine NetworkPersistence::loadRunSequenceForReplay(const std::filesystem::path& filePath) {
    return deserializeRunSequenceToReplay(readFile(filePath));
}
