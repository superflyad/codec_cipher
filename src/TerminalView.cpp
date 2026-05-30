#include "TerminalView.h"

#include <iostream>
#include <sstream>

void TerminalView::renderMenu() const {
    std::cout << "\n=== Codec Cipher Dimensional Laboratory ===\n"
              << "1. Create Object\n"
              << "2. Inspect Current Object\n"
              << "3. Save Current Object\n"
              << "4. Load Object\n"
              << "5. List Objects\n"
              << "6. Exit\n"
              << "Select an option: ";
}

void TerminalView::displayObjectInformation(const DimensionalObject& object) const {
    std::cout << "\nObject: " << object.getName() << '\n'
              << "Created: " << object.getCreationTimestamp() << '\n'
              << "Dimensions: " << object.getDimensionCount() << '\n';
    displayClassification(object);

    std::cout << "Values: ";
    const auto& values = object.getValues();
    for (std::size_t index = 0; index < values.size(); ++index) {
        if (index > 0) {
            std::cout << ", ";
        }
        std::cout << values[index];
    }
    std::cout << '\n';

    displayBinaryVertexLabels(object);
}

void TerminalView::displayClassification(const DimensionalObject& object) const {
    std::cout << "Classification: " << object.getClassification() << '\n';
}

void TerminalView::displayBinaryVertexLabels(const DimensionalObject& object) const {
    const auto& values = object.getValues();
    const std::size_t width = labelWidth(values.size());

    std::cout << "Binary vertex labels:\n";
    if (values.empty()) {
        std::cout << "  (no vertices)\n";
        return;
    }

    for (std::size_t index = 0; index < values.size(); ++index) {
        std::cout << "  " << toBinaryLabel(index, width) << " -> " << values[index] << '\n';
    }
}

void TerminalView::displayObjectList(const Laboratory& laboratory) const {
    const auto& objects = laboratory.listObjects();
    std::cout << "\nKnown objects:\n";
    if (objects.empty()) {
        std::cout << "  (none)\n";
        return;
    }

    for (std::size_t index = 0; index < objects.size(); ++index) {
        std::cout << "  [" << index << "] " << objects[index].getName()
                  << " - " << objects[index].getClassification()
                  << " (" << objects[index].getDimensionCount() << " values)\n";
    }
}

void TerminalView::displayMessage(const std::string& message) const {
    std::cout << message << '\n';
}

std::string TerminalView::toBinaryLabel(std::size_t value, std::size_t width) {
    std::string label(width, '0');
    for (std::size_t offset = 0; offset < width; ++offset) {
        const std::size_t bitIndex = width - offset - 1;
        if ((value & (static_cast<std::size_t>(1) << bitIndex)) != 0) {
            label[offset] = '1';
        }
    }
    return label;
}

std::size_t TerminalView::labelWidth(std::size_t vertexCount) {
    if (vertexCount <= 1) {
        return 1;
    }

    std::size_t width = 0;
    std::size_t value = vertexCount - 1;
    while (value > 0) {
        ++width;
        value >>= 1;
    }
    return width;
}
