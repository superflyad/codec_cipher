#include "DimensionalObject.h"

#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <utility>

DimensionalObject::DimensionalObject(std::string name, std::vector<double> values)
    : name_(std::move(name)),
      creationTimestamp_(createTimestamp()),
      values_(std::move(values)),
      classification_(classify(values_)) {}

DimensionalObject::DimensionalObject(std::string name, std::string creationTimestamp, std::vector<double> values)
    : name_(std::move(name)),
      creationTimestamp_(std::move(creationTimestamp)),
      values_(std::move(values)),
      classification_(classify(values_)) {}

const std::string& DimensionalObject::getName() const {
    return name_;
}

const std::string& DimensionalObject::getCreationTimestamp() const {
    return creationTimestamp_;
}

const std::vector<double>& DimensionalObject::getValues() const {
    return values_;
}

std::size_t DimensionalObject::getDimensionCount() const {
    return values_.size();
}

const std::string& DimensionalObject::getClassification() const {
    return classification_;
}

std::string DimensionalObject::classify(const std::vector<double>& values) {
    const std::size_t count = values.size();

    if (count == 4) {
        return "Square";
    }

    if (count == 8) {
        return "Cube";
    }

    if (count >= 16 && isPowerOfTwo(count)) {
        return "Hyperdimensional Object";
    }

    return "Unstable Object";
}

std::string DimensionalObject::createTimestamp() {
    const auto now = std::chrono::system_clock::now();
    const std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
    std::tm localTime{};

#if defined(_WIN32)
    localtime_s(&localTime, &currentTime);
#else
    localtime_r(&currentTime, &localTime);
#endif

    std::ostringstream stream;
    stream << std::put_time(&localTime, "%Y-%m-%d %H:%M:%S");
    return stream.str();
}

bool DimensionalObject::isPowerOfTwo(std::size_t value) {
    return value != 0 && (value & (value - 1)) == 0;
}
