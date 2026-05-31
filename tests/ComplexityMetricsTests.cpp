#include "ComplexityMetrics.h"

#include <cassert>

namespace {

Network createNetwork() {
    Network network;
    network.addNode("root", "Root");
    network.addNode("a", "A");
    network.addNode("b", "B");
    network.addEdge("edge-1", "root", "a", "contains");
    network.addEdge("edge-2", "root", "b", "contains");
    network.addEdge("edge-3", "a", "b", "refines");
    return network;
}

NestedCubeContainer createNestedCubes() {
    NestedCubeContainer nestedCubes;
    nestedCubes.addRootCube("root-cube");
    nestedCubes.addChildCube("root-cube", "child-cube");
    nestedCubes.addChildCube("child-cube", "inner-cube");
    return nestedCubes;
}

void testNetworkComplexityMetrics() {
    const Network network = createNetwork();
    const NetworkComplexityMetrics metrics = ComplexityMetrics::measureNetworkComplexity(network);

    assert(metrics.nodeCount == 3);
    assert(metrics.edgeCount == 3);
    assert(metrics.relationshipCount == 2);
    assert(metrics.edgeToNodeRatio == 1.0);
}

void testDepthScoringMetrics() {
    const NestedCubeContainer nestedCubes = createNestedCubes();
    const DepthScoreMetrics metrics = ComplexityMetrics::measureDepth(nestedCubes);

    assert(metrics.cubeCount == 3);
    assert(metrics.maxDepth == 2);
    assert(metrics.averageDepth == 1.0);
}

void testRelationshipDensityMetrics() {
    const Network network = createNetwork();
    const RelationshipDensityMetrics metrics = ComplexityMetrics::measureRelationshipDensity(network);

    assert(metrics.relationshipCount == 2);
    assert(metrics.relationshipsPerNode > 0.66);
    assert(metrics.relationshipsPerNode < 0.67);
    assert(metrics.edgesPerRelationship == 1.5);
}

void testRecoveryDifficultyPrototype() {
    Network network = createNetwork();
    NestedCubeContainer nestedCubes = createNestedCubes();
    RunSequenceManager manager(4);
    manager.recordRun("baseline", network, nestedCubes);
    network.addNode("c", "C");
    manager.recordRun("expanded", network, nestedCubes);

    const RecoveryDifficultyEstimate estimate =
        ComplexityMetrics::estimateRecoveryDifficulty(network, nestedCubes, manager);

    assert(estimate.score > 0.0);
    assert(estimate.runCount == 2);
    assert(estimate.maxDepth == 2);
    assert(estimate.relationshipCount == 2);
}

} // namespace

int main() {
    testNetworkComplexityMetrics();
    testDepthScoringMetrics();
    testRelationshipDensityMetrics();
    testRecoveryDifficultyPrototype();
    return 0;
}
