#pragma once

#include "NestedCube.h"
#include "Network.h"
#include "RunEngine.h"

#include <cstddef>

struct NetworkComplexityMetrics {
    std::size_t nodeCount;
    std::size_t edgeCount;
    std::size_t relationshipCount;
    double edgeToNodeRatio;
};

struct DepthScoreMetrics {
    std::size_t cubeCount;
    std::size_t maxDepth;
    double averageDepth;
};

struct RelationshipDensityMetrics {
    std::size_t relationshipCount;
    double relationshipsPerNode;
    double edgesPerRelationship;
};

struct RecoveryDifficultyEstimate {
    double score;
    std::size_t runCount;
    std::size_t maxDepth;
    std::size_t relationshipCount;
};

class ComplexityMetrics {
public:
    static NetworkComplexityMetrics measureNetworkComplexity(const Network& network);
    static DepthScoreMetrics measureDepth(const NestedCubeContainer& nestedCubes);
    static RelationshipDensityMetrics measureRelationshipDensity(const Network& network);
    static RecoveryDifficultyEstimate estimateRecoveryDifficulty(const Network& network,
                                                                  const NestedCubeContainer& nestedCubes,
                                                                  const RunSequenceManager& runSequenceManager);
};
