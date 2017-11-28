/*
 * HumanPlayer.h
 *
 *  Created on: Nov 28, 2017
 *      Author: leah
 */

<<<<<<< HEAD
#ifndef HUMANPLAYER_H_
#define HUMANPLAYER_H_

=======
#ifndef REVERSI_HUMANPLAYER_H
#define REVERSI_HUMANPLAYER_H
#include "Shortcuts.h" //in order to get the typedefs
>>>>>>> 6ac857854cf2c9c33264042560d7a3aa9cb534e9
#include "Player.h"
#include "Shortcuts.h"

class HumanPlayer: public Player {
public:
<<<<<<< HEAD
	HumanPlayer();
	/**
	 * constructor for player, given sign.
	 * @param x player's sign.
	 */
	HumanPlayer(char x);

	/**
	 * player plays a turn.
	 * @param c coordinate to place player on.
	 */
	void playTurn(Shortcuts::coordinate &c, Shortcuts::coordVec v, Board &b);
	virtual ~HumanPlayer();
};

#endif /* HUMANPLAYER_H_ */
=======
    /**
     * default constructor.
     */
    HumanPlayer();

    /**
     * constructor for player, given sign.
     * @param x player's sign.
     */
    HumanPlayer(char x);

    /**
     * player plays a turn.
     * @param c coordinate to place player on.
     */
    void playTurn(Shortcuts::coordinate &c);

private:
    char sign;
    bool hasMoves;
};

>>>>>>> 6ac857854cf2c9c33264042560d7a3aa9cb534e9



#endif //REVERSI_HUMANPLAYER_H
