#include "Cube.h"

#include <sstream>
#include <utility>

Cube::Cube(std::string id)
    : id_(std::move(id)), vertices_(generateVertices()), edges_(generateEdges()) {}

const std::string& Cube::getId() const {
    return id_;
}

const std::vector<CubeVertex>& Cube::getVertices() const {
    return vertices_;
}

const std::vector<CubeEdge>& Cube::getEdges() const {
    return edges_;
}

const CubeVertex* Cube::findVertexByLabel(const std::string& label) const {
    for (const auto& vertex : vertices_) {
        if (vertex.label == label) {
            return &vertex;
        }
    }

    return nullptr;
}

CubeMetrics Cube::getMetrics() const {
    return CubeMetrics{vertices_.size(), edges_.size(), 3};
}

std::vector<std::string> Cube::inspectVertexLabels() const {
    std::vector<std::string> labels;
    labels.reserve(vertices_.size());

    for (const auto& vertex : vertices_) {
        labels.push_back(vertex.label);
    }

    return labels;
}

std::vector<std::string> Cube::inspectEdgeLabels() const {
    std::vector<std::string> labels;
    labels.reserve(edges_.size());

    for (const auto& edge : edges_) {
        std::ostringstream stream;
        stream << vertices_[edge.fromVertexIndex].label << "->" << vertices_[edge.toVertexIndex].label;
        labels.push_back(stream.str());
    }

    return labels;
}

std::vector<CubeVertex> Cube::generateVertices() {
    std::vector<CubeVertex> vertices;
    vertices.reserve(8);

    for (std::size_t index = 0; index < 8; ++index) {
        const std::array<int, 3> coordinates{
            static_cast<int>((index >> 2) & 1),
            static_cast<int>((index >> 1) & 1),
            static_cast<int>(index & 1),
        };

        vertices.push_back(CubeVertex{index, coordinates, createVertexLabel(coordinates)});
    }

    return vertices;
}

std::vector<CubeEdge> Cube::generateEdges() {
    std::vector<CubeEdge> edges;
    edges.reserve(12);

    for (std::size_t fromIndex = 0; fromIndex < 8; ++fromIndex) {
        for (std::size_t dimension = 0; dimension < 3; ++dimension) {
            const std::size_t toIndex = fromIndex ^ (std::size_t{1} << dimension);
            if (fromIndex < toIndex) {
                edges.push_back(CubeEdge{fromIndex, toIndex});
            }
        }
    }

    return edges;
}

std::string Cube::createVertexLabel(const std::array<int, 3>& coordinates) {
    std::ostringstream stream;
    stream << coordinates[0] << coordinates[1] << coordinates[2];
    return stream.str();
}
