#pragma once

#include <cstddef>
#include <string>
#include <vector>

class DimensionalObject {
public:
    DimensionalObject(std::string name, std::vector<double> values);
    DimensionalObject(std::string name, std::string creationTimestamp, std::vector<double> values);

    const std::string& getName() const;
    const std::string& getCreationTimestamp() const;
    const std::vector<double>& getValues() const;
    std::size_t getDimensionCount() const;
    const std::string& getClassification() const;

    static std::string classify(const std::vector<double>& values);

private:
    std::string name_;
    std::string creationTimestamp_;
    std::vector<double> values_;
    std::string classification_;

    static std::string createTimestamp();
    static bool isPowerOfTwo(std::size_t value);
};
