//
// Created by leah on 25/12/17.
//

#ifndef ROOT_JOINCOMMAND_H
#define ROOT_JOINCOMMAND_H

#include "Command.h"
//typedef struct gameData{string name;int player1Socket; int player2socket;} gameData;
class JoinCommand: public Command {
public:

    /**
     * constructor
     */
    JoinCommand();

    /**
     * execute the command
     * @param cd client data-data relevant from command execution
     * @param sid client socket id
     */
    virtual void execute(vector <string> cd, int sid);
private:

    /**
     * run the game after both players are joined
     * @param name game name
     * @param player1Socket socket of first player
     * @param player2Socket socket of second player
     */
    void runGame(string name, int player1Socket, int player2Socket);

    /**
     * assign symbol to player
     * @param clientSocket players socket
     * @param numPlayer order of player when joining game
     */
    void assignSymbol(int clientSocket, int numPlayer) const;

    /**
     * pass the moves between the clients
     * @param clientSocket player socket to pass the move to
     * @param oppMove opponents move
     * @param firstMove if it is first move or not
     * @return the next move...
     */
    coordinate passMove(int clientSocket, coordinate oppMove, bool &firstMove);

    /**
     * @param m cooordinate of move
     * @return true if move indicates the game has been won
     */
    bool isWin(coordinate m);

};

#endif //ROOT_JOINCOMMAND_H
