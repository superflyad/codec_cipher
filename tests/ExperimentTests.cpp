#include "Experiment.h"

#include "Refinement.h"

#include <cassert>
#include <stdexcept>

namespace {

void populateBaseline(ExperimentSession& session) {
    session.getNetwork().addNode("root", "Root");
    session.getNestedCubes().addRootCube("cube-root");
    session.getRunSequenceManager().recordRun("baseline", session.getNetwork(), session.getNestedCubes());
}

void testExperimentSessionManagerAndNotes() {
    ExperimentSessionManager manager;
    ExperimentSession& session = manager.createSession("exp-1", "First Experiment", 11);
    populateBaseline(session);
    const ExperimentNote& note = session.addNote("Baseline network and cube created.");

    assert(manager.listSessions().size() == 1);
    assert(manager.findSession("exp-1") != nullptr);
    assert(manager.findSession("missing") == nullptr);
    assert(session.getTitle() == "First Experiment");
    assert(session.getRunSequenceManager().getBaseSeed() == 11);
    assert(note.index == 1);
    assert(session.getNotes().size() == 1);

    bool duplicateRejected = false;
    try {
        manager.createSession("exp-1", "Duplicate");
    } catch (const std::invalid_argument&) {
        duplicateRejected = true;
    }
    assert(duplicateRejected);
}

void testExperimentComparisonTools() {
    ExperimentSession left("left", "Left", 1);
    ExperimentSession right("right", "Right", 1);
    populateBaseline(left);
    populateBaseline(right);

    RefinementOperations::refineNode(right.getNetwork(), "root", "child", "Child", "edge-1");
    RefinementOperations::refineCube(right.getNestedCubes(), "cube-root", "cube-child");
    right.getRunSequenceManager().recordRun("expanded", right.getNetwork(), right.getNestedCubes());

    const ExperimentComparison comparison = ExperimentComparisonTools::compare(left, right);

    assert(comparison.leftSessionId == "left");
    assert(comparison.rightSessionId == "right");
    assert(comparison.nodeDelta == 1);
    assert(comparison.edgeDelta == 1);
    assert(comparison.cubeDelta == 1);
    assert(comparison.recoveryDifficultyDelta > 0.0);
}

} // namespace

int main() {
    testExperimentSessionManagerAndNotes();
    testExperimentComparisonTools();
    return 0;
}
