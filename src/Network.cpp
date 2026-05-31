#include "Network.h"

#include <queue>
#include <stdexcept>
#include <unordered_set>
#include <utility>

NetworkNode& Network::addNode(const std::string& id, const std::string& label) {
    return addNode(id, label, {});
}

NetworkNode& Network::addNode(const std::string& id, const std::string& label, const std::vector<double>& values) {
    if (nodeIndexById_.find(id) != nodeIndexById_.end()) {
        throw std::invalid_argument("Duplicate network node id: " + id);
    }

    nodes_.emplace_back(id, label, values);
    nodeIndexById_[id] = nodes_.size() - 1;
    return nodes_.back();
}

NetworkEdge& Network::addEdge(const std::string& id,
                              const std::string& fromNodeId,
                              const std::string& toNodeId,
                              const std::string& relationship) {
    if (edgeIndexById_.find(id) != edgeIndexById_.end()) {
        throw std::invalid_argument("Duplicate network edge id: " + id);
    }

    requireKnownNode(fromNodeId);
    requireKnownNode(toNodeId);

    edges_.emplace_back(id, fromNodeId, toNodeId, relationship);
    const std::size_t edgeIndex = edges_.size() - 1;
    edgeIndexById_[id] = edgeIndex;
    edgeIndexesByRelationship_[relationship].push_back(edgeIndex);
    return edges_.back();
}

const NetworkNode* Network::findNode(const std::string& id) const {
    const auto iterator = nodeIndexById_.find(id);
    if (iterator == nodeIndexById_.end()) {
        return nullptr;
    }

    return &nodes_[iterator->second];
}

NetworkNode* Network::findNode(const std::string& id) {
    const auto iterator = nodeIndexById_.find(id);
    if (iterator == nodeIndexById_.end()) {
        return nullptr;
    }

    return &nodes_[iterator->second];
}

const NetworkEdge* Network::findEdge(const std::string& id) const {
    const auto iterator = edgeIndexById_.find(id);
    if (iterator == edgeIndexById_.end()) {
        return nullptr;
    }

    return &edges_[iterator->second];
}

NetworkEdge* Network::findEdge(const std::string& id) {
    const auto iterator = edgeIndexById_.find(id);
    if (iterator == edgeIndexById_.end()) {
        return nullptr;
    }

    return &edges_[iterator->second];
}

const std::vector<NetworkNode>& Network::getNodes() const {
    return nodes_;
}

const std::vector<NetworkEdge>& Network::getEdges() const {
    return edges_;
}

std::vector<const NetworkEdge*> Network::getEdgesForRelationship(const std::string& relationship) const {
    std::vector<const NetworkEdge*> matches;
    const auto iterator = edgeIndexesByRelationship_.find(relationship);
    if (iterator == edgeIndexesByRelationship_.end()) {
        return matches;
    }

    for (const std::size_t edgeIndex : iterator->second) {
        matches.push_back(&edges_[edgeIndex]);
    }

    return matches;
}

std::vector<const NetworkEdge*> Network::getOutgoingEdges(const std::string& nodeId) const {
    std::vector<const NetworkEdge*> outgoingEdges;
    for (const auto& edge : edges_) {
        if (edge.getFromNodeId() == nodeId) {
            outgoingEdges.push_back(&edge);
        }
    }

    return outgoingEdges;
}

std::vector<const NetworkEdge*> Network::getIncomingEdges(const std::string& nodeId) const {
    std::vector<const NetworkEdge*> incomingEdges;
    for (const auto& edge : edges_) {
        if (edge.getToNodeId() == nodeId) {
            incomingEdges.push_back(&edge);
        }
    }

    return incomingEdges;
}

std::vector<const NetworkNode*> Network::traverseFrom(const std::string& startNodeId) const {
    std::vector<const NetworkNode*> traversal;
    const NetworkNode* startNode = findNode(startNodeId);
    if (startNode == nullptr) {
        return traversal;
    }

    std::queue<std::string> pending;
    std::unordered_set<std::string> visited;
    pending.push(startNodeId);
    visited.insert(startNodeId);

    while (!pending.empty()) {
        const std::string currentNodeId = pending.front();
        pending.pop();

        const NetworkNode* currentNode = findNode(currentNodeId);
        if (currentNode != nullptr) {
            traversal.push_back(currentNode);
        }

        for (const NetworkEdge* edge : getOutgoingEdges(currentNodeId)) {
            if (visited.insert(edge->getToNodeId()).second) {
                pending.push(edge->getToNodeId());
            }
        }
    }

    return traversal;
}

std::size_t Network::getNodeCount() const {
    return nodes_.size();
}

std::size_t Network::getEdgeCount() const {
    return edges_.size();
}

std::size_t Network::getRelationshipCount() const {
    return edgeIndexesByRelationship_.size();
}

void Network::requireKnownNode(const std::string& nodeId) const {
    if (nodeIndexById_.find(nodeId) == nodeIndexById_.end()) {
        throw std::invalid_argument("Unknown network node id: " + nodeId);
    }
}
