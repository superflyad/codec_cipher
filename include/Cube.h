#pragma once

#include <array>
#include <cstddef>
#include <string>
#include <vector>

struct CubeVertex {
    std::size_t index;
    std::array<int, 3> coordinates;
    std::string label;
};

struct CubeEdge {
    std::size_t fromVertexIndex;
    std::size_t toVertexIndex;
};

struct CubeMetrics {
    std::size_t vertexCount;
    std::size_t edgeCount;
    std::size_t dimensionCount;
};

class Cube {
public:
    explicit Cube(std::string id);

    const std::string& getId() const;
    const std::vector<CubeVertex>& getVertices() const;
    const std::vector<CubeEdge>& getEdges() const;
    const CubeVertex* findVertexByLabel(const std::string& label) const;
    CubeMetrics getMetrics() const;
    std::vector<std::string> inspectVertexLabels() const;
    std::vector<std::string> inspectEdgeLabels() const;

private:
    std::string id_;
    std::vector<CubeVertex> vertices_;
    std::vector<CubeEdge> edges_;

    static std::vector<CubeVertex> generateVertices();
    static std::vector<CubeEdge> generateEdges();
    static std::string createVertexLabel(const std::array<int, 3>& coordinates);
};
