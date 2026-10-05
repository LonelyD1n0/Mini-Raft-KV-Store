#include "mini_raft_kv_store.h"

bool MiniRaftKVStore::Put(const std::string& key, const std::string& value) {
    kv_map_[key] = value;
    return true;// 此处另有插入失败情况未写
}

std::optional<std::string> MiniRaftKVStore::Get(const std::string& key) const {
    auto it = kv_map_.find(key);

    if (it == kv_map_.end()) {
        return std::nullopt;
    }

    return it->second;
}

bool MiniRaftKVStore::Delete(const std::string& key) {
    return kv_map_.erase(key) > 0;
}