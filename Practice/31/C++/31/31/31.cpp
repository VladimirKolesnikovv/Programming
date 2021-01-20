#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>

#define ПО_ЗНАЧЕНИЮ

using std::vector;
using std::ostream;

#ifdef ПО_ССЫЛКЕ
ostream& operator<<(ostream& os, const vector<int>& x) {
	os << x.size() << "\t| ";
	for (int i = 0; i < x.size(); i++) {
		os << &x[i];
		if (i + 1 < x.size())
			os << " ";
	}
	os << std::endl;
	return os;
}
#endif
#ifdef ПО_ЗНАЧЕНИЮ
ostream& operator<<(ostream& os, vector<int> x) {
	os << x.size() << "\t| ";
	for (int i = 0; i < x.size(); i++) {
		os << &(x[i]);
		if (i + 1 < x.size())
			os << " ";
	}
	os << std::endl;
	return os;
}
#endif

int main()
{
	vector<int> v;
	std::ofstream ofs("data.txt");
	for (int i = 0; i <= 63; i++) {
		v.push_back(1);
		ofs << v;
	}
	while (v.size()) {
		v.pop_back();
		ofs << v;
	}
}