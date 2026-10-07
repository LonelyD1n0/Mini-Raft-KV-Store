#pragma once

#include <optional>
#include <string>
#include <unordered_map>
#include <mutex>
// #include <iostream>

class MiniRaftKVStore {
public:
    bool Put(const std::string& key, const std::string& value);// 插入键值

    std::optional<std::string> Get(const std::string& key) const;// 获取键值

    bool Delete(const std::string& key);// 删除键值

private:
    std::unordered_map<std::string, std::string> kv_map_;// 使用unordered_map存放键值

    mutable std::mutex mutex_;// 互斥锁
};