//
// Created by leah on 25/12/17.
//

#include "List_gamesCommand.h"

List_gamesCommand::List_gamesCommand() {}

void List_gamesCommand::execute(clientData *cd, int sid) {
    GamesList* games = GamesList::getGamesList();
    games->display();
}