#include "Network.h"

#include <cassert>
#include <stdexcept>
#include <string>

namespace {

void testNodeAndEdgeCreation() {
    Network network;

    network.addNode("root", "Root", {1.0, 2.0});
    network.addNode("child", "Child");
    const NetworkEdge& edge = network.addEdge("edge-1", "root", "child", "contains");

    assert(network.getNodeCount() == 2);
    assert(network.getEdgeCount() == 1);
    assert(network.getRelationshipCount() == 1);
    assert(edge.getRelationship() == "contains");
    assert(network.findNode("root")->getValues().size() == 2);
    assert(network.findEdge("edge-1")->getToNodeId() == "child");
}

void testLookupFailuresAndDuplicateProtection() {
    Network network;
    network.addNode("root", "Root");

    assert(network.findNode("missing") == nullptr);
    assert(network.findEdge("missing") == nullptr);

    bool duplicateNodeRejected = false;
    try {
        network.addNode("root", "Duplicate");
    } catch (const std::invalid_argument&) {
        duplicateNodeRejected = true;
    }
    assert(duplicateNodeRejected);

    bool unknownTargetRejected = false;
    try {
        network.addEdge("bad-edge", "root", "missing", "contains");
    } catch (const std::invalid_argument&) {
        unknownTargetRejected = true;
    }
    assert(unknownTargetRejected);
}

void testRelationshipRegistryAndTraversal() {
    Network network;
    network.addNode("root", "Root");
    network.addNode("a", "A");
    network.addNode("b", "B");
    network.addNode("c", "C");

    network.addEdge("edge-1", "root", "a", "contains");
    network.addEdge("edge-2", "root", "b", "contains");
    network.addEdge("edge-3", "a", "c", "refines");
    network.addEdge("edge-4", "c", "root", "cycles");

    const auto containsEdges = network.getEdgesForRelationship("contains");
    assert(containsEdges.size() == 2);
    assert(network.getEdgesForRelationship("missing").empty());

    const auto outgoingRoot = network.getOutgoingEdges("root");
    const auto incomingRoot = network.getIncomingEdges("root");
    assert(outgoingRoot.size() == 2);
    assert(incomingRoot.size() == 1);

    const auto traversal = network.traverseFrom("root");
    assert(traversal.size() == 4);
    assert(traversal[0]->getId() == "root");
    assert(network.traverseFrom("missing").empty());
}

} // namespace

int main() {
    testNodeAndEdgeCreation();
    testLookupFailuresAndDuplicateProtection();
    testRelationshipRegistryAndTraversal();
    return 0;
}
