#include "Visualization.h"

#include "Refinement.h"

#include <cassert>
#include <string>

namespace {

void testAsciiNetworkVisualization() {
    Network network;
    network.addNode("root", "Root");
    network.addNode("child", "Child");
    network.addEdge("edge-1", "root", "child", "contains");

    const std::string output = AsciiVisualization::renderNetwork(network);
    assert(output.find("Network") != std::string::npos);
    assert(output.find("Nodes (2)") != std::string::npos);
    assert(output.find("root --contains-> child") != std::string::npos);
}

void testAsciiNestedCubeVisualization() {
    NestedCubeContainer nestedCubes;
    nestedCubes.addRootCube("root");
    RefinementOperations::generateNestedCubes(nestedCubes, "root", "child", 2);
    nestedCubes.addChildCube("child-1", "inner");

    const std::string output = AsciiVisualization::renderNestedCubes(nestedCubes);
    assert(output.find("Nested Cubes") != std::string::npos);
    assert(output.find("- Cube root") != std::string::npos);
    assert(output.find("  - Cube child-1") != std::string::npos);
    assert(output.find("    - Cube inner") != std::string::npos);
}

void testRunTimelineVisualization() {
    Network network;
    network.addNode("root", "Root");
    NestedCubeContainer nestedCubes;
    nestedCubes.addRootCube("cube-root");

    RunSequenceManager manager(5);
    manager.recordRun("baseline", network, nestedCubes);

    const std::string output = AsciiVisualization::renderRunTimeline(manager);
    assert(output.find("Run Timeline") != std::string::npos);
    assert(output.find("Run 1") != std::string::npos);
    assert(output.find("baseline") != std::string::npos);
    assert(output.find("nodes=1") != std::string::npos);
}

void testSvgExportPrototype() {
    Network network;
    network.addNode("root", "Root");
    network.addNode("child", "Child");
    network.addEdge("edge-1", "root", "child", "contains");

    const std::string output = SvgExportPrototype::renderNetwork(network);
    assert(output.find("<svg") != std::string::npos);
    assert(output.find("<line") != std::string::npos);
    assert(output.find("<circle") != std::string::npos);
    assert(output.find("root") != std::string::npos);
    assert(output.find("child") != std::string::npos);
}

} // namespace

int main() {
    testAsciiNetworkVisualization();
    testAsciiNestedCubeVisualization();
    testRunTimelineVisualization();
    testSvgExportPrototype();
    return 0;
}
