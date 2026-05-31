#include "Visualization.h"

#include <sstream>
#include <unordered_map>

std::string AsciiVisualization::renderNetwork(const Network& network) {
    std::ostringstream stream;
    stream << "Network\n";
    stream << "Nodes (" << network.getNodeCount() << ")\n";

    for (const auto& node : network.getNodes()) {
        stream << "- " << node.getId() << " [" << node.getLabel() << "]\n";
    }

    stream << "Edges (" << network.getEdgeCount() << ")\n";
    for (const auto& edge : network.getEdges()) {
        stream << "- " << edge.getFromNodeId() << " --" << edge.getRelationship() << "-> "
               << edge.getToNodeId() << "\n";
    }

    return stream.str();
}

std::string AsciiVisualization::renderNestedCubes(const NestedCubeContainer& nestedCubes) {
    std::ostringstream stream;
    stream << "Nested Cubes\n";

    for (const auto& entry : nestedCubes.inspectHierarchy()) {
        if (!entry.parentCubeId.has_value()) {
            std::string branch;
            renderCubeBranch(nestedCubes, entry.cubeId, 0, branch);
            stream << branch;
        }
    }

    return stream.str();
}

std::string AsciiVisualization::renderRunTimeline(const RunSequenceManager& runSequenceManager) {
    std::ostringstream stream;
    stream << "Run Timeline\n";

    for (const auto& historyEntry : runSequenceManager.getHistory()) {
        stream << "Run " << historyEntry.runNumber << " [seed " << historyEntry.seed << "] "
               << historyEntry.label << " nodes=" << historyEntry.nodeCount
               << " edges=" << historyEntry.edgeCount << " cubes=" << historyEntry.cubeCount << "\n";
    }

    return stream.str();
}

void AsciiVisualization::renderCubeBranch(const NestedCubeContainer& nestedCubes,
                                          const std::string& cubeId,
                                          std::size_t depth,
                                          std::string& output) {
    output.append(depth * 2, ' ');
    output += "- Cube " + cubeId + "\n";

    for (const Cube* childCube : nestedCubes.getChildCubes(cubeId)) {
        renderCubeBranch(nestedCubes, childCube->getId(), depth + 1, output);
    }
}

std::string SvgExportPrototype::renderNetwork(const Network& network) {
    constexpr int width = 640;
    constexpr int height = 240;
    constexpr int y = 120;
    constexpr int leftPadding = 80;
    constexpr int spacing = 120;

    std::ostringstream stream;
    std::unordered_map<std::string, int> xByNodeId;

    stream << "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"" << width << "\" height=\"" << height
           << "\" viewBox=\"0 0 " << width << " " << height << "\">\n";
    stream << "<rect width=\"100%\" height=\"100%\" fill=\"white\"/>\n";

    int nodeIndex = 0;
    for (const auto& node : network.getNodes()) {
        xByNodeId[node.getId()] = leftPadding + (nodeIndex * spacing);
        ++nodeIndex;
    }

    for (const auto& edge : network.getEdges()) {
        stream << "<line x1=\"" << xByNodeId[edge.getFromNodeId()] << "\" y1=\"" << y << "\" x2=\""
               << xByNodeId[edge.getToNodeId()] << "\" y2=\"" << y
               << "\" stroke=\"black\" stroke-width=\"2\"/>\n";
    }

    for (const auto& node : network.getNodes()) {
        const int x = xByNodeId[node.getId()];
        stream << "<circle cx=\"" << x << "\" cy=\"" << y << "\" r=\"20\" fill=\"white\" stroke=\"black\"/>\n";
        stream << "<text x=\"" << x << "\" y=\"" << (y + 40)
               << "\" font-size=\"12\" text-anchor=\"middle\">" << node.getId() << "</text>\n";
    }

    stream << "</svg>\n";
    return stream.str();
}
