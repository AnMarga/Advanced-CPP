#pragma once

#include <cstdint>
#include <string>
#include <vector>

struct State {
    int ref_count;
    std::vector<std::string>* data;
};

class COWVector {
public:
    COWVector();
    ~COWVector();

    COWVector(const COWVector& other);
    COWVector& operator=(const COWVector& other);

    // Rule of 5?

    size_t Size() const;

    void Resize(size_t size);

    const std::string& Get(size_t at);
    const std::string& Back();

    void PushBack(const std::string& value);

    void Set(size_t at, const std::string& value);

private:
    State* state_;

    void Refresh();
};
