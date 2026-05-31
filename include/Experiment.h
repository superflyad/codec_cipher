#pragma once

#include "ComplexityMetrics.h"
#include "NestedCube.h"
#include "Network.h"
#include "RunEngine.h"

#include <cstdint>
#include <deque>
#include <string>
#include <vector>

struct ExperimentNote {
    std::size_t index;
    std::string text;
};

struct ExperimentComparison {
    std::string leftSessionId;
    std::string rightSessionId;
    int nodeDelta;
    int edgeDelta;
    int cubeDelta;
    double recoveryDifficultyDelta;
};

class ExperimentSession {
public:
    ExperimentSession(std::string id, std::string title, std::uint32_t baseSeed = 1);

    const std::string& getId() const;
    const std::string& getTitle() const;
    Network& getNetwork();
    const Network& getNetwork() const;
    NestedCubeContainer& getNestedCubes();
    const NestedCubeContainer& getNestedCubes() const;
    RunSequenceManager& getRunSequenceManager();
    const RunSequenceManager& getRunSequenceManager() const;

    const ExperimentNote& addNote(const std::string& text);
    const std::vector<ExperimentNote>& getNotes() const;

private:
    std::string id_;
    std::string title_;
    Network network_;
    NestedCubeContainer nestedCubes_;
    RunSequenceManager runSequenceManager_;
    std::vector<ExperimentNote> notes_;
};

class ExperimentSessionManager {
public:
    ExperimentSession& createSession(const std::string& id, const std::string& title, std::uint32_t baseSeed = 1);
    ExperimentSession* findSession(const std::string& id);
    const ExperimentSession* findSession(const std::string& id) const;
    const std::deque<ExperimentSession>& listSessions() const;

private:
    std::deque<ExperimentSession> sessions_;
};

class ExperimentComparisonTools {
public:
    static ExperimentComparison compare(const ExperimentSession& left, const ExperimentSession& right);
};
