#include "RunEngine.h"

#include <stdexcept>
#include <utility>

ReplayEngine::ReplayEngine(std::vector<Run> runs) : runs_(std::move(runs)) {}

std::vector<NetworkSnapshot> ReplayEngine::replayAll() const {
    std::vector<NetworkSnapshot> snapshots;
    snapshots.reserve(runs_.size());

    for (const auto& run : runs_) {
        snapshots.push_back(run.snapshot);
    }

    return snapshots;
}

std::optional<NetworkSnapshot> ReplayEngine::replayTo(std::size_t runNumber) const {
    for (const auto& run : runs_) {
        if (run.number == runNumber) {
            return run.snapshot;
        }
    }

    return std::nullopt;
}

RunSequenceManager::RunSequenceManager(std::uint32_t baseSeed) : baseSeed_(baseSeed) {}

const Run& RunSequenceManager::recordRun(const std::string& label,
                                         const Network& network,
                                         const NestedCubeContainer& nestedCubes) {
    const std::size_t runNumber = runs_.size() + 1;
    const std::uint32_t seed = seedForRun(runNumber);
    NetworkSnapshot snapshot{runNumber, seed, label, network, nestedCubes};
    runs_.push_back(Run{runNumber, seed, label, snapshot});
    return runs_.back();
}

const std::vector<Run>& RunSequenceManager::getRuns() const {
    return runs_;
}

const Run* RunSequenceManager::findRun(std::size_t runNumber) const {
    for (const auto& run : runs_) {
        if (run.number == runNumber) {
            return &run;
        }
    }

    return nullptr;
}

std::vector<RunHistoryEntry> RunSequenceManager::getHistory() const {
    std::vector<RunHistoryEntry> history;
    history.reserve(runs_.size());

    for (const auto& run : runs_) {
        history.push_back(RunHistoryEntry{
            run.number,
            run.seed,
            run.label,
            run.snapshot.network.getNodeCount(),
            run.snapshot.network.getEdgeCount(),
            run.snapshot.nestedCubes.getCubeCount(),
        });
    }

    return history;
}

ReplayEngine RunSequenceManager::createReplayEngine() const {
    return ReplayEngine(runs_);
}

std::uint32_t RunSequenceManager::getBaseSeed() const {
    return baseSeed_;
}

std::uint32_t RunSequenceManager::previewSeedForRun(std::size_t runNumber) const {
    if (runNumber == 0) {
        throw std::invalid_argument("Run number must be greater than zero.");
    }

    return seedForRun(runNumber);
}

std::uint32_t RunSequenceManager::seedForRun(std::size_t runNumber) const {
    return baseSeed_ + static_cast<std::uint32_t>((runNumber - 1) * 2654435761u);
}
