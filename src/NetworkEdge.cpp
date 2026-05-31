#include "NetworkEdge.h"

#include <utility>

NetworkEdge::NetworkEdge(std::string id, std::string fromNodeId, std::string toNodeId, std::string relationship)
    : id_(std::move(id)),
      fromNodeId_(std::move(fromNodeId)),
      toNodeId_(std::move(toNodeId)),
      relationship_(std::move(relationship)) {}

const std::string& NetworkEdge::getId() const {
    return id_;
}

const std::string& NetworkEdge::getFromNodeId() const {
    return fromNodeId_;
}

const std::string& NetworkEdge::getToNodeId() const {
    return toNodeId_;
}

const std::string& NetworkEdge::getRelationship() const {
    return relationship_;
}
