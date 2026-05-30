#pragma once

#include "DimensionalObject.h"

#include <filesystem>
#include <optional>
#include <string>

class Persistence {
public:
    explicit Persistence(std::filesystem::path saveDirectory = "saves");

    std::filesystem::path saveObject(const DimensionalObject& object) const;
    std::optional<DimensionalObject> loadObject(const std::filesystem::path& path) const;
    const std::filesystem::path& getSaveDirectory() const;

private:
    std::filesystem::path saveDirectory_;

    static std::string sanitizeFilename(const std::string& name);
};
