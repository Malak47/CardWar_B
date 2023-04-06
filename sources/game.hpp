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
        string number[13]{"2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace"};
        string symbol[4]{"Hearts", "Spades", "Clubs", "Diamonds"};
        Player &player1, &player2;
        short winnerPerRound;
        Card p1Deck[26];
        Card p2Deck[26];
        int p1 = 0, p2 = 0, curr = 0, logIndex = 0, drawAmount = 0, numberOfDrawsPerRound = 0;
        string log[26];
        string str;

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

        void CheckWhichCardWins(Card p1Card, Card p2Card);

        void setp1Deck(Card card);

        void setp2Deck(Card card);

        Card *getp1Deck();

        Card *getp2Deck();

        void saveLog();

        void playRound();

        void myPrint();
    };
}
#endif //S_S_B_2A_GAME_H