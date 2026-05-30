#pragma once

#include "DimensionalObject.h"

#include <cstddef>
#include <optional>
#include <vector>

class Laboratory {
public:
    DimensionalObject& createObject(const std::string& name, const std::vector<double>& values);
    DimensionalObject& addObject(const DimensionalObject& object);

    DimensionalObject* getCurrentObject();
    const DimensionalObject* getCurrentObject() const;

    const std::vector<DimensionalObject>& listObjects() const;
    const DimensionalObject* inspectObject(std::size_t index) const;
    bool setCurrentObject(std::size_t index);

private:
    std::vector<DimensionalObject> objects_;
    std::optional<std::size_t> currentIndex_;
};
