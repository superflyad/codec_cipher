#include "Persistence.h"

#include <cctype>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <utility>

Persistence::Persistence(std::filesystem::path saveDirectory)
    : saveDirectory_(std::move(saveDirectory)) {
    std::filesystem::create_directories(saveDirectory_);
}

std::filesystem::path Persistence::saveObject(const DimensionalObject& object) const {
    std::filesystem::create_directories(saveDirectory_);
    const std::filesystem::path filePath = saveDirectory_ / (sanitizeFilename(object.getName()) + ".ccobj");

    std::ofstream output(filePath);
    if (!output) {
        throw std::runtime_error("Unable to open save file for writing: " + filePath.string());
    }

    output << "CodecCipherObject v1\n";
    output << object.getName() << '\n';
    output << object.getCreationTimestamp() << '\n';
    output << object.getDimensionCount() << '\n';

    const auto& values = object.getValues();
    for (std::size_t index = 0; index < values.size(); ++index) {
        if (index > 0) {
            output << ' ';
        }
        output << values[index];
    }
    output << '\n';

    return filePath;
}

std::optional<DimensionalObject> Persistence::loadObject(const std::filesystem::path& path) const {
    std::filesystem::path filePath = path;
    if (!filePath.is_absolute() && !std::filesystem::exists(filePath)) {
        filePath = saveDirectory_ / filePath;
    }

    std::ifstream input(filePath);
    if (!input) {
        return std::nullopt;
    }

    std::string header;
    std::getline(input, header);
    if (header != "CodecCipherObject v1") {
        return std::nullopt;
    }

    std::string name;
    std::string timestamp;
    std::string countLine;
    std::getline(input, name);
    std::getline(input, timestamp);
    std::getline(input, countLine);

    if (!input || name.empty() || timestamp.empty() || countLine.empty()) {
        return std::nullopt;
    }

    std::size_t expectedCount = 0;
    try {
        expectedCount = static_cast<std::size_t>(std::stoull(countLine));
    } catch (const std::exception&) {
        return std::nullopt;
    }

    std::string valuesLine;
    std::getline(input, valuesLine);
    std::istringstream valuesStream(valuesLine);
    std::vector<double> values;
    double value = 0.0;
    while (valuesStream >> value) {
        values.push_back(value);
    }

    if (values.size() != expectedCount) {
        return std::nullopt;
    }

    return DimensionalObject(name, timestamp, values);
}

const std::filesystem::path& Persistence::getSaveDirectory() const {
    return saveDirectory_;
}

std::string Persistence::sanitizeFilename(const std::string& name) {
    std::string sanitized;
    for (const unsigned char character : name) {
        if (std::isalnum(character) || character == '-' || character == '_') {
            sanitized.push_back(static_cast<char>(character));
        } else if (std::isspace(character)) {
            sanitized.push_back('_');
        }
    }

    if (sanitized.empty()) {
        return "dimensional_object";
    }

    return sanitized;
}
