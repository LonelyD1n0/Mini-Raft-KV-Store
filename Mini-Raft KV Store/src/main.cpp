#include <iostream>
#include <string>
#include <vector>
#include <algorithm> // std::transform();
#include <cctype> // std::toupper();
#include "mini_raft_kv_store.h"

static bool translateCommand(const std::string& command,MiniRaftKVStore& kvmap) {
	std::vector<std::string> vec;// 存放关键词
	std::string str;// 暂存变量

	int n = command.size();
	// 拆分命令
	for (char c : command) {
		if (c == ' ') {
			if (!str.empty()) {
				vec.push_back(str);
				str.clear();
			}
		}
		else {
			str.push_back(c);
		}
	}

	if (!str.empty()) {
		vec.push_back(str);
	}// push最后一个单词块

	n = vec.size();
	if (n == 0) return true;
	std::string com_ = vec[0];// 命令

	std::transform(com_.begin(), com_.end(), com_.begin(),[](unsigned char c) {
			return std::toupper(c);
		});// 统一成大写

	if (com_ == "PUT") {
		if (n != 3) return false;

		std::string key_ = vec[1], value_ = vec[2];// 键值
		auto res = kvmap.Put(key_, value_);
		if (res == true) {
			std::cout << "OK." << std::endl;
			return res;
		}
		return res;
	}

	else if (com_ == "GET") {
		if (n != 2) return false;

		std::string key_ = vec[1];
		auto res = kvmap.Get(key_);
		if (res.has_value()) {
			std::cout << res.value() << std::endl;
			return true;
		}
		else {
			std::cerr << "NOT FOUND." << std::endl;
			return true;
		}
	}

	else if (com_ == "DELETE") {
		if (n != 2) return false;

		std::string key_ = vec[1];
		auto res = kvmap.Delete(key_);
		if (res) {
			std::cout << "OK." << std::endl;
		}
		return res;
	}

	else {
		std::cout << "UNKNOWN COMMAND." << std::endl;
		return true;
	}// 未知命令报告

	return true;
}


int main() {
	MiniRaftKVStore kvmap;
	std::string command;// 输入的一整行命令
	while (1) {
		command.clear();// 每一轮清空命令
		bool success = true;

		std::cout << "> ";
		if (!std::getline(std::cin, command)) {
			break;
		}

		if (command == "EXIT" || command == "exit") {
			std::cout << "BYE." << std::endl;
			break;
		}

		success = translateCommand(command,kvmap);

		if (success != true) {
			std::cerr << "ERROR!" << std::endl;
		}
	}
}