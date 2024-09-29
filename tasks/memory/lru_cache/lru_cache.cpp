#include "lru_cache.h"

LruCache::LruCache(size_t max_size) {
    vec_ = new std::vector<TItem>(max_size);
    accesscnt_ = 0;
    itcnt_ = 0;
}

LruCache::~LruCache() {
    delete vec_;
}

void LruCache::Set(const std::string& key, const std::string& value) {
    int i;

    // ищем с таким же ключом
    i = -1;
    for (size_t j = 0; j < itcnt_; j++) {
        if (vec_->at(j).key == key) {
            i = j;
            break;
        }
    }

    if (i == -1) {
        // Такого ключа нет
        if (itcnt_ < vec_->capacity()) {
            // Место есть
            i = itcnt_;
            itcnt_++;
        } else {
            // Места нет
            // ищем минимум
            int mincnt;
            i = 0;
            mincnt = vec_->at(0).cnt;
            for (size_t j = 1; j < itcnt_; j++) {
                if (mincnt > vec_->at(j).cnt) {
                    mincnt = vec_->at(j).cnt;
                }
            }
        }
    }

    vec_->at(i).key = key;
    vec_->at(i).val = value;
    accesscnt_++;
    vec_->at(i).cnt = accesscnt_;
}

bool LruCache::Get(const std::string& key, std::string* value) {
    int i;
    i = -1;
    for (size_t j = 0; j < itcnt_; j++) {
        if (vec_->at(j).key == key) {
            i = j;
            break;
        }
    }

    if (i == -1) {
        return false;  // ключа нет
    }

    // ключ есть
    *value = vec_->at(i).val;
    accesscnt_++;
    vec_->at(i).cnt = accesscnt_;
    return true;
}
