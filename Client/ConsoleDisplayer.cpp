/*
 * ConsoleDisplayer.cpp
 * leah orlin 313357725
 * yair frank 203699566
 */

#include "ConsoleDisplayer.h"

ConsoleDisplayer::ConsoleDisplayer() {
	// TODO Auto-generated constructor stub

}


void ConsoleDisplayer::display(const vector<vector<char> > &vec) const{
	unsigned int k = 1;
	unsigned int l = 0, i = 0;
	unsigned int size = vec.size();
	cout << " |";
	while (k < size) {
		cout << ' ' << k << " |";
		k++;
	}
	cout << endl;
	for (unsigned int i = 0; i < size; i++) {
		if (i==size-1)
			cout<<"--";
		else
			cout << "----";
	}
	cout << endl;
	k = 1;
	while (k < size) {
		cout << k << '|';
		while (l < size -1) {
			cout << ' ' << vec[i][l];

			cout << " |";
			l++;
		}
		l = 0;
		cout << endl;
		for (unsigned int m = 0; m < size; m++) {
			if (m==size-1)
				cout<<"--";
			else
				cout << "----";
		}
		cout << endl;
		k++;
		i++;
	}
}

