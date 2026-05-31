#include "Refinement.h"

#include <cassert>
#include <stdexcept>

namespace {

void testNodeAndTopologyRefinement() {
    Network network;
    network.addNode("root", "Root");

    RefinementOperations::refineNode(network, "root", "child", "Child", "edge-1");
    RefinementOperations::mutateTopology(network, "edge-2", "child", "root", "cycles");

    assert(network.getNodeCount() == 2);
    assert(network.getEdgeCount() == 2);
    assert(network.getEdgesForRelationship("refines").size() == 1);
    assert(network.getEdgesForRelationship("cycles").size() == 1);
    assert(network.traverseFrom("root").size() == 2);
}

void testEdgeRefinement() {
    Network network;
    network.addNode("a", "A");
    network.addNode("b", "B");
    network.addEdge("edge-1", "a", "b", "contains");

    RefinementOperations::refineEdge(network, "edge-1", "mid", "Midpoint", "edge-2", "edge-3");

    assert(network.getNodeCount() == 3);
    assert(network.getEdgeCount() == 3);
    assert(network.findNode("mid") != nullptr);
    assert(network.findEdge("edge-2")->getFromNodeId() == "a");
    assert(network.findEdge("edge-3")->getToNodeId() == "b");
    assert(network.getEdgesForRelationship("refines").size() == 2);
}

void testCubeRefinementAndNestedGeneration() {
    NestedCubeContainer nestedCubes;
    nestedCubes.addRootCube("root-cube");

    RefinementOperations::refineCube(nestedCubes, "root-cube", "child-cube");
    const auto generatedIds = RefinementOperations::generateNestedCubes(nestedCubes, "child-cube", "inner", 2);

    assert(generatedIds.size() == 2);
    assert(generatedIds[0] == "inner-1");
    assert(generatedIds[1] == "inner-2");
    assert(nestedCubes.getCubeCount() == 4);
    assert(nestedCubes.getCubeDepth("child-cube") == 1);
    assert(nestedCubes.getCubeDepth("inner-2") == 2);
}

void testRuleRegistry() {
    RefinementRuleRegistry registry = RefinementRuleRegistry::createDefault();

    assert(registry.listRules().size() == 5);
    assert(registry.findRule("node.refine") != nullptr);
    assert(registry.findRule("missing") == nullptr);

    bool duplicateRejected = false;
    try {
        registry.addRule("node.refine", "Duplicate");
    } catch (const std::invalid_argument&) {
        duplicateRejected = true;
    }
    assert(duplicateRejected);
}

} // namespace

int main() {
    testNodeAndTopologyRefinement();
    testEdgeRefinement();
    testCubeRefinementAndNestedGeneration();
    testRuleRegistry();
    return 0;
}
