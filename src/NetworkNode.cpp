#include "NetworkNode.h"

#include <utility>

NetworkNode::NetworkNode(std::string id, std::string label)
    : id_(std::move(id)), label_(std::move(label)) {}

NetworkNode::NetworkNode(std::string id, std::string label, std::vector<double> values)
    : id_(std::move(id)), label_(std::move(label)), values_(std::move(values)) {}

const std::string& NetworkNode::getId() const {
    return id_;
}

const std::string& NetworkNode::getLabel() const {
    return label_;
}

const std::vector<double>& NetworkNode::getValues() const {
    return values_;
}
