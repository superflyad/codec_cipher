#pragma once

#include <string>

class Edge {
public:
    Edge(std::string id,
         std::string sourceNodeId,
         std::string targetNodeId,
         std::string relationshipType,
         double weight);

    const std::string& getId() const;
    const std::string& getSourceNodeId() const;
    const std::string& getTargetNodeId() const;
    const std::string& getRelationshipType() const;
    double getWeight() const;

    std::string getSummary() const;

private:
    std::string id_;
    std::string sourceNodeId_;
    std::string targetNodeId_;
    std::string relationshipType_;
    double weight_;
};
