#include <cassert>
#include <string>
#include <thread>
#include <vector>

#include "mini_raft_kv_store.h"

int main() {
    MiniRaftKVStore store;

    constexpr int thread_count = 8;
    constexpr int keys_per_thread = 1000;

    std::vector<std::thread> threads;

    for (int thread_id = 0;
        thread_id < thread_count;
        ++thread_id) {

        threads.emplace_back([&store, thread_id]() {
            for (int i = 0; i < keys_per_thread; ++i) {
                std::string key =
                    std::to_string(thread_id) + "-" +
                    std::to_string(i);

                store.Put(key, "value");
            }
            });
    }

    for (auto& thread : threads) {
        thread.join();
    }

    for (int thread_id = 0;
        thread_id < thread_count;
        ++thread_id) {

        for (int i = 0; i < keys_per_thread; ++i) {
            std::string key =
                std::to_string(thread_id) + "-" +
                std::to_string(i);

            auto result = store.Get(key);

            assert(result.has_value());
            assert(result.value() == "value");
        }
    }
}