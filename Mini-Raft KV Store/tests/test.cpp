//#include <cassert>
//#include <iostream>
//#include "mini_raft_kv_store.h"
//
//int main() {
//    MiniRaftKVStore store;
//
//    assert(store.Put("name", "Dino"));
//    
//    auto value = store.Get("name");
//    assert(value.has_value());
//    assert(value.value() == "Dino");
//
//    assert(!store.Get("age").has_value());
//
//    assert(store.Delete("name"));
//    assert(!store.Get("name").has_value());
//
//    assert(!store.Delete("name"));
//
//    std::cout << "All tests passed\n";
//}