cmake_minimum_required(VERSION 3.10)

project(MiniRaftKVStore LANGUAGES CXX)

find_package(Threads REQUIRED)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(KV_STORE_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/src/mini_raft_kv_store.cpp")
set(KV_STORE_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")

# Interactive command-line application.
add_executable(mini_raft_kv_store
    src/main.cpp
    "${KV_STORE_SOURCE}"
)
target_include_directories(mini_raft_kv_store PRIVATE "${KV_STORE_INCLUDE_DIR}")

# Standalone basic test program.
add_executable(kv_store_test
    tests/test.cpp
    "${KV_STORE_SOURCE}"
)
target_include_directories(kv_store_test PRIVATE "${KV_STORE_INCLUDE_DIR}")

# Standalone concurrent test program.
add_executable(kv_store_concurrent_test
    tests/concurrent_test.cpp
    "${KV_STORE_SOURCE}"
)
target_include_directories(kv_store_concurrent_test PRIVATE "${KV_STORE_INCLUDE_DIR}")
target_link_libraries(kv_store_concurrent_test PRIVATE Threads::Threads)
