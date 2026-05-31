#include "ComplexityMetrics.h"
#include "Experiment.h"
#include "NetworkPersistence.h"
#include "Refinement.h"
#include "Visualization.h"

#include <cassert>
#include <filesystem>
#include <string>

namespace {

void testVersion01Workflow() {
    ExperimentSessionManager sessionManager;
    ExperimentSession& baseline = sessionManager.createSession("baseline", "Baseline", 100);
    ExperimentSession& refined = sessionManager.createSession("refined", "Refined", 100);

    baseline.getNetwork().addNode("root", "Root");
    baseline.getNestedCubes().addRootCube("cube-root");
    baseline.getRunSequenceManager().recordRun("Run 1", baseline.getNetwork(), baseline.getNestedCubes());
    baseline.addNote("Created the baseline network and root cube.");

    refined.getNetwork().addNode("root", "Root");
    refined.getNestedCubes().addRootCube("cube-root");
    refined.getRunSequenceManager().recordRun("Run 1", refined.getNetwork(), refined.getNestedCubes());

    RefinementOperations::refineNode(refined.getNetwork(), "root", "child", "Child", "edge-1");
    RefinementOperations::mutateTopology(refined.getNetwork(), "edge-2", "child", "root", "cycles");
    RefinementOperations::generateNestedCubes(refined.getNestedCubes(), "cube-root", "inner", 2);
    refined.getRunSequenceManager().recordRun("Run 2", refined.getNetwork(), refined.getNestedCubes());
    refined.addNote("Refined the network and generated nested cubes.");

    const auto replayedSnapshots = refined.getRunSequenceManager().createReplayEngine().replayAll();
    const std::string networkView = AsciiVisualization::renderNetwork(refined.getNetwork());
    const std::string cubeView = AsciiVisualization::renderNestedCubes(refined.getNestedCubes());
    const std::string timelineView = AsciiVisualization::renderRunTimeline(refined.getRunSequenceManager());
    const std::string svgView = SvgExportPrototype::renderNetwork(refined.getNetwork());
    const NetworkComplexityMetrics networkMetrics =
        ComplexityMetrics::measureNetworkComplexity(refined.getNetwork());
    const DepthScoreMetrics depthMetrics = ComplexityMetrics::measureDepth(refined.getNestedCubes());
    const RecoveryDifficultyEstimate recoveryDifficulty = ComplexityMetrics::estimateRecoveryDifficulty(
        refined.getNetwork(), refined.getNestedCubes(), refined.getRunSequenceManager());
    const ExperimentComparison comparison = ExperimentComparisonTools::compare(baseline, refined);

    assert(replayedSnapshots.size() == 2);
    assert(replayedSnapshots[1].network.getNodeCount() == 2);
    assert(networkView.find("root --refines-> child") != std::string::npos);
    assert(cubeView.find("  - Cube inner-1") != std::string::npos);
    assert(timelineView.find("Run 2") != std::string::npos);
    assert(svgView.find("<svg") != std::string::npos);
    assert(networkMetrics.nodeCount == 2);
    assert(depthMetrics.maxDepth == 1);
    assert(recoveryDifficulty.score > 0.0);
    assert(comparison.nodeDelta == 1);
    assert(comparison.cubeDelta == 2);

    const std::filesystem::path runsPath = std::filesystem::temp_directory_path() / "codec_cipher_v01_runs.ccruns";
    NetworkPersistence::saveRunSequence(refined.getRunSequenceManager().getRuns(), runsPath);
    const ReplayEngine loadedReplay = NetworkPersistence::loadRunSequenceForReplay(runsPath);
    assert(loadedReplay.replayAll().size() == 2);
    std::filesystem::remove(runsPath);
}

} // namespace

int main() {
    testVersion01Workflow();
    return 0;
}
