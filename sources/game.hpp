//
// Created by malaklinux on 3/27/23.
//

#ifndef S_S_B_2A_GAME_H
#define S_S_B_2A_GAME_H

#include "player.hpp"
#include "deck.hpp"
#include "prints.hpp"
#include <string>

using namespace std;

namespace ariel {
    class Game {
    private:
        Prints prints;
        Player &player1, &player2;
        Deck deck;
        short winnerPerRound;

    public:
        Game(Player &player1, Player &player2);

        void setPlayersDecks();

        void CheckWhichCardWins(Card p1Card, Card p2Card);

        void playTurn();

        void playAll();

        void Errors();

        bool isValidPlayer(Player *player);

        void printLastTurn();

        void printLog();

        void printStats();

        void printWiner();

        void myPrint();

        void playRound(bool flag);

    };
}
#endif //S_S_B_2A_GAME_H