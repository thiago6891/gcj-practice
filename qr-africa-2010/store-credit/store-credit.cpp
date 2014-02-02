/*
 * store-credit.cpp
 *
 *  Created on: Feb 1, 2014
 *      Author: thiago
 */
#include <fstream>
using namespace std;

class Solution {
	int _size;
	int* _items;

public:
	void setSize(int s) { _size = s; }
	void setItems(int* i) { _items = i; }
	int itemCount() { return _size; }
	int* getItems() { return _items; }

};

class TestCase {
	int _credit;
	int _itemQty;
	int* _prices;

	bool rightCombo(int* combo, int size) {
		int sum = 0;
		for (int i = 0; i < size; i++) {
			sum += _prices[combo[i]];
		}
		return sum == this->_credit;
	}

public:
	void setCredit(int c) { _credit = c; }
	void setItemQty(int q) { _itemQty = q; }
	void setPrices(int* p) { _prices = p; }
	Solution findSolution();
};

TestCase* createTestCasesFromFile(char*, int*);
Solution* findSolutions(int, TestCase*);
void outpoutSolutionsToFile(char*, int, Solution*);
int* getFirstCombo(int);
bool nextCombo(int*, int);

int main(int argc, char** argv) {
	if (argc != 3) return 1;

	int testcaseQty;
	TestCase* testCases = createTestCasesFromFile(argv[1], &testcaseQty);
	Solution* solutions = findSolutions(testcaseQty, testCases);
	outpoutSolutionsToFile(argv[2], testcaseQty, solutions);

	delete testCases;
	delete solutions;

	return 0;
}

TestCase* createTestCasesFromFile(char* fname, int* tc_count) {
	ifstream infile(fname);

	infile >> *tc_count;

	// Initialize test cases
	TestCase* testcases = new TestCase[*tc_count];
	for (int tc_num = 0; tc_num < *tc_count; tc_num++) {
		int credit;
		infile >> credit;
		testcases[tc_num].setCredit(credit);

		int itemQty;
		infile >> itemQty;
		testcases[tc_num].setItemQty(itemQty);

		int* prices = new int[itemQty];
		for (int i = 0; i < itemQty; i++) {
			infile >> prices[i];
		}
		testcases[tc_num].setPrices(prices);
	}

	infile.close();

	return testcases;
}

Solution* findSolutions(int tc_count, TestCase* testCases) {
	Solution* solutions = new Solution[tc_count];

	for (int tc_num = 0; tc_num < tc_count; tc_num++) {
		solutions[tc_num] = testCases[tc_num].findSolution();
	}

	return solutions;
}

void outpoutSolutionsToFile(char* fname, int tc_count, Solution* solutions) {
	ofstream outfile(fname);

	for (int tc_num = 0; tc_num < tc_count; tc_num++) {
		outfile << "Case #" << tc_num + 1 << ": ";
		for (int s_item = 0; s_item < solutions[tc_num].itemCount(); s_item++) {
			outfile << solutions[tc_num].getItems()[s_item] + 1 << " ";
		}
		outfile << endl;
	}

	outfile.close();
}

int* getFirstCombo(int size) {
	int* combo = new int[size];
	for (int i = 0; i < size; i++) combo[i] = i;
	return combo;
}

bool nextCombo(int* combo, int size, int max) {
	int elem = size - 1;
	while (elem < size) {
		if (combo[elem] < max) {
			combo[elem]++;
			elem++;
			if (elem < size) combo[elem] = combo[elem - 1];
		} else {
			elem--;
			if (elem < 0) return false;
		}
	}

	return true;
}

Solution TestCase::findSolution() {
	Solution solution;

	for (int i = 1; i <= this->_itemQty; i++) {
		int* combo = getFirstCombo(i);
		bool solved = this->rightCombo(combo, i);
		while (!solved && nextCombo(combo, i, this->_itemQty - 1)) {
			solved = this->rightCombo(combo, i);
		}

		if (solved) {
			solution.setSize(i);
			solution.setItems(combo);
			break;
		}
	}

	return solution;
}
