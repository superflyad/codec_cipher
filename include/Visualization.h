#pragma once

#include "NestedCube.h"
#include "Network.h"
#include "RunEngine.h"

#include <string>

class AsciiVisualization {
public:
    static std::string renderNetwork(const Network& network);
    static std::string renderNestedCubes(const NestedCubeContainer& nestedCubes);
    static std::string renderRunTimeline(const RunSequenceManager& runSequenceManager);

private:
    static void renderCubeBranch(const NestedCubeContainer& nestedCubes,
                                 const std::string& cubeId,
                                 std::size_t depth,
                                 std::string& output);
};

class SvgExportPrototype {
public:
    static std::string renderNetwork(const Network& network);
};
