#pragma once

#include <string>

class NetworkEdge {
public:
    NetworkEdge(std::string id, std::string fromNodeId, std::string toNodeId, std::string relationship);

    const std::string& getId() const;
    const std::string& getFromNodeId() const;
    const std::string& getToNodeId() const;
    const std::string& getRelationship() const;

private:
    std::string id_;
    std::string fromNodeId_;
    std::string toNodeId_;
    std::string relationship_;
};
