/*
 * ConsoleDisplayer.cpp
 * leah orlin 313357725
 */

#include "ConsoleDisplayer.h"

ConsoleDisplayer::ConsoleDisplayer() {
	// TODO Auto-generated constructor stub

}


void ConsoleDisplayer::display(const vector<vector<char> > &vec) const{
	unsigned int k = 1;
	unsigned int l = 0, i = 0;
	cout << " |";
	while (k < 9) {
		cout << ' ' << k << " |";
		k++;
	}
	cout << endl << "----------------------------------" << endl;
	k = 1;
	while (k < 9) {
		cout << k << '|';
		while (l < vec.size()) {
			cout << ' ' << vec[i][l];
			if (l!= vec.size() - 1) {
				cout << " |";
			}
			l++;
		}
		l = 0;
		cout << endl << "----------------------------------" << endl;
		k++;
		i++;
	}
}

