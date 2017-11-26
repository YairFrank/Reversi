/*
 * Displayer.h
 *
 * leah orlin 313357725
 */

#ifndef DISPLAYER_H_
#define DISPLAYER_H_
#include <vector>
#include <iostream>
using namespace std;

class Displayer {

public:
	Displayer();
	virtual ~Displayer();

	/**
	 * virtual function to display a board. Will be defined in inherited classes (console/graphic).
	 * @param board
	 */
	virtual void display(const vector<vector<char> > &board) const;



};

#endif /* DISPLAYER_H_ */
