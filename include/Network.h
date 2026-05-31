#pragma once

#include "NetworkEdge.h"
#include "NetworkNode.h"

#include <cstddef>
#include <string>
#include <unordered_map>
#include <vector>

class Network {
public:
    NetworkNode& addNode(const std::string& id, const std::string& label);
    NetworkNode& addNode(const std::string& id, const std::string& label, const std::vector<double>& values);
    NetworkEdge& addEdge(const std::string& id,
                         const std::string& fromNodeId,
                         const std::string& toNodeId,
                         const std::string& relationship);

    const NetworkNode* findNode(const std::string& id) const;
    NetworkNode* findNode(const std::string& id);
    const NetworkEdge* findEdge(const std::string& id) const;
    NetworkEdge* findEdge(const std::string& id);

    const std::vector<NetworkNode>& getNodes() const;
    const std::vector<NetworkEdge>& getEdges() const;
    std::vector<const NetworkEdge*> getEdgesForRelationship(const std::string& relationship) const;
    std::vector<const NetworkEdge*> getOutgoingEdges(const std::string& nodeId) const;
    std::vector<const NetworkEdge*> getIncomingEdges(const std::string& nodeId) const;
    std::vector<const NetworkNode*> traverseFrom(const std::string& startNodeId) const;

    std::size_t getNodeCount() const;
    std::size_t getEdgeCount() const;
    std::size_t getRelationshipCount() const;

private:
    std::vector<NetworkNode> nodes_;
    std::vector<NetworkEdge> edges_;
    std::unordered_map<std::string, std::size_t> nodeIndexById_;
    std::unordered_map<std::string, std::size_t> edgeIndexById_;
    std::unordered_map<std::string, std::vector<std::size_t>> edgeIndexesByRelationship_;

    void requireKnownNode(const std::string& nodeId) const;
};
