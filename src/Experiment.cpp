#include "Experiment.h"

#include <stdexcept>
#include <utility>

namespace {

int delta(std::size_t left, std::size_t right) {
    return static_cast<int>(right) - static_cast<int>(left);
}

} // namespace

ExperimentSession::ExperimentSession(std::string id, std::string title, std::uint32_t baseSeed)
    : id_(std::move(id)), title_(std::move(title)), runSequenceManager_(baseSeed) {}

const std::string& ExperimentSession::getId() const {
    return id_;
}

const std::string& ExperimentSession::getTitle() const {
    return title_;
}

Network& ExperimentSession::getNetwork() {
    return network_;
}

const Network& ExperimentSession::getNetwork() const {
    return network_;
}

NestedCubeContainer& ExperimentSession::getNestedCubes() {
    return nestedCubes_;
}

const NestedCubeContainer& ExperimentSession::getNestedCubes() const {
    return nestedCubes_;
}

RunSequenceManager& ExperimentSession::getRunSequenceManager() {
    return runSequenceManager_;
}

const RunSequenceManager& ExperimentSession::getRunSequenceManager() const {
    return runSequenceManager_;
}

const ExperimentNote& ExperimentSession::addNote(const std::string& text) {
    notes_.push_back(ExperimentNote{notes_.size() + 1, text});
    return notes_.back();
}

const std::vector<ExperimentNote>& ExperimentSession::getNotes() const {
    return notes_;
}

ExperimentSession& ExperimentSessionManager::createSession(const std::string& id,
                                                           const std::string& title,
                                                           std::uint32_t baseSeed) {
    if (findSession(id) != nullptr) {
        throw std::invalid_argument("Duplicate experiment session id: " + id);
    }

    sessions_.emplace_back(id, title, baseSeed);
    return sessions_.back();
}

ExperimentSession* ExperimentSessionManager::findSession(const std::string& id) {
    for (auto& session : sessions_) {
        if (session.getId() == id) {
            return &session;
        }
    }

    return nullptr;
}

const ExperimentSession* ExperimentSessionManager::findSession(const std::string& id) const {
    for (const auto& session : sessions_) {
        if (session.getId() == id) {
            return &session;
        }
    }

    return nullptr;
}

const std::deque<ExperimentSession>& ExperimentSessionManager::listSessions() const {
    return sessions_;
}

ExperimentComparison ExperimentComparisonTools::compare(const ExperimentSession& left,
                                                        const ExperimentSession& right) {
    const RecoveryDifficultyEstimate leftDifficulty = ComplexityMetrics::estimateRecoveryDifficulty(
        left.getNetwork(), left.getNestedCubes(), left.getRunSequenceManager());
    const RecoveryDifficultyEstimate rightDifficulty = ComplexityMetrics::estimateRecoveryDifficulty(
        right.getNetwork(), right.getNestedCubes(), right.getRunSequenceManager());

    return ExperimentComparison{
        left.getId(),
        right.getId(),
        delta(left.getNetwork().getNodeCount(), right.getNetwork().getNodeCount()),
        delta(left.getNetwork().getEdgeCount(), right.getNetwork().getEdgeCount()),
        delta(left.getNestedCubes().getCubeCount(), right.getNestedCubes().getCubeCount()),
        rightDifficulty.score - leftDifficulty.score,
    };
}
