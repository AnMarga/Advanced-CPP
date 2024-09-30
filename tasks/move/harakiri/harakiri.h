#pragma once

#include <string>

// Should not allow reuse and yell under sanitizers.
// Fix the interface and implementation.
// AwesomeCallback should add "awesomeness".
class OneTimeCallback {
public:
    virtual ~OneTimeCallback() = default;
    virtual std::string operator()() const&& = 0;
};

// Implement ctor, operator(), maybe something else...
class AwesomeCallback : public OneTimeCallback {
public:
    // AwesomeCallback(std::string s) : data_(std::move(s)), data_ptr_(&data_) {
    // }
    AwesomeCallback(std::string s) : data_(std::move(s)) {
    }

    std::string operator()() const&& {
        // auto result = *data_ptr_ + "awesomeness";
        // data_ptr_ = nullptr;
        auto result = data_ + "awesomeness";
        delete this;  //
        return result;
    }

private:
    mutable std::string data_;  // const
    // mutable const std::string* data_ptr_;
};
