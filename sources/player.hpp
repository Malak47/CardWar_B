//
// Created by malaklinux on 3/27/23.
//

#ifndef S_S_B_2A_PLAYER_H
#define S_S_B_2A_PLAYER_H

#include <string>
#include "card.hpp"

using namespace std;

namespace ariel {
    class Player {
    private:
        string name;
        int stack_size;
        int cards_taken;
        int total_round_wins;
        double win_rate;
        Card *deck;
    public:
        Player();

        Player(string name);

        void setName(string name);

        int stacksize();

        int cardesTaken();

        string getName();

        double getRate();

        void setRate(double rate);

        void updateCardsTaken();

        void setStackSize(int size);

        void setDeck(Card *cards);

        Card* getDeck();

        void updateTotalRoundWins();

        int getTotalRoundWins();
    };
}
#endif //S_S_B_2A_PLAYER_H