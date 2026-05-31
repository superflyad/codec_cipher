#include "Edge.h"
#include "Laboratory.h"
#include "Node.h"
#include "Persistence.h"
#include "TerminalView.h"

#include <exception>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>

namespace {
std::string readLine(const std::string& prompt) {
    std::cout << prompt;
    std::string value;
    std::getline(std::cin, value);
    return value;
}

std::vector<double> readValues() {
    while (true) {
        const std::string line = readLine("Enter numeric values separated by spaces: ");
        std::istringstream stream(line);
        std::vector<double> values;
        double value = 0.0;

        while (stream >> value) {
            values.push_back(value);
        }

        if (!values.empty() && stream.eof()) {
            return values;
        }

        std::cout << "Please enter at least one valid numeric value.\n";
    }
}

int readMenuChoice() {
    int choice = 0;
    if (!(std::cin >> choice)) {
        std::cin.clear();
        choice = 0;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return choice;
}

void createObject(Laboratory& laboratory, const TerminalView& view) {
    const std::string name = readLine("Object name: ");
    if (name.empty()) {
        view.displayMessage("Object names cannot be empty.");
        return;
    }

    DimensionalObject& object = laboratory.createObject(name, readValues());
    view.displayMessage("Created object.");
    view.displayObjectInformation(object);
}

void inspectCurrentObject(const Laboratory& laboratory, const TerminalView& view) {
    const DimensionalObject* object = laboratory.getCurrentObject();
    if (object == nullptr) {
        view.displayMessage("No current object is available.");
        return;
    }

    view.displayObjectInformation(*object);
}

void saveCurrentObject(const Laboratory& laboratory, const Persistence& persistence, const TerminalView& view) {
    const DimensionalObject* object = laboratory.getCurrentObject();
    if (object == nullptr) {
        view.displayMessage("No current object is available to save.");
        return;
    }

    try {
        const auto savePath = persistence.saveObject(*object);
        view.displayMessage("Saved object to " + savePath.string());
    } catch (const std::exception& error) {
        view.displayMessage(std::string("Save failed: ") + error.what());
    }
}

void loadObject(Laboratory& laboratory, const Persistence& persistence, const TerminalView& view) {
    const std::string path = readLine("Load filename or path: ");
    if (path.empty()) {
        view.displayMessage("Load path cannot be empty.");
        return;
    }

    const auto loaded = persistence.loadObject(path);
    if (!loaded) {
        view.displayMessage("Load failed. Check the path and file format.");
        return;
    }

    DimensionalObject& object = laboratory.addObject(*loaded);
    view.displayMessage("Loaded object and set it as current.");
    view.displayObjectInformation(object);
}
} // namespace

int main() {
    Laboratory laboratory;
    Persistence persistence;
    TerminalView view;

    const Node exampleNode("node:origin", "Origin Signal", 1.0, 0);
    const Edge exampleEdge("edge:origin-self",
                           exampleNode.getId(),
                           exampleNode.getId(),
                           "self-reference",
                           1.0);
    view.displayMessage("Network primitive example:");
    view.displayMessage("  " + exampleNode.getSummary());
    view.displayMessage("  " + exampleEdge.getSummary());

    bool running = true;
    while (running) {
        view.renderMenu();
        switch (readMenuChoice()) {
        case 1:
            createObject(laboratory, view);
            break;
        case 2:
            inspectCurrentObject(laboratory, view);
            break;
        case 3:
            saveCurrentObject(laboratory, persistence, view);
            break;
        case 4:
            loadObject(laboratory, persistence, view);
            break;
        case 5:
            view.displayObjectList(laboratory);
            break;
        case 6:
            running = false;
            break;
        default:
            view.displayMessage("Unknown option. Choose 1 through 6.");
            break;
        }
    }

    view.displayMessage("Exiting Codec Cipher.");
    return 0;
}
