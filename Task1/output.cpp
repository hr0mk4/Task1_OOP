#include"output.hpp"

strings::Output::Output(std::ostream& os): out(os) { }

strings::Output& strings::Output::operator<<(types t) { type = t; return *this; }

strings::Output& strings::Output::operator<<(const String& S) {
	out << S.get_str();
	return *this;
}

strings::Output& strings::Output::operator<<(const BlockString& bs) {
	if (type == array) {
		out << "{";
		std::vector<std::string> v = bs.get_strs();
		for (int i = 0; i < v.size(); ++i) {
			out << "\"";
			out << v[i];
			out << "\"";
			if (i < v.size() - 1)
				out << ", ";
		}
		out << "}";
	}
	if (type == plain){
		std::vector<std::string> v = bs.get_strs();
		for (int i = 0; i < v.size(); ++i)
			out << v[i];
	}
	if (type == def)
		std::cerr << "FAILURE: Choose the modifier";
	return *this;
}

strings::Output& strings::Output::operator<<(const BlockSample& bs) {
	out << "{";
	std::vector<std::vector<int>> v = bs.get_smps();
	for (int i = 0; i < bs.size(); ++i) {
		out << " {";
		for (int j = 0; j < v[i].size() - 1; ++j)
			out << v[i][j] << ", ";
		out << v[i][v[i].size() - 1];
		out << "} ";
		if (i < bs.size() - 1)
			out << ", ";
	}
	out << "}";
	return *this;
}