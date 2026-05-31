#include "Node.h"

#include <sstream>
#include <utility>

Node::Node(std::string id, std::string label, double numericValue, std::size_t depth)
    : id_(std::move(id)),
      label_(std::move(label)),
      numericValue_(numericValue),
      depth_(depth) {}

const std::string& Node::getId() const {
    return id_;
}

const std::string& Node::getLabel() const {
    return label_;
}

double Node::getNumericValue() const {
    return numericValue_;
}

std::size_t Node::getDepth() const {
    return depth_;
}

std::string Node::getSummary() const {
    std::ostringstream stream;
    stream << "Node[" << id_ << "] " << label_
           << " value=" << numericValue_
           << " depth=" << depth_;
    return stream.str();
}
