#include "cow_vector.h"

COWVector::COWVector() {
    state_ = new State();
    state_->ref_count = 0;
    state_->data = new std::vector<std::string>();
}

COWVector::~COWVector() {
    if (state_->ref_count == 0) {
        state_->data->clear();
        delete state_->data;
        delete state_;
    } else {
        state_->ref_count--;
    }
}

COWVector::COWVector(const COWVector& other) {
    state_ = other.state_;
    state_->ref_count++;
}

COWVector& COWVector::operator=(const COWVector& other) {
    if (state_ != other.state_) {
        if (state_->ref_count == 0) {
            state_->data->clear();
            delete state_->data;
            delete state_;
        } else {
            state_->ref_count--;
        }
        state_ = other.state_;
        state_->ref_count++;
    }
    return *this;
}

size_t COWVector::Size() const {
    return state_->data->size();
}

void COWVector::Resize(size_t size) {
    Refresh();
    state_->data->resize(size);
}

const std::string& COWVector::Get(size_t at) {
    return state_->data->at(at);
}

const std::string& COWVector::Back() {
    return state_->data->back();
}

void COWVector::PushBack(const std::string& value) {
    Refresh();
    state_->data->push_back(value);
}

void COWVector::Set(size_t at, const std::string& value) {
    Refresh();
    state_->data->at(at) = value;
}

void COWVector::Refresh() {
    if (state_->ref_count > 0) {
        state_->ref_count--;
        std::vector<std::string>* new_data = new std::vector<std::string>(*state_->data);
        state_ = new State();
        state_->ref_count = 0;
        state_->data = new_data;
    }
}
