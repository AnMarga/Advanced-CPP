#pragma once

#include <string>
#include <vector>

class LruCache {
public:
    LruCache(size_t max_size);
    ~LruCache();

    void Set(const std::string& key, const std::string& value);

    bool Get(const std::string& key, std::string* value);

private:
    typedef struct {
        std::string key;
        std::string val;
        int cnt;
    } TItem;

    std::vector<TItem>* vec_;
    int accesscnt_;
    size_t itcnt_;
};
