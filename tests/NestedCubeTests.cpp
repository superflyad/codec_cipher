#include "NestedCube.h"

#include <cassert>
#include <stdexcept>

namespace {

void testNestedCubeContainerAndRelationships() {
    NestedCubeContainer container;
    container.addRootCube("root");
    container.addChildCube("root", "left");
    container.addChildCube("root", "right");
    container.addChildCube("left", "left-inner");

    assert(container.getCubeCount() == 4);
    assert(container.getRootCubeCount() == 1);
    assert(container.findCube("root") != nullptr);
    assert(container.findCube("missing") == nullptr);
    assert(container.getParentCubeId("root") == std::nullopt);
    assert(container.getParentCubeId("left").value() == "root");
    assert(container.getChildCubes("root").size() == 2);
    assert(container.getChildCubes("left").size() == 1);
}

void testDepthTrackingAndTraversal() {
    NestedCubeContainer container;
    container.addRootCube("root");
    container.addChildCube("root", "left");
    container.addChildCube("root", "right");
    container.addChildCube("left", "left-inner");

    assert(container.getCubeDepth("root") == 0);
    assert(container.getCubeDepth("left") == 1);
    assert(container.getCubeDepth("left-inner") == 2);

    const auto traversal = container.traverseFrom("root");
    assert(traversal.size() == 4);
    assert(traversal[0]->getId() == "root");
    assert(traversal[1]->getId() == "left");
    assert(traversal[2]->getId() == "right");
    assert(traversal[3]->getId() == "left-inner");
    assert(container.traverseFrom("missing").empty());
}

void testHierarchyInspectionAndValidation() {
    NestedCubeContainer container;
    container.addRootCube("root");
    container.addChildCube("root", "child");

    const auto entries = container.inspectHierarchy();
    assert(entries.size() == 2);
    assert(entries[0].cubeId == "root");
    assert(entries[0].depth == 0);
    assert(!entries[0].parentCubeId.has_value());
    assert(entries[1].cubeId == "child");
    assert(entries[1].depth == 1);
    assert(entries[1].parentCubeId.value() == "root");

    bool duplicateRejected = false;
    try {
        container.addRootCube("root");
    } catch (const std::invalid_argument&) {
        duplicateRejected = true;
    }
    assert(duplicateRejected);

    bool missingParentRejected = false;
    try {
        container.addChildCube("missing", "orphan");
    } catch (const std::invalid_argument&) {
        missingParentRejected = true;
    }
    assert(missingParentRejected);
}

} // namespace

int main() {
    testNestedCubeContainerAndRelationships();
    testDepthTrackingAndTraversal();
    testHierarchyInspectionAndValidation();
    return 0;
}
