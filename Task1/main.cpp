#include "strings.hpp"
#include "Sample.hpp"
#include "output.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

int main() {
	std::string s = "abc ";
	strings::String a, b = "a", c = s;
	strings::BlockString bstr = a + b * 1 + 2 * c;
	// Prints {"" , "a", "abc ", "abc "}:
	strings::cout << strings::array << bstr << '\n';
	strings::cout << strings::plain << bstr << '\n'; // Prints aabc abc 
	strings::cout << bstr(3) << ' ' << bstr[3] << '\n'; //Prints c abc 

	std::ofstream fil("a.txt");
	strings::Output fout(fil);
	fout << strings::plain << bstr << '\n'; // Prints aabcabc to file a.txt
	fil.close(); // Closes file a.txt

	std::vector <std::vector <int >> v = { {4, 3, 2, 1, 0}, {3, 5, 10} , {0} };
	strings::BlockSample f(v);
	strings::cout << strings::array << f(bstr) << '\n'; // {" cbaa", "ca?", "a"}
	strings::cout << strings::plain << f(bstr) << '\n'; // cbaaca?a

	v = { {1, 2, 1}, {4, 5, 5} };
	strings::BlockSample g(v);
	strings::cout << strings::array << g(bstr) << '\n'; // {" aba", " aa"}
	strings::cout << strings::plain << g(bstr) << '\n'; // aba aa

	strings::BlockSample fg = f(g); // fg = {{5, 4, 1, 2, 1}, {4, 5, -1}, {1}}
	// Prints some representation of block samples :
	strings::cout << f << '\n' << g << '\n' << fg << '\n';
	// Prints {"a aba", " a?", "a"}:
	strings::cout << strings::array << fg(bstr) << '\n';
	strings::cout << strings::plain << fg(bstr) << '\n'; // a aba a?a

	strings::Sample shift_left(std::vector <int >({ 1 , 2, 3, 4, 5, 6, 7, 8, 0 }));
	strings::BlockSample h = shift_left(fg);
	// h = {{4 , 1, 2, 1, 4, 5, -1, 1, 5}}
	strings::cout << strings::array << h(c) << '\n'; // {"?bcb???b?"}
	strings::cout << strings::plain << h(c) << '\n'; // ?bcb???b?

	shift_left = std::vector <int >({ 1 , 2, 0 });
	strings::Sample shift_right(std::vector <int >({ 2 , 0, 1 }));
	f = shift_left * 1 + 2 * shift_right;
	// f = {{1 , 2, 0}, {2, 0, 1}, {2, 0, 1}}
	strings::cout << strings::array << f(s) << '\n'; // {"bca", "cab", "cab"}
	strings::cout << strings::plain << f(s) << '\n'; // bcacabcab

	a = "b";
	bstr = (shift_right + shift_left(shift_right))(a + b * 2);
	strings::cout << strings::array << bstr << '\n'; // {"aba", "baa"}
	strings::cout << strings::plain << bstr << '\n'; // ababaa

	return 0;
}