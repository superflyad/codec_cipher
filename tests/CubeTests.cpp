#include "Cube.h"

#include <cassert>
#include <set>
#include <string>

namespace {

void testCubePrimitiveAndMetrics() {
    const Cube cube("cube-1");
    const CubeMetrics metrics = cube.getMetrics();

    assert(cube.getId() == "cube-1");
    assert(metrics.vertexCount == 8);
    assert(metrics.edgeCount == 12);
    assert(metrics.dimensionCount == 3);
}

void testVertexMapping() {
    const Cube cube("cube-1");
    const auto vertexLabels = cube.inspectVertexLabels();
    const std::set<std::string> uniqueLabels(vertexLabels.begin(), vertexLabels.end());

    assert(vertexLabels.size() == 8);
    assert(uniqueLabels.size() == 8);
    assert(cube.findVertexByLabel("000") != nullptr);
    assert(cube.findVertexByLabel("111") != nullptr);
    assert(cube.findVertexByLabel("222") == nullptr);
    assert(cube.findVertexByLabel("101")->coordinates[0] == 1);
    assert(cube.findVertexByLabel("101")->coordinates[1] == 0);
    assert(cube.findVertexByLabel("101")->coordinates[2] == 1);
}

void testEdgeGenerationAndInspection() {
    const Cube cube("cube-1");
    const auto edgeLabels = cube.inspectEdgeLabels();
    const std::set<std::string> uniqueEdges(edgeLabels.begin(), edgeLabels.end());

    assert(edgeLabels.size() == 12);
    assert(uniqueEdges.size() == 12);
    assert(uniqueEdges.find("000->001") != uniqueEdges.end());
    assert(uniqueEdges.find("000->010") != uniqueEdges.end());
    assert(uniqueEdges.find("000->100") != uniqueEdges.end());
    assert(uniqueEdges.find("011->111") != uniqueEdges.end());
}

} // namespace

int main() {
    testCubePrimitiveAndMetrics();
    testVertexMapping();
    testEdgeGenerationAndInspection();
    return 0;
}
