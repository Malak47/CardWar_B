//
// Created by malaklinux on 4/8/23.
//

#ifndef S_S_B_2A_PRINTS_H
#define S_S_B_2A_PRINTS_H

#include "card.hpp"
#include "player.hpp"
#include <string>

using namespace std;


namespace ariel {
    const int CardsNumber = 26;

    class Prints {
    private:
        int drawAmount;
        unsigned int logIndex;
        string str;
        array<string, CardsNumber> log;


    public:
        Prints();

        void printLastTurn();

        void printLog();

        void printStats(Player &player1, Player &player2);

        void printWiner(Player &player1, Player &player2);

        void saveLog(Player &player1, Player &player2, short winnerPerRound);

        void myPrint(Player &player1, Player &player2, short winnerPerRound);

        string getStr();

        string *getLog();

        int getDrawAmount();

        void updateDrawAmount();

        unsigned int getLogIndex();

        void updateLogIndex();

        void setLog(string str);
    };

}
#endif //S_S_B_2A_PRINTS_H
