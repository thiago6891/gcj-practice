#include <fstream>
#include <iomanip>
#include <list>
using namespace std;

int main(int argc, char** argv) {
	ifstream ifile(argv[1]);
	ofstream ofile(argv[2]);

	int tc_total;
	ifile >> tc_total;
	for (int tc = 1; tc <= tc_total; tc++) {
		int total_coords;
		ifile >> total_coords;

		list<int> v1;
		for (int c = 0; c < total_coords; c++) {
			int coord;
			ifile >> coord;
			v1.push_back(coord);
		}

		list<int> v2;
		for (int c = 0; c < total_coords; c++) {
			int coord;
			ifile >> coord;
			v2.push_back(coord);
		}

		// After both vectors have their coordinates ordered, the minimum scalar product is
		// calculated by multiplying one vector's smallest coordinates with the other's biggest
		// ones, in other words, minimum scalar product = x1*yn + x2*y(n-1) + ... + xn*y1
		v1.sort();
		v2.sort();

		list<int>::iterator it1 = v1.begin();
		list<int>::reverse_iterator it2 = v2.rbegin();

		// The double scalar_product variable and the typecast on *it1 and *it2 are used to deal
		// with large numbers.
		double scalar_product = 0;
		for (int c = 0; c < total_coords; c++) {
			scalar_product += (double)(*it1) * (double)(*it2);
			it1++;
			it2++;
		}

		ofile << "Case #" << tc << ": " 
			<< setiosflags(ios::fixed) << setprecision(0) 
			<< scalar_product << endl;
	}

	ifile.close();
	ofile.close();

	return 0;
}