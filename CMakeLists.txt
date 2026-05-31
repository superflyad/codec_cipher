cmake_minimum_required(VERSION 3.16)

project(codec_cipher VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(codec_cipher
    app/main.cpp
    src/ComplexityMetrics.cpp
    src/Cube.cpp
    src/DimensionalObject.cpp
    src/Edge.cpp
    src/Experiment.cpp
    src/Laboratory.cpp
    src/Network.cpp
    src/NetworkEdge.cpp
    src/NetworkNode.cpp
    src/NetworkPersistence.cpp
    src/NestedCube.cpp
    src/Node.cpp
    src/Persistence.cpp
    src/Refinement.cpp
    src/RunEngine.cpp
    src/TerminalView.cpp
    src/Visualization.cpp
)

target_include_directories(codec_cipher PRIVATE include)

enable_testing()

add_executable(network_core_tests
    tests/NetworkCoreTests.cpp
    src/Network.cpp
    src/NetworkEdge.cpp
    src/NetworkNode.cpp
)

target_include_directories(network_core_tests PRIVATE include)

add_test(NAME network_core_tests COMMAND network_core_tests)

add_executable(cube_tests
    tests/CubeTests.cpp
    src/Cube.cpp
)

target_include_directories(cube_tests PRIVATE include)

add_test(NAME cube_tests COMMAND cube_tests)

add_executable(nested_cube_tests
    tests/NestedCubeTests.cpp
    src/Cube.cpp
    src/NestedCube.cpp
)

target_include_directories(nested_cube_tests PRIVATE include)

add_test(NAME nested_cube_tests COMMAND nested_cube_tests)

add_executable(run_engine_tests
    tests/RunEngineTests.cpp
    src/Cube.cpp
    src/NestedCube.cpp
    src/Network.cpp
    src/NetworkEdge.cpp
    src/NetworkNode.cpp
    src/RunEngine.cpp
)

target_include_directories(run_engine_tests PRIVATE include)

add_test(NAME run_engine_tests COMMAND run_engine_tests)

add_executable(refinement_tests
    tests/RefinementTests.cpp
    src/Cube.cpp
    src/NestedCube.cpp
    src/Network.cpp
    src/NetworkEdge.cpp
    src/NetworkNode.cpp
    src/Refinement.cpp
)

target_include_directories(refinement_tests PRIVATE include)

add_test(NAME refinement_tests COMMAND refinement_tests)

add_executable(visualization_tests
    tests/VisualizationTests.cpp
    src/Cube.cpp
    src/NestedCube.cpp
    src/Network.cpp
    src/NetworkEdge.cpp
    src/NetworkNode.cpp
    src/Refinement.cpp
    src/RunEngine.cpp
    src/Visualization.cpp
)

target_include_directories(visualization_tests PRIVATE include)

add_test(NAME visualization_tests COMMAND visualization_tests)

add_executable(network_persistence_tests
    tests/NetworkPersistenceTests.cpp
    src/Cube.cpp
    src/NestedCube.cpp
    src/Network.cpp
    src/NetworkEdge.cpp
    src/NetworkNode.cpp
    src/NetworkPersistence.cpp
    src/RunEngine.cpp
)

target_include_directories(network_persistence_tests PRIVATE include)

add_test(NAME network_persistence_tests COMMAND network_persistence_tests)

add_executable(complexity_metrics_tests
    tests/ComplexityMetricsTests.cpp
    src/ComplexityMetrics.cpp
    src/Cube.cpp
    src/NestedCube.cpp
    src/Network.cpp
    src/NetworkEdge.cpp
    src/NetworkNode.cpp
    src/RunEngine.cpp
)

target_include_directories(complexity_metrics_tests PRIVATE include)

add_test(NAME complexity_metrics_tests COMMAND complexity_metrics_tests)

add_executable(experiment_tests
    tests/ExperimentTests.cpp
    src/ComplexityMetrics.cpp
    src/Cube.cpp
    src/Experiment.cpp
    src/NestedCube.cpp
    src/Network.cpp
    src/NetworkEdge.cpp
    src/NetworkNode.cpp
    src/Refinement.cpp
    src/RunEngine.cpp
)

target_include_directories(experiment_tests PRIVATE include)

add_test(NAME experiment_tests COMMAND experiment_tests)

add_executable(v01_workflow_tests
    tests/V01WorkflowTests.cpp
    src/ComplexityMetrics.cpp
    src/Cube.cpp
    src/Experiment.cpp
    src/NestedCube.cpp
    src/Network.cpp
    src/NetworkEdge.cpp
    src/NetworkNode.cpp
    src/NetworkPersistence.cpp
    src/Refinement.cpp
    src/RunEngine.cpp
    src/Visualization.cpp
)

target_include_directories(v01_workflow_tests PRIVATE include)

add_test(NAME v01_workflow_tests COMMAND v01_workflow_tests)
