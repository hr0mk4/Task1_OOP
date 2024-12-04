#ifndef SAMPLE_H
#define SAMPLE_H

#include "strings.hpp"
#include <vector>
#include <string>

namespace strings {
	class BlockSample;
	class Sample {
		std::vector<int> smp;
	public:
		Sample(std::vector<int> v);
		strings::String operator()(const strings::String &s);
		strings::String operator()(const strings::BlockString& s);
		Sample operator()(const std::vector<Sample> &s);
		strings::Sample operator()(const strings::Sample& bs);
		std::vector<int> get_smp();
		Sample operator()(const strings::BlockSample& bs);
	};
	class BlockSample {
		std::vector<strings::Sample> block_s;
	public:
		BlockSample(strings::Sample v);
		BlockSample();
		BlockSample(std::vector<strings::Sample> v);
		BlockSample(std::vector<std::vector<int>> v);
		friend BlockSample operator+(const BlockSample& s1, const BlockSample& s2);
		friend BlockSample operator+(const BlockSample& s1, const strings::Sample& s2);
		//friend BlockSample operator+(const strings::Sample& s1, const strings::Sample& s2);
		friend BlockSample operator*(const BlockSample& s, const int n);
		friend BlockSample operator*(const int n, const BlockSample& s);
		strings::Sample& operator[](unsigned n);
		strings::BlockString operator()(const strings::String& b_s);
		strings::BlockString operator()(const strings::BlockString& b_s);
		strings::BlockSample operator()(strings::BlockSample& b_s);
		const unsigned size() const;
		const std::vector<std::vector<int>> get_smps() const;
		const std::vector<strings::Sample> get_samples() const;
	};
	BlockSample operator+(const BlockSample& s1, const BlockSample& s2);
	BlockSample operator+(const BlockSample& s1, const strings::Sample& s2);
	BlockSample operator*(const BlockSample& s, const int n);
	BlockSample operator*(const int n, const BlockSample& s);
	strings::BlockSample operator+(const Sample &s,const strings::Sample& bs);
	strings::BlockSample operator*(const Sample& bs, int n);
	strings::BlockSample operator*(int n, const Sample& bs);
}

#endif