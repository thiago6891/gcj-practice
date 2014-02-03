#include <fstream>
#include <string>
#include <stack>

int main(int argc, char** argv) {
	if (argc != 3) return -1;

	std::ifstream ifile(argv[1]);
	std::ofstream ofile(argv[2]);

	std::string line;

	std::getline(ifile, line);
	int tc_count = std::stoi(line, nullptr);

	for (int tc = 1; tc <= tc_count; tc++) {
		std::getline(ifile, line);

		std::stack<std::string> all_words;
		std::string word;

		auto it = std::begin(line);
		while (it != std::end(line)) {
			word.clear();
			all_words.push(word);
			while (it != std::end(line) && *it != ' ') {
				all_words.top().push_back(*it);
				it++;
			}
			if (it != std::end(line)) it++;
		}

		ofile << "Case #" << tc << ": ";
		while (!all_words.empty()) {
			ofile << all_words.top() << " ";
			all_words.pop();
		}
		ofile << std::endl;
	}

	ifile.close();
	ofile.close();

	return 0;
}
