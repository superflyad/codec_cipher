#pragma once

#include "Cube.h"

#include <cstddef>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

struct CubeHierarchyEntry {
    std::string cubeId;
    std::optional<std::string> parentCubeId;
    std::size_t depth;
};

class NestedCubeContainer {
public:
    Cube& addRootCube(const std::string& cubeId);
    Cube& addChildCube(const std::string& parentCubeId, const std::string& cubeId);

    const Cube* findCube(const std::string& cubeId) const;
    Cube* findCube(const std::string& cubeId);
    std::optional<std::string> getParentCubeId(const std::string& cubeId) const;
    std::vector<const Cube*> getChildCubes(const std::string& cubeId) const;
    std::size_t getCubeDepth(const std::string& cubeId) const;
    std::vector<const Cube*> traverseFrom(const std::string& cubeId) const;
    std::vector<CubeHierarchyEntry> inspectHierarchy() const;

    std::size_t getCubeCount() const;
    std::size_t getRootCubeCount() const;

private:
    std::vector<Cube> cubes_;
    std::unordered_map<std::string, std::size_t> cubeIndexById_;
    std::unordered_map<std::string, std::string> parentByCubeId_;
    std::unordered_map<std::string, std::vector<std::string>> childrenByCubeId_;

    Cube& addCube(const std::optional<std::string>& parentCubeId, const std::string& cubeId);
    void requireKnownCube(const std::string& cubeId) const;
};
