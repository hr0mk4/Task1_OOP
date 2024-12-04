#ifndef OUTPUT_H
#define OUTPUT_H

#include"Sample.hpp"
#include"strings.hpp"
#include <iostream>

namespace strings {
	enum types { array, plain, def };
	class Output {
		std::ostream& out;
		types type = def;
	public:
		Output(std::ostream& os);
		Output& operator<<(types t);
		Output& operator<<(const String& s);
		Output& operator<<(const BlockString& bs);
		Output& operator<<(const BlockSample& bs);
		template <class T> Output& operator<<(const T& var) {
			out << var;
			return *this;
		}
	};

	inline Output cout = std::cout;
}

#endif