#include "strings.hpp"

strings::String::String(const char * s) {
	str = s;
}

strings::String::String(const std::string s) {
	str = s;
}

const unsigned strings::String::size() const {
	return str.size();
}

const char& strings::String::operator[](const unsigned n) const {
	if (n < 0 || n >= str.size()) {
		std::cerr << "Index is out of range";
		exit(1);
	}
	return str[n];
}

const std::string strings::String::get_str() const { return str; }

strings::String& strings::String::operator=(const std::string s) {
	str = s;
	return *this;
}

strings::String& strings::String::operator=(const char* s) {
	str = s;
	return *this;
}
strings::BlockString::BlockString(const strings::String& s) : block_str{ s } { }

strings::BlockString::BlockString() { }

strings::BlockString strings::operator+(const BlockString& b_s1, const BlockString& b_s2) {
	BlockString block = b_s1;
	for (int i = 0; i < b_s2.block_str.size(); ++i)
		block.block_str.push_back(b_s2.block_str[i]);
	return block;
}

strings::BlockString strings::operator+(const strings::String& s1, const strings::String& s2) {
	BlockString block = s1;
	block.block_str.push_back(s2);
	return block;
}

strings::BlockString strings::operator*(const BlockString& b_s, const int n) {
	if (n < 0)
		std::cerr << "Arg must be a positive number";
	BlockString block = b_s;
	for (int i = 0; i < n - 1; ++i)
		for (int j = 0; j < b_s.block_str.size(); ++j)
			block.block_str.push_back(b_s.block_str[j]);
	return block;
}


strings::BlockString strings::operator*(const int n, const BlockString& b_s) {
	if (n < 0)
		std::cerr << "Arg must be a positive number";
	BlockString block = b_s;
	for (int i = 0; i < n - 1; ++i)
		for (int j = 0; j < b_s.block_str.size(); ++j)
			block.block_str.push_back(b_s.block_str[j]);
	return block;
}


const strings::String& strings::BlockString::operator[](unsigned n) const { return block_str[n]; }

const char strings::BlockString::operator()(int n) const {
	int i = 0;
	for (; i < block_str.size(); ++i) {
		if (block_str[i].size() <= n)
			n -= block_str[i].size();
		else
			break;
	}
	if (i == block_str.size()) {
		std::cerr << "Index is out of range";
		exit(1);
	}
	return block_str[i][n];
}

const unsigned strings::BlockString::size() const { return block_str.size(); }

const std::vector<std::string> strings::BlockString::get_strs() const {
	std::vector<std::string> ans;
	for (strings::String s : block_str)
		ans.push_back(s.get_str());
	return ans;
}