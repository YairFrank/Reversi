/*
 * Shortcuts.h
 * yair frank 203699566
 * leah orlin 313357725
 */

#ifndef SHORTCUTS_H_
#define SHORTCUTS_H_
#include <vector>
#include <string>

using namespace std;

class Shortcuts {

public:

		typedef vector<vector<char> > matrix;
		typedef struct coordinate {int x; int y;} coordinate;
		typedef struct aiOption {coordinate move; int score;} aiOption;
		typedef vector<Shortcuts::coordinate> coordVec;
};



#endif /* SHORTCUTS_H_ */
