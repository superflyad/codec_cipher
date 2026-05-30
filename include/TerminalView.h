#pragma once

#include "DimensionalObject.h"
#include "Laboratory.h"

#include <cstddef>
#include <string>

class TerminalView {
public:
    void renderMenu() const;
    void displayObjectInformation(const DimensionalObject& object) const;
    void displayClassification(const DimensionalObject& object) const;
    void displayBinaryVertexLabels(const DimensionalObject& object) const;
    void displayObjectList(const Laboratory& laboratory) const;
    void displayMessage(const std::string& message) const;

private:
    static std::string toBinaryLabel(std::size_t value, std::size_t width);
    static std::size_t labelWidth(std::size_t vertexCount);
};
