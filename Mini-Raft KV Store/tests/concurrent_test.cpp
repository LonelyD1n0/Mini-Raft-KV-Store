#include <cassert>
#include <string>
#include <thread>
#include <vector>
#include <functional>

#include "mini_raft_kv_store.h"

int main() {
    MiniRaftKVStore store;

    int thread_num = 8;// 线程数量
    std::vector<std::thread> threads(thread_num);

    std::function<void(int)> thread_put;

    thread_put = [&](int i) {
        int cnt = 1000;
        while (cnt--) {
            std::string key = std::to_string(i) + "-" + std::to_string(cnt);
            std::string value = "value" + std::to_string(i);
            store.Put(key, value);
        }// 线程内部执行1000次写入

        //std::string key = std::to_string(i);
        //std::string value = "value" + std::to_string(i);
        //store.Put(key, value);
        };// 需要线程执行的函数

    int thread_id;// 线程id
    for (thread_id = 0; thread_id < thread_num; ++thread_id) {
        threads[thread_id] = std::thread(thread_put, thread_id);
    }

    for (int thread_id = 0; thread_id < thread_num; ++thread_id) {
        threads[thread_id].join();// 同步
    }

    for (int thread_id = 0; thread_id<thread_num ; ++thread_id) {
        for (int i = 0; i < 1000; ++i) {
            std::string key = std::to_string(thread_id) + "-" + std::to_string(i);

            auto res = store.Get(key);

            assert(res.has_value());
            std::string value = "value" + std::to_string(thread_id);
            assert(res.value() == value);
        }
    }
}








//MiniRaftKVStore store;

//constexpr int thread_count = 8;
//constexpr int keys_per_thread = 1000;

//std::vector<std::thread> threads;

//for (int thread_id = 0;
//    thread_id < thread_count;
//    ++thread_id) {

//    threads.emplace_back([&store, thread_id]() {
//        for (int i = 0; i < keys_per_thread; ++i) {
//            std::string key =
//                std::to_string(thread_id) + "-" +
//                std::to_string(i);

//            store.Put(key, "value");
//        }
//    });
//}

//for (auto& thread : threads) {
//    thread.join();
//}

//for (int thread_id = 0;
//    thread_id < thread_count;
//    ++thread_id) {

//    for (int i = 0; i < keys_per_thread; ++i) {
//        std::string key =
//            std::to_string(thread_id) + "-" +
//            std::to_string(i);

//        auto result = store.Get(key);

//        assert(result.has_value());
//        assert(result.value() == "value");
//    }
//}