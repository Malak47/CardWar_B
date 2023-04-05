//
// Created by malaklinux on 3/27/23.
//

#ifndef S_S_B_2A_GAME_H
#define S_S_B_2A_GAME_H

#include "player.hpp"
#include "card.hpp"
#include <string>

using namespace std;

namespace ariel {
    class Game {
    private:

        Player &player1, &player2;
        short winner;
        Card p1Deck[26];
        Card p2Deck[26];
        int p1 = 0, p2 = 0, curr = 0;

    public:
        Game();

        Game(Player &player1, Player &player2);

        void playTurn();

        void printLastTurn();

        void playAll();

        void printWiner();

        void printLog();

        void printStats();

        void Errors();

        bool isValidPlayer(Player *player);

        void shuffleDeck();

        Card *createCards(Card deck[]);

        void setWinner(short winner);

        short getWinner();

        short CheckWhichCardWins(Card p1Card, Card p2Card);

        void setp1Deck(Card card);

        void setp2Deck(Card card);

        Card *getp1Deck();

        Card *getp2Deck();
    };
}
#endif //S_S_B_2A_GAME_H