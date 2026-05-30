#include "Laboratory.h"

DimensionalObject& Laboratory::createObject(const std::string& name, const std::vector<double>& values) {
    objects_.emplace_back(name, values);
    currentIndex_ = objects_.size() - 1;
    return objects_.back();
}

DimensionalObject& Laboratory::addObject(const DimensionalObject& object) {
    objects_.push_back(object);
    currentIndex_ = objects_.size() - 1;
    return objects_.back();
}

DimensionalObject* Laboratory::getCurrentObject() {
    if (!currentIndex_ || *currentIndex_ >= objects_.size()) {
        return nullptr;
    }

    return &objects_[*currentIndex_];
}

const DimensionalObject* Laboratory::getCurrentObject() const {
    if (!currentIndex_ || *currentIndex_ >= objects_.size()) {
        return nullptr;
    }

    return &objects_[*currentIndex_];
}

const std::vector<DimensionalObject>& Laboratory::listObjects() const {
    return objects_;
}

const DimensionalObject* Laboratory::inspectObject(std::size_t index) const {
    if (index >= objects_.size()) {
        return nullptr;
    }

    return &objects_[index];
}

bool Laboratory::setCurrentObject(std::size_t index) {
    if (index >= objects_.size()) {
        return false;
    }

    currentIndex_ = index;
    return true;
}
