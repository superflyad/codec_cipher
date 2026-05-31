#pragma once

#include <cstddef>
#include <string>

class Node {
public:
    Node(std::string id, std::string label, double numericValue, std::size_t depth);

    const std::string& getId() const;
    const std::string& getLabel() const;
    double getNumericValue() const;
    std::size_t getDepth() const;

    std::string getSummary() const;

private:
    std::string id_;
    std::string label_;
    double numericValue_;
    std::size_t depth_;
};
