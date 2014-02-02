/*
 * store-credit.cpp
 *
 *  Created on: Feb 1, 2014
 *      Author: thiago
 */
#include <fstream>
using namespace std;

class Solution {
	int* _items;

public:
	void setItems(int* i) { _items = i; }
	int* getItems() { return _items; }
};

class TestCase {
	int _credit;
	int _itemQty;
	int* _prices;

	bool rightCombo(int* combo) {
		int sum = 0;
		for (int i = 0; i < 2; i++) {
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
int* getFirstCombo();
void nextCombo(int*, int);

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
		for (int s_item = 0; s_item < 2; s_item++) {
			outfile << solutions[tc_num].getItems()[s_item] + 1 << " ";
		}
		outfile << endl;
	}

	outfile.close();
}

int* getFirstCombo() {
	int* combo = new int[2];
	for (int i = 0; i < 2; i++) combo[i] = i;
	return combo;
}

void nextCombo(int* combo, int max) {
	int elem = 1;
	while (elem < 2) {
		if (combo[elem] < max) {
			combo[elem]++;
			elem++;
			if (elem < 2) combo[elem] = combo[elem - 1];
		} else {
			elem--;
		}
	}
}

Solution TestCase::findSolution() {
	Solution solution;
	
	int* combo = getFirstCombo();
	while (!this->rightCombo(combo)) {
		nextCombo(combo, this->_itemQty - 1);
	}
	solution.setItems(combo);
	
	return solution;
}
