//
// Created by malaklinux on 3/27/23.
//

#ifndef S_S_B_2A_PLAYER_H
#define S_S_B_2A_PLAYER_H

#include <string>
#include <array>
#include "card.hpp"

using namespace std;
const int playerCardsNumber = 26;

namespace ariel {
    class Player {
    private:
        string name;
        int stack_size;
        int cards_taken;
        unsigned long playerIterator;
        int total_round_wins;
        double win_rate;
        //Card initial_cards[playerCardsNumber];
        array<Card,playerCardsNumber> initial_cards;
    public:
        Player(string name);

        void setName(string name);

        string getName();

        int stacksize();

        void setStackSize(int size);

        int cardesTaken();

        void updateCardsTaken(int num);

        void setRate(double rate);

        double getRate();

        void setDeck(Card card);

        void updatePlayerIterator();

        void resetPlayerIterator();

        Card getCard();

        Card* getDeck();

        void updateTotalRoundWins();

        int getTotalRoundWins();

    };
}
#endif //S_S_B_2A_PLAYER_H