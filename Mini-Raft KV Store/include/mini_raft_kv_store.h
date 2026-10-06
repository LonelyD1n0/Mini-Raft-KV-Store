#pragma once

#include <optional>
#include <string>
#include <unordered_map>
// #include <iostream>

class MiniRaftKVStore {
public:
    bool Put(const std::string& key, const std::string& value);

    std::optional<std::string> Get(const std::string& key) const;

    bool Delete(const std::string& key);

private:
    std::unordered_map<std::string, std::string> kv_map_;
};