#pragma once

#include <string>
#include <vector>

class NetworkNode {
public:
    NetworkNode(std::string id, std::string label);
    NetworkNode(std::string id, std::string label, std::vector<double> values);

    const std::string& getId() const;
    const std::string& getLabel() const;
    const std::vector<double>& getValues() const;

private:
    std::string id_;
    std::string label_;
    std::vector<double> values_;
};
