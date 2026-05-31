#pragma once

#include "RunEngine.h"

#include <filesystem>
#include <string>
#include <vector>

class NetworkPersistence {
public:
    static std::string serializeNetwork(const Network& network);
    static Network deserializeNetwork(const std::string& content);

    static std::string serializeSnapshot(const NetworkSnapshot& snapshot);
    static NetworkSnapshot deserializeSnapshot(const std::string& content);

    static std::string serializeRunSequence(const std::vector<Run>& runs);
    static ReplayEngine deserializeRunSequenceToReplay(const std::string& content);

    static void saveNetwork(const Network& network, const std::filesystem::path& filePath);
    static Network loadNetwork(const std::filesystem::path& filePath);

    static void saveSnapshot(const NetworkSnapshot& snapshot, const std::filesystem::path& filePath);
    static NetworkSnapshot loadSnapshot(const std::filesystem::path& filePath);

    static void saveRunSequence(const std::vector<Run>& runs, const std::filesystem::path& filePath);
    static ReplayEngine loadRunSequenceForReplay(const std::filesystem::path& filePath);
};
