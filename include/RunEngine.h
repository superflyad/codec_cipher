#pragma once

#include "NestedCube.h"
#include "Network.h"

#include <cstdint>
#include <optional>
#include <string>
#include <vector>

struct NetworkSnapshot {
    std::size_t runNumber;
    std::uint32_t seed;
    std::string label;
    Network network;
    NestedCubeContainer nestedCubes;
};

struct Run {
    std::size_t number;
    std::uint32_t seed;
    std::string label;
    NetworkSnapshot snapshot;
};

struct RunHistoryEntry {
    std::size_t runNumber;
    std::uint32_t seed;
    std::string label;
    std::size_t nodeCount;
    std::size_t edgeCount;
    std::size_t cubeCount;
};

class ReplayEngine {
public:
    explicit ReplayEngine(std::vector<Run> runs);

    std::vector<NetworkSnapshot> replayAll() const;
    std::optional<NetworkSnapshot> replayTo(std::size_t runNumber) const;

private:
    std::vector<Run> runs_;
};

class RunSequenceManager {
public:
    explicit RunSequenceManager(std::uint32_t baseSeed = 1);

    const Run& recordRun(const std::string& label, const Network& network, const NestedCubeContainer& nestedCubes);
    const std::vector<Run>& getRuns() const;
    const Run* findRun(std::size_t runNumber) const;
    std::vector<RunHistoryEntry> getHistory() const;
    ReplayEngine createReplayEngine() const;

    std::uint32_t getBaseSeed() const;
    std::uint32_t previewSeedForRun(std::size_t runNumber) const;

private:
    std::uint32_t baseSeed_;
    std::vector<Run> runs_;

    std::uint32_t seedForRun(std::size_t runNumber) const;
};
