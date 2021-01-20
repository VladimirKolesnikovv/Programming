#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <algorithm>

using std::vector;
using std::ostream;
using std::istream;
using std::string;

const string filename = "train.csv";
const string out_filename = "out.csv";

struct Passenger {
	/*int*/ string survival;       
									
	/*int*/ string pclass;
									
	string name;
	string sex;
	/*double*/ string age;
	double age_double;
	/*int*/ string sibsp;
	/*int*/ string parch;
	string ticket;
	/*double*/ string fare;
	string cabin;
	string embarked;
};

int skipToNonspaceCharacter(string& x, int pos) {
	while (pos < x.length()) {
		if ((x[pos] == ' ') || (x[pos] == '\t')) {
			pos++;
		}
		else {
			return pos;
		}
	}
	return -1;
}

string readToComma(string& x, int& pos) {
	string buff = {};
	while (pos < x.length()) {
		if ((x[pos] == '\r') || (x[pos] == '\n') || (x[pos] == ',')) {
			break;
		}
		buff += x[pos];
		pos++;
	}
	return buff;
}

string readQuote(string& x, int& pos) {
	string buff = {};
	bool quoteOpened = true;
	while (pos < x.length()) {
		if ((x[pos] == '"')) {
			quoteOpened = !quoteOpened;
		}
		if ((x[pos] == '\r') || (x[pos] == '\n')) {
			break;
		}
		if ((x[pos] == ',') && (!quoteOpened)) {
			break;
		}
		if (quoteOpened)
			buff += x[pos];
		pos++;
	}
	return buff;
}

void readString(string& x, vector<string>& values, int& pos) {
	pos = skipToNonspaceCharacter(x, pos);
	if (pos >= 0) {
		if (x[pos] == '"') {
			pos++;
			string buff = readQuote(x, pos);
			values.push_back(buff);
		}
		else {
			string buff = readToComma(x, pos);
			values.push_back(buff);
		}
		if (x[pos] == ',') {
			pos++;
			readString(x, values, pos);
		}
		else {
			pos++;
		}
	}
}

istream& operator>>(istream& is, vector<Passenger>& x) {
	std::stringstream ss;
	ss << is.rdbuf();
	string lines = ss.str();
	int pos = 0;
	int count = 0;
	while (pos < lines.length()) {
		count++;
		vector<string> values = {};
		readString(lines, values, pos);
		if (count == 1) continue;
		Passenger p;
		p.survival = values[1];
		p.pclass = values[2];
		p.name = values[3];
		p.sex = values[4];
		p.age = values[5];
		try { p.age_double = std::stod(p.age); }
		catch (...) { p.age_double = -1; };
		p.sibsp = values[6];
		p.parch = values[7];
		p.ticket = values[8];
		p.fare = values[9];
		p.cabin = values[10];
		p.embarked = values[11];
		x.push_back(p);
	}
	return is;
}

string replace_quote(string str) {
	int sbegin = 0;
	int offset = 0;
	while (sbegin >= 0) {
		sbegin = str.find("\"", offset);
		if (sbegin > 0) {
			str = str.replace(sbegin, 1, "\"\"");
		}
		offset = sbegin + 2;
	}
	return str;
}

ostream& operator<<(ostream& os, vector<Passenger>& x) {
	for (int i = 0; i < x.size(); i++) {
		os << x[i].survival << ",";
		os << x[i].pclass << ",";
		os << "\"" << replace_quote(x[i].name) << "\",";
		os << x[i].sex << ",";
		os << x[i].age << ",";
		os << x[i].sibsp << ",";
		os << x[i].parch << ",";
		os << x[i].ticket << ",";
		os << x[i].fare << ",";
		os << x[i].cabin << ",";
		os << x[i].embarked << std::endl;
	}
	return os;
}

bool sortpred(const Passenger& a, const Passenger& b) {
	return a.age_double < b.age_double;
}

void sort(vector<Passenger>& x) {
	vector<std::reference_wrapper<Passenger>> px;
	for (int i = 0; i < x.size(); i++) {
		if ((x[i].sex == "female") && (x[i].survival == "1") && (x[i].pclass == "1")) {
			px.push_back(std::ref(x[i]));
		}
	}
	for (int i = 0; i < px.size(); i++) {
		auto it = std::min_element(std::begin(px) + i, std::end(px), sortpred);
		int id = std::distance(std::begin(px), it);
		auto temp = px[id].get();
		px[id].get() = px[i].get();
		px[i].get() = temp;
	}
}

int main()
{
	std::ifstream is(filename);
	std::ofstream os(out_filename);
	vector<Passenger> v;
	is >> v;
	sort(v);
	os << v;
}