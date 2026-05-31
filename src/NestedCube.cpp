#include "NestedCube.h"

#include <queue>
#include <stdexcept>

Cube& NestedCubeContainer::addRootCube(const std::string& cubeId) {
    return addCube(std::nullopt, cubeId);
}

Cube& NestedCubeContainer::addChildCube(const std::string& parentCubeId, const std::string& cubeId) {
    requireKnownCube(parentCubeId);
    return addCube(parentCubeId, cubeId);
}

const Cube* NestedCubeContainer::findCube(const std::string& cubeId) const {
    const auto iterator = cubeIndexById_.find(cubeId);
    if (iterator == cubeIndexById_.end()) {
        return nullptr;
    }

    return &cubes_[iterator->second];
}

Cube* NestedCubeContainer::findCube(const std::string& cubeId) {
    const auto iterator = cubeIndexById_.find(cubeId);
    if (iterator == cubeIndexById_.end()) {
        return nullptr;
    }

    return &cubes_[iterator->second];
}

std::optional<std::string> NestedCubeContainer::getParentCubeId(const std::string& cubeId) const {
    requireKnownCube(cubeId);
    const auto iterator = parentByCubeId_.find(cubeId);
    if (iterator == parentByCubeId_.end()) {
        return std::nullopt;
    }

    return iterator->second;
}

std::vector<const Cube*> NestedCubeContainer::getChildCubes(const std::string& cubeId) const {
    requireKnownCube(cubeId);

    std::vector<const Cube*> children;
    const auto iterator = childrenByCubeId_.find(cubeId);
    if (iterator == childrenByCubeId_.end()) {
        return children;
    }

    for (const auto& childCubeId : iterator->second) {
        children.push_back(findCube(childCubeId));
    }

    return children;
}

std::size_t NestedCubeContainer::getCubeDepth(const std::string& cubeId) const {
    requireKnownCube(cubeId);

    std::size_t depth = 0;
    std::string currentCubeId = cubeId;
    auto parentIterator = parentByCubeId_.find(currentCubeId);

    while (parentIterator != parentByCubeId_.end()) {
        ++depth;
        currentCubeId = parentIterator->second;
        parentIterator = parentByCubeId_.find(currentCubeId);
    }

    return depth;
}

std::vector<const Cube*> NestedCubeContainer::traverseFrom(const std::string& cubeId) const {
    std::vector<const Cube*> traversal;
    if (findCube(cubeId) == nullptr) {
        return traversal;
    }

    std::queue<std::string> pending;
    pending.push(cubeId);

    while (!pending.empty()) {
        const std::string currentCubeId = pending.front();
        pending.pop();

        traversal.push_back(findCube(currentCubeId));

        const auto childrenIterator = childrenByCubeId_.find(currentCubeId);
        if (childrenIterator == childrenByCubeId_.end()) {
            continue;
        }

        for (const auto& childCubeId : childrenIterator->second) {
            pending.push(childCubeId);
        }
    }

    return traversal;
}

std::vector<CubeHierarchyEntry> NestedCubeContainer::inspectHierarchy() const {
    std::vector<CubeHierarchyEntry> entries;
    entries.reserve(cubes_.size());

    for (const auto& cube : cubes_) {
        entries.push_back(CubeHierarchyEntry{cube.getId(), getParentCubeId(cube.getId()), getCubeDepth(cube.getId())});
    }

    return entries;
}

std::size_t NestedCubeContainer::getCubeCount() const {
    return cubes_.size();
}

std::size_t NestedCubeContainer::getRootCubeCount() const {
    return cubes_.size() - parentByCubeId_.size();
}

Cube& NestedCubeContainer::addCube(const std::optional<std::string>& parentCubeId, const std::string& cubeId) {
    if (cubeIndexById_.find(cubeId) != cubeIndexById_.end()) {
        throw std::invalid_argument("Duplicate cube id: " + cubeId);
    }

    cubes_.emplace_back(cubeId);
    cubeIndexById_[cubeId] = cubes_.size() - 1;

    if (parentCubeId.has_value()) {
        parentByCubeId_[cubeId] = parentCubeId.value();
        childrenByCubeId_[parentCubeId.value()].push_back(cubeId);
    }

    return cubes_.back();
}

void NestedCubeContainer::requireKnownCube(const std::string& cubeId) const {
    if (cubeIndexById_.find(cubeId) == cubeIndexById_.end()) {
        throw std::invalid_argument("Unknown cube id: " + cubeId);
    }
}
