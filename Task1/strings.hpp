#ifndef STRINGS_H
#define STRINGS_H

#include<string>
#include<iostream>
#include<vector>

namespace strings {
	class String {
		std::string str;
	public:
		String(const char* s = "");
		String(const std::string s);
		const unsigned size() const;
		const char& operator[](const unsigned n) const;
		const std::string get_str() const;
		String& operator=(const std::string s);
		String& operator=(const char *s);
	};
	class BlockString {
		std::vector<strings::String> block_str;
	public:
		BlockString(const strings::String& s);
		BlockString();
		friend BlockString operator+(const BlockString& s1, const BlockString& s2);
		friend BlockString operator+(const strings::String& s1, const strings::String& s2);
		friend BlockString operator*(const BlockString& s, const int n);
		//friend BlockString operator*(const strings::String& s, const int n);
		friend BlockString operator*(const int n, const BlockString& s);
		//friend BlockString operator*(const int n, const strings::String& s);
		const strings::String& operator[](unsigned n) const;
		const char operator()(int n) const;
		const unsigned size() const;
		const std::vector<std::string> get_strs() const;
	};
	BlockString operator*(const BlockString& s, const int n);
	BlockString operator*(const int n, const BlockString& s);
	BlockString operator+(const strings::String& s1, const strings::String& s2);
	BlockString operator+(const BlockString& s1, const BlockString& s2);
}

#endif