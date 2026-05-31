#include "Edge.h"

#include <sstream>
#include <utility>

Edge::Edge(std::string id,
           std::string sourceNodeId,
           std::string targetNodeId,
           std::string relationshipType,
           double weight)
    : id_(std::move(id)),
      sourceNodeId_(std::move(sourceNodeId)),
      targetNodeId_(std::move(targetNodeId)),
      relationshipType_(std::move(relationshipType)),
      weight_(weight) {}

const std::string& Edge::getId() const {
    return id_;
}

const std::string& Edge::getSourceNodeId() const {
    return sourceNodeId_;
}

const std::string& Edge::getTargetNodeId() const {
    return targetNodeId_;
}

const std::string& Edge::getRelationshipType() const {
    return relationshipType_;
}

double Edge::getWeight() const {
    return weight_;
}

std::string Edge::getSummary() const {
    std::ostringstream stream;
    stream << "Edge[" << id_ << "] " << sourceNodeId_
           << " -> " << targetNodeId_
           << " type=" << relationshipType_
           << " weight=" << weight_;
    return stream.str();
}
