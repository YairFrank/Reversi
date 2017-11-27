/*
 * ConsoleDisplayer.h
 *
 * leah orlin 313357725
 */


#ifndef CONSOLEDISPLAYER_H_
#define CONSOLEDISPLAYER_H_

#include "Displayer.h"

class ConsoleDisplayer: public Displayer {
public:
	ConsoleDisplayer();

	/**
	 * display a given 2d vector.
	 * @param vec matrix (2d vector).
	 */
	void display(const vector<vector<char> > &vec) const;
};

#endif /* CONSOLEDISPLAYER_H_ */
