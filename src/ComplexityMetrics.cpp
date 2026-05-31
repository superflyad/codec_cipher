#include "ComplexityMetrics.h"

NetworkComplexityMetrics ComplexityMetrics::measureNetworkComplexity(const Network& network) {
    const std::size_t nodeCount = network.getNodeCount();
    const std::size_t edgeCount = network.getEdgeCount();
    const std::size_t relationshipCount = network.getRelationshipCount();
    const double edgeToNodeRatio = nodeCount == 0 ? 0.0 : static_cast<double>(edgeCount) / nodeCount;

    return NetworkComplexityMetrics{nodeCount, edgeCount, relationshipCount, edgeToNodeRatio};
}

DepthScoreMetrics ComplexityMetrics::measureDepth(const NestedCubeContainer& nestedCubes) {
    const auto entries = nestedCubes.inspectHierarchy();
    if (entries.empty()) {
        return DepthScoreMetrics{0, 0, 0.0};
    }

    std::size_t maxDepth = 0;
    std::size_t totalDepth = 0;
    for (const auto& entry : entries) {
        if (entry.depth > maxDepth) {
            maxDepth = entry.depth;
        }
        totalDepth += entry.depth;
    }

    return DepthScoreMetrics{entries.size(), maxDepth, static_cast<double>(totalDepth) / entries.size()};
}

RelationshipDensityMetrics ComplexityMetrics::measureRelationshipDensity(const Network& network) {
    const std::size_t relationshipCount = network.getRelationshipCount();
    const double relationshipsPerNode =
        network.getNodeCount() == 0 ? 0.0 : static_cast<double>(relationshipCount) / network.getNodeCount();
    const double edgesPerRelationship =
        relationshipCount == 0 ? 0.0 : static_cast<double>(network.getEdgeCount()) / relationshipCount;

    return RelationshipDensityMetrics{relationshipCount, relationshipsPerNode, edgesPerRelationship};
}

RecoveryDifficultyEstimate ComplexityMetrics::estimateRecoveryDifficulty(
    const Network& network,
    const NestedCubeContainer& nestedCubes,
    const RunSequenceManager& runSequenceManager) {
    const NetworkComplexityMetrics complexity = measureNetworkComplexity(network);
    const DepthScoreMetrics depth = measureDepth(nestedCubes);
    const RelationshipDensityMetrics density = measureRelationshipDensity(network);
    const std::size_t runCount = runSequenceManager.getRuns().size();

    const double score = static_cast<double>(complexity.nodeCount)
        + (static_cast<double>(complexity.edgeCount) * 1.5)
        + (static_cast<double>(depth.maxDepth) * 2.0)
        + (density.edgesPerRelationship * 1.25)
        + (static_cast<double>(runCount) * 0.75);

    return RecoveryDifficultyEstimate{score, runCount, depth.maxDepth, complexity.relationshipCount};
}
