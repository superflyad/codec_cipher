#pragma once

#include "NestedCube.h"
#include "Network.h"

#include <string>
#include <vector>

struct RefinementRule {
    std::string name;
    std::string description;
};

class RefinementOperations {
public:
    static NetworkNode& refineNode(Network& network,
                                   const std::string& sourceNodeId,
                                   const std::string& refinedNodeId,
                                   const std::string& refinedNodeLabel,
                                   const std::string& edgeId,
                                   const std::string& relationship = "refines");

    static NetworkNode& refineEdge(Network& network,
                                   const std::string& sourceEdgeId,
                                   const std::string& midpointNodeId,
                                   const std::string& midpointNodeLabel,
                                   const std::string& firstEdgeId,
                                   const std::string& secondEdgeId,
                                   const std::string& relationship = "refines");

    static Cube& refineCube(NestedCubeContainer& nestedCubes,
                            const std::string& parentCubeId,
                            const std::string& childCubeId);

    static std::vector<std::string> generateNestedCubes(NestedCubeContainer& nestedCubes,
                                                        const std::string& parentCubeId,
                                                        const std::string& childIdPrefix,
                                                        std::size_t count);

    static NetworkEdge& mutateTopology(Network& network,
                                       const std::string& edgeId,
                                       const std::string& fromNodeId,
                                       const std::string& toNodeId,
                                       const std::string& relationship);
};

class RefinementRuleRegistry {
public:
    void addRule(const std::string& name, const std::string& description);
    const RefinementRule* findRule(const std::string& name) const;
    const std::vector<RefinementRule>& listRules() const;

    static RefinementRuleRegistry createDefault();

private:
    std::vector<RefinementRule> rules_;
};
