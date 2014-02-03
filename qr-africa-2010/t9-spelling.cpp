#include <fstream>
#include <string>

void out_digit(int d, int* last_n, std::ofstream* ofile, int strokes) {
	if (*last_n == d) *ofile << ' ';
	for (int i = 0; i < strokes; i++) *ofile << d;
	*last_n = d;
}

void get_digit_times(char c, int* digit, int* times) {
	if (c - 'w' >= 0) { *digit = 9; *times = c - 'w' + 1; }
	else if (c - 't' >= 0) { *digit = 8; *times = c - 't' + 1; }
	else if (c - 'p' >= 0) { *digit = 7; *times = c - 'p' + 1; }
	else if (c - 'm' >= 0) { *digit = 6; *times = c - 'm' + 1; }
	else if (c - 'j' >= 0) { *digit = 5; *times = c - 'j' + 1; }
	else if (c - 'g' >= 0) { *digit = 4; *times = c - 'g' + 1; }
	else if (c - 'd' >= 0) { *digit = 3; *times = c - 'd' + 1; }
	else if (c - 'a' >= 0) { *digit = 2; *times = c - 'a' + 1; }
	else { *digit = 0; *times = 1; }
}

int main(int argc, char** argv) {
	if (argc != 3) return -1;

	std::ifstream ifile(argv[1]);
	std::ofstream ofile(argv[2]);

	std::string line;
	std::getline(ifile, line);
	int tc_count = std::stoi(line, nullptr);

	for (int tc = 1; tc <= tc_count; tc++) {
		ofile << "Case #" << tc << ": ";

		std::getline(ifile, line);

		int last_n = ' ';
		auto it = std::begin(line);
		while (it != std::end(line)) {
			int digit;
			int times;
			get_digit_times(*it, &digit, &times);
			out_digit(digit, &last_n, &ofile, times);
			it++;
		}

		ofile << std::endl;
	}

	ifile.close();
	ofile.close();

	return 0;
}
