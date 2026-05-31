#include "RunEngine.h"

#include <cassert>

namespace {

Network createNetworkWithNode(const std::string& nodeId) {
    Network network;
    network.addNode(nodeId, nodeId);
    return network;
}

NestedCubeContainer createCubesWithRoot(const std::string& cubeId) {
    NestedCubeContainer nestedCubes;
    nestedCubes.addRootCube(cubeId);
    return nestedCubes;
}

void testRunModelSequenceAndDeterministicSeeds() {
    RunSequenceManager manager(42);
    Network network = createNetworkWithNode("root");
    NestedCubeContainer nestedCubes = createCubesWithRoot("cube-root");

    const Run& firstRun = manager.recordRun("Run 1", network, nestedCubes);
    const std::size_t firstRunNumber = firstRun.number;
    const std::uint32_t firstRunSeed = firstRun.seed;
    network.addNode("child", "child");
    network.addEdge("edge-1", "root", "child", "contains");
    nestedCubes.addChildCube("cube-root", "cube-child");
    const Run& secondRun = manager.recordRun("Run 2", network, nestedCubes);

    assert(manager.getBaseSeed() == 42);
    assert(firstRunNumber == 1);
    assert(firstRunSeed == manager.previewSeedForRun(1));
    assert(secondRun.number == 2);
    assert(secondRun.seed == manager.previewSeedForRun(2));
    assert(firstRunSeed != secondRun.seed);
    assert(manager.getRuns().size() == 2);
    assert(manager.findRun(2)->label == "Run 2");
    assert(manager.findRun(3) == nullptr);
}

void testSnapshotsAndRunHistory() {
    RunSequenceManager manager(7);
    Network network = createNetworkWithNode("root");
    NestedCubeContainer nestedCubes = createCubesWithRoot("cube-root");

    manager.recordRun("baseline", network, nestedCubes);
    network.addNode("child", "child");
    nestedCubes.addChildCube("cube-root", "cube-child");
    manager.recordRun("expanded", network, nestedCubes);

    const auto history = manager.getHistory();
    assert(history.size() == 2);
    assert(history[0].runNumber == 1);
    assert(history[0].nodeCount == 1);
    assert(history[0].edgeCount == 0);
    assert(history[0].cubeCount == 1);
    assert(history[1].runNumber == 2);
    assert(history[1].nodeCount == 2);
    assert(history[1].cubeCount == 2);
}

void testReplayEngine() {
    RunSequenceManager manager(99);
    Network network = createNetworkWithNode("root");
    NestedCubeContainer nestedCubes = createCubesWithRoot("cube-root");

    manager.recordRun("Run 1", network, nestedCubes);
    network.addNode("child", "child");
    manager.recordRun("Run 2", network, nestedCubes);

    const ReplayEngine replayEngine = manager.createReplayEngine();
    const auto snapshots = replayEngine.replayAll();
    const auto runTwo = replayEngine.replayTo(2);

    assert(snapshots.size() == 2);
    assert(snapshots[0].runNumber == 1);
    assert(snapshots[0].network.getNodeCount() == 1);
    assert(snapshots[1].runNumber == 2);
    assert(snapshots[1].network.getNodeCount() == 2);
    assert(runTwo.has_value());
    assert(runTwo->label == "Run 2");
    assert(!replayEngine.replayTo(3).has_value());
}

} // namespace

int main() {
    testRunModelSequenceAndDeterministicSeeds();
    testSnapshotsAndRunHistory();
    testReplayEngine();
    return 0;
}
