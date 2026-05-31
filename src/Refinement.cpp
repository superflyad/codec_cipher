#include "Refinement.h"

#include <stdexcept>

NetworkNode& RefinementOperations::refineNode(Network& network,
                                              const std::string& sourceNodeId,
                                              const std::string& refinedNodeId,
                                              const std::string& refinedNodeLabel,
                                              const std::string& edgeId,
                                              const std::string& relationship) {
    if (network.findNode(sourceNodeId) == nullptr) {
        throw std::invalid_argument("Unknown source node id: " + sourceNodeId);
    }

    NetworkNode& refinedNode = network.addNode(refinedNodeId, refinedNodeLabel);
    network.addEdge(edgeId, sourceNodeId, refinedNodeId, relationship);
    return refinedNode;
}

NetworkNode& RefinementOperations::refineEdge(Network& network,
                                              const std::string& sourceEdgeId,
                                              const std::string& midpointNodeId,
                                              const std::string& midpointNodeLabel,
                                              const std::string& firstEdgeId,
                                              const std::string& secondEdgeId,
                                              const std::string& relationship) {
    const NetworkEdge* sourceEdge = network.findEdge(sourceEdgeId);
    if (sourceEdge == nullptr) {
        throw std::invalid_argument("Unknown source edge id: " + sourceEdgeId);
    }

    const std::string fromNodeId = sourceEdge->getFromNodeId();
    const std::string toNodeId = sourceEdge->getToNodeId();
    NetworkNode& midpointNode = network.addNode(midpointNodeId, midpointNodeLabel);
    network.addEdge(firstEdgeId, fromNodeId, midpointNodeId, relationship);
    network.addEdge(secondEdgeId, midpointNodeId, toNodeId, relationship);
    return midpointNode;
}

Cube& RefinementOperations::refineCube(NestedCubeContainer& nestedCubes,
                                       const std::string& parentCubeId,
                                       const std::string& childCubeId) {
    return nestedCubes.addChildCube(parentCubeId, childCubeId);
}

std::vector<std::string> RefinementOperations::generateNestedCubes(NestedCubeContainer& nestedCubes,
                                                                   const std::string& parentCubeId,
                                                                   const std::string& childIdPrefix,
                                                                   std::size_t count) {
    std::vector<std::string> generatedCubeIds;
    generatedCubeIds.reserve(count);

    for (std::size_t index = 0; index < count; ++index) {
        const std::string childCubeId = childIdPrefix + "-" + std::to_string(index + 1);
        nestedCubes.addChildCube(parentCubeId, childCubeId);
        generatedCubeIds.push_back(childCubeId);
    }

    return generatedCubeIds;
}

NetworkEdge& RefinementOperations::mutateTopology(Network& network,
                                                  const std::string& edgeId,
                                                  const std::string& fromNodeId,
                                                  const std::string& toNodeId,
                                                  const std::string& relationship) {
    return network.addEdge(edgeId, fromNodeId, toNodeId, relationship);
}

void RefinementRuleRegistry::addRule(const std::string& name, const std::string& description) {
    if (findRule(name) != nullptr) {
        throw std::invalid_argument("Duplicate refinement rule: " + name);
    }

    rules_.push_back(RefinementRule{name, description});
}

const RefinementRule* RefinementRuleRegistry::findRule(const std::string& name) const {
    for (const auto& rule : rules_) {
        if (rule.name == name) {
            return &rule;
        }
    }

    return nullptr;
}

const std::vector<RefinementRule>& RefinementRuleRegistry::listRules() const {
    return rules_;
}

RefinementRuleRegistry RefinementRuleRegistry::createDefault() {
    RefinementRuleRegistry registry;
    registry.addRule("node.refine", "Create a new node connected to an existing source node.");
    registry.addRule("edge.refine", "Create a midpoint node and connect it along an existing edge.");
    registry.addRule("cube.refine", "Create a child cube inside an existing parent cube.");
    registry.addRule("cube.generate_nested", "Generate multiple child cubes inside an existing parent cube.");
    registry.addRule("topology.mutate", "Create a new relationship edge between known nodes.");
    return registry;
}
