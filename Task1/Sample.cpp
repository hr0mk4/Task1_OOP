#include "Sample.hpp"

strings::Sample::Sample(std::vector<int> v) : smp(v) { }

strings::String strings::Sample::operator()(const strings::String &s) {
	int size = smp.size();
	char* ans = new char[size + 1];
	for (int i = 0; i < size; ++i) {
		if (smp[i] >= s.size() || smp[i] < 0)
			ans[i] = '?';
		else
			ans[i] = s[smp[i]];
	}
	ans[size] = '\0';
	strings::String a(ans);
	delete[] ans;
	return a;
}

strings::String strings::Sample::operator()(const strings::BlockString &s) {
	int size = smp.size();
	char* ans = new char[size + 1];
	int block_size = 0;
	for (int i = 0; i < s.size(); ++i)
		block_size += s[i].size();
	for (int i = 0; i < size; ++i) {
		if (smp[i] >= block_size || smp[i] < 0)
			ans[i] = '?';
		else {
			int n = smp[i];
			int j = 0;
			for (; n >= s[j].size(); ++j)
				n -= s[j].size();
			ans[i] = s[j][n];
		}
	}
	ans[size] = '\0';
	strings::String a(ans);
	delete[] ans;
	return a;
}

strings::Sample strings::Sample::operator()(const std::vector<Sample>& s) {
	std::vector<int> ans;
	int size = 0;
	for (int i = 0; i < s.size(); ++i)
		size += s[i].smp.size();
	for (int i = 0; i < smp.size(); ++i) {
		if (smp[i] >= size || smp[i] < 0) {
			ans.push_back(-1);
			continue;
		}
		int n = smp[i];
		for (int j = 0; j < s.size(); ++j) {
			if (s[j].smp.size() <= n)
				n -= s[j].smp.size();
			else {
				ans.push_back(s[j].smp[n]);
				break;
			}
		}
	}
	strings::Sample a(ans);
	return a;
}

/*strings::BlockSample strings::Sample::operator()(const strings::BlockSample& bs) {
	strings::BlockSample ans;
	strings::Sample s = *this;
	ans = s(bs.get_smps());
	return ans;
}*/

strings::BlockSample strings::operator*(const strings::Sample& bs, int n) {
	if (n < 0)
		std::cerr << "Arg must be a positive number";
	strings::BlockSample ans;
	for (int i = 0; i < n; ++i)
		ans = ans + bs;
	return ans;
}

strings::BlockSample strings::operator*(int n, const strings::Sample& bs) {
	if (n < 0)
		std::cerr << "Arg must be a positive number";
	strings::BlockSample ans;
	for (int i = 0; i < n; ++i)
		ans = ans + bs;
	return ans;
}

strings::Sample strings::Sample::operator()(const strings::Sample& bs) {
	int size = bs.smp.size();
	std::vector<int> ans;
	for (int i = 0; i < smp.size(); ++i) {
		if (smp[i] >= size || smp[i] < 0)
			ans.push_back(-1);
		else
			ans.push_back(bs.smp[smp[i]]);
	}
	return ans;
}

strings::BlockSample strings::operator+(const strings::Sample &s1, const strings::Sample& s) {
	BlockSample b(s1);
	b = b + s;
	return b;
}

strings::BlockSample::BlockSample(strings::Sample v) : block_s{ v } { }

strings::BlockSample::BlockSample() { }

strings::BlockSample::BlockSample(std::vector<strings::Sample> v) : block_s(v) { }

strings::BlockSample::BlockSample(std::vector<std::vector<int>> v) {
	for (int i = 0; i < v.size(); ++i)
		block_s.push_back(strings::Sample(v[i]));
}

strings::BlockSample strings::operator+(const BlockSample& b_s1, const BlockSample& b_s2) {
	BlockSample block = b_s1;
	for (int i = 0; i < b_s2.block_s.size(); ++i)
		block.block_s.push_back(b_s2.block_s[i]);
	return block;
}

strings::BlockSample strings::operator+(const BlockSample& s1, const strings::Sample& s2) {
	BlockSample block = s1;
	block.block_s.push_back(s2);
	return block;
}

strings::BlockSample strings::operator*(const BlockSample& b_s, const int n) {
	if (n < 0)
		std::cerr << "Arg must be a positive number";
	BlockSample block = b_s;
	for (int i = 0; i < n - 1; ++i)
		for (int j = 0; i < b_s.block_s.size(); ++j)
			block.block_s.push_back(b_s.block_s[j]);
	return block;
}

strings::BlockSample strings::operator*(const int n, const BlockSample& b_s) {
	if (n < 0)
		std::cerr << "Arg must be a positive number";
	BlockSample block = b_s;
	for (int i = 0; i < n - 1; ++i)
		for (int j = 0; i < b_s.block_s.size(); ++j)
			block.block_s.push_back(b_s.block_s[j]);
	return block;
}

strings::Sample& strings::BlockSample::operator[](unsigned n) {
	if (n < 0 || n >= block_s.size()) {
		std::cerr << "Inappropriate argument";
		exit(1);
	}
	return block_s[n]; 
}

strings::BlockString strings::BlockSample::operator()(const strings::String& s) {
	strings::BlockString ans;
	for (int i = 0; i < block_s.size(); ++i) {
		strings::String str = block_s[i](s);
		ans = ans + str;
	}
	return ans;
}

strings::BlockString strings::BlockSample::operator()(const strings::BlockString& v) {
	strings::BlockString ans;
	for (int i = 0; i < block_s.size(); ++i) {
		strings::String str = block_s[i](v);
		ans = ans + str;
	}
	return ans;
}

strings::BlockSample strings::BlockSample::operator()(strings::BlockSample& b_s) {
	strings::BlockSample ans;
	for (int i = 0; i < block_s.size(); ++i)
		ans = ans + block_s[i](b_s.block_s);
	return ans;
}

const unsigned strings::BlockSample::size() const {
	return block_s.size();
}

std::vector<int> strings::Sample::get_smp() {
	return smp;
}

const std::vector<std::vector<int>> strings::BlockSample::get_smps() const {
	std::vector<std::vector<int>> ans;
	for (strings::Sample s : block_s)
		ans.push_back(s.get_smp());
	return ans;
}

const std::vector<strings::Sample> strings::BlockSample::get_samples() const { return block_s; }

strings::Sample strings::Sample::operator()(const strings::BlockSample& bs) {
	Sample s = *this;
	return s(bs.get_samples());
}