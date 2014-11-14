#include <fstream>
#include <unordered_map>
#include <string>
#include <cmath>
using namespace std;

int main() {
	ifstream ifile("A-large-practice.in");
	ofstream ofile("A-large-practice.out");

	int T; ifile >> T;
	for (int tc = 1; tc <= T; tc++)
	{
		string str; ifile >> str;
		unordered_map<char, int> dic;

		string::iterator it = str.begin();
		dic.insert({ *it, 1 });
		it++;
		
		while (it != str.end()) {
			char c = (char)*it;
			if (c != str[0]) break;
			it++;
		}

		if (it != str.end()) {
			dic.insert({ *it, 0 });
			it++;
		}

		int base = 2;
		while (it != str.end()) {
			if (dic.find(*it) == dic.end())
				dic.insert({ *it, base++ });
			it++;
		}
		
		long long result = 0;
		long long power = 1;
		for (int i = str.length() - 1; i >= 0; i--)
		{
			result += dic[str[i]] * power;
			power *= base;
		}

		ofile << "Case #" << tc << ": " << result << endl;
	}

	ifile.close();
	ofile.close();

	return 0;
}
