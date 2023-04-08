//
// Created by malaklinux on 4/8/23.
//

#ifndef S_S_B_2A_PRINTS_H
#define S_S_B_2A_PRINTS_H
#include "card.hpp"
#include "player.hpp"
#include <string>
#include "iostream"
#include <iomanip>
using namespace std;


namespace ariel {
    class Prints {
    private:
        int logIndex, drawAmount;
        string *log, str;
    public:
        Prints();

        void printLastTurn();

        void printLog();

        void printStats(Player player1, Player player2);

        void printWiner(Player player1, Player player2);

        void saveLog(Player player1, Player player2, short winnerPerRound);

        void myPrint(Player player1,Player player2, short winnerPerRound);

        string getStr();

        string *getLog();

        int getDrawAmount();

        void updateDrawAmount();

        int getLogIndex();

        void updateLogIndex();

        void setLog(string str);
    };

}
#endif //S_S_B_2A_PRINTS_H
