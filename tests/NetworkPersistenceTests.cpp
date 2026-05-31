#include "NetworkPersistence.h"

#include <cassert>
#include <filesystem>

namespace {

Network createNetwork() {
    Network network;
    network.addNode("root", "Root", {1.0, 2.0});
    network.addNode("child", "Child");
    network.addEdge("edge-1", "root", "child", "contains");
    return network;
}

NestedCubeContainer createNestedCubes() {
    NestedCubeContainer nestedCubes;
    nestedCubes.addRootCube("cube-root");
    nestedCubes.addChildCube("cube-root", "cube-child");
    return nestedCubes;
}

void testNetworkSerializationRoundTrip() {
    const Network network = createNetwork();
    const Network restored = NetworkPersistence::deserializeNetwork(NetworkPersistence::serializeNetwork(network));

    assert(restored.getNodeCount() == 2);
    assert(restored.getEdgeCount() == 1);
    assert(restored.findNode("root")->getValues().size() == 2);
    assert(restored.findEdge("edge-1")->getRelationship() == "contains");
}

void testSnapshotSerializationRoundTrip() {
    NetworkSnapshot snapshot{2, 77, "expanded", createNetwork(), createNestedCubes()};
    const NetworkSnapshot restored =
        NetworkPersistence::deserializeSnapshot(NetworkPersistence::serializeSnapshot(snapshot));

    assert(restored.runNumber == 2);
    assert(restored.seed == 77);
    assert(restored.label == "expanded");
    assert(restored.network.getNodeCount() == 2);
    assert(restored.nestedCubes.getCubeCount() == 2);
    assert(restored.nestedCubes.getCubeDepth("cube-child") == 1);
}

void testRunSequenceReplayFromSavedSequence() {
    RunSequenceManager manager(10);
    Network network = createNetwork();
    NestedCubeContainer nestedCubes = createNestedCubes();
    manager.recordRun("Run 1", network, nestedCubes);
    network.addNode("second-child", "Second Child");
    manager.recordRun("Run 2", network, nestedCubes);

    const ReplayEngine replayEngine =
        NetworkPersistence::deserializeRunSequenceToReplay(NetworkPersistence::serializeRunSequence(manager.getRuns()));
    const auto snapshots = replayEngine.replayAll();

    assert(snapshots.size() == 2);
    assert(snapshots[0].network.getNodeCount() == 2);
    assert(snapshots[1].network.getNodeCount() == 3);
    assert(replayEngine.replayTo(2)->label == "Run 2");
}

void testFilePersistence() {
    const std::filesystem::path networkPath = std::filesystem::temp_directory_path() / "codec_cipher_network_test.ccnet";
    const std::filesystem::path snapshotPath = std::filesystem::temp_directory_path() / "codec_cipher_snapshot_test.ccsnap";
    const std::filesystem::path runsPath = std::filesystem::temp_directory_path() / "codec_cipher_runs_test.ccruns";

    const Network network = createNetwork();
    NetworkSnapshot snapshot{1, 3, "saved", network, createNestedCubes()};
    RunSequenceManager manager(3);
    manager.recordRun("saved", network, snapshot.nestedCubes);

    NetworkPersistence::saveNetwork(network, networkPath);
    NetworkPersistence::saveSnapshot(snapshot, snapshotPath);
    NetworkPersistence::saveRunSequence(manager.getRuns(), runsPath);

    assert(NetworkPersistence::loadNetwork(networkPath).getNodeCount() == 2);
    assert(NetworkPersistence::loadSnapshot(snapshotPath).nestedCubes.getCubeCount() == 2);
    assert(NetworkPersistence::loadRunSequenceForReplay(runsPath).replayAll().size() == 1);

    std::filesystem::remove(networkPath);
    std::filesystem::remove(snapshotPath);
    std::filesystem::remove(runsPath);
}

} // namespace

int main() {
    testNetworkSerializationRoundTrip();
    testSnapshotSerializationRoundTrip();
    testRunSequenceReplayFromSavedSequence();
    testFilePersistence();
    return 0;
}
