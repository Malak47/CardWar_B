//
// Created by malaklinux on 4/8/23.
//

#include "prints.hpp"
#include "player.hpp"
#include <string>

using namespace std;

namespace ariel {

    Prints::Prints() {
        this->logIndex = 0;
        this->log = nullptr;
        this->drawAmount = 0;
        this->str = "";
    }

    // Alice played Queen of Hearts Bob played 5 of Spades. Alice wins.
// Alice played 6 of Hearts Bob played 6 of Spades. Draw. Alice played 10 of Clubs Bob played 10 of Diamonds. draw. Alice played Jack of Clubs Bob played King of Diamonds. Bob wins.
    void Prints::printLastTurn() {
        cout << log[logIndex - 1] << "\n";
    }

// prints all the turns played one line per turn (same format as game.printLastTurn())
    void Prints::printLog() {
        for (int i = 0; i < logIndex; ++i) {
            cout << log[i] << "\n";
        }
    }

// for each player prints basic statistics: win rate, cards won, <other stats you want to print>. Also print the draw rate and amount of draws that happand. (draw within a draw counts as 2 draws. )
    void Prints::printStats(Player player1, Player player2) {

        cout << setw(15) << "Win rate:" << setw(15) << fixed << setprecision(2)
             << (double) (player1.getRate() * 100) << "%" << "\n";
        cout << setw(15) << "Player:" << setw(15) << player1.getName() << "\n";
        cout << setw(15) << "Cards won:" << setw(15) << player1.cardesTaken() << "\n";
        cout << setw(15) << "Cards left:" << setw(15) << player1.stacksize() << "\n\n";


        cout << setw(15) << "Win rate:" << setw(15) << fixed << setprecision(2)
             << (double) (player2.getRate() * 100) << "%" << "\n";
        cout << setw(15) << "Player:" << setw(15) << player2.getName() << "\n";
        cout << setw(15) << "Cards won:" << setw(15) << player2.cardesTaken() << "\n";
        cout << setw(15) << "Cards left:" << setw(15) << player2.stacksize() << "\n\n";


        cout << setw(15) << "Draw rate:" << setw(15) << fixed << setprecision(2)
             << (double) ((double) drawAmount / logIndex) * 100 << "%" << "\n";
        cout << setw(15) << "Amount of Draw:" << setw(15) << drawAmount << "\n\n";
    }

    void Prints::printWiner(Player player1, Player player2) {
        if (player1.cardesTaken() > player2.cardesTaken()) {
            cout << player1.getName() << "\n";
        } else if (player2.cardesTaken() > player1.cardesTaken()) {
            cout << player2.getName() << "\n";
        } else {
            throw invalid_argument("===============> ERROR:: There is No Winner <===============");
        }
    }

    void Prints::saveLog(Player player1, Player player2, short winnerPerRound) {
        if (winnerPerRound == 0) {
            str += player1.getName() + " played " + player1.getCard().getNumber() + " of " +
                   player1.getCard().getSymbol() + " " +
                   player2.getName() + " played " + player2.getCard().getNumber() + " of "
                   + player2.getCard().getSymbol() + ".";
        } else {
            str = player1.getName() + " played " + player1.getCard().getNumber() + " of " +
                  player1.getCard().getSymbol() + " " +
                  player2.getName() + " played " + player2.getCard().getNumber() + " of "
                  + player2.getCard().getSymbol() + ".";
        }
    }

    void Prints::myPrint(Player player1, Player player2, short winnerPerRound) {
        cout << "["
             << player1.getCard().getNumber()
             << ","
             << winnerPerRound
             << ","
             << player2.getCard().getNumber()
             << ","
             << player1.stacksize() + player1.cardesTaken() + player2.stacksize() + player2.cardesTaken()
             << "] ";
    }

    string Prints::getStr() {
        return this->str;
    }

    string *Prints::getLog() {
        return this->log;
    }

    int Prints::getDrawAmount() {
        return this->drawAmount;
    }

    void Prints::updateDrawAmount() {
        this->drawAmount++;

    }

    int Prints::getLogIndex() {
        return this->logIndex;

    }

    void Prints::updateLogIndex() {
        this->logIndex++;
    }

    void Prints::setLog(string appendStr) {
        this->log[logIndex] = appendStr;
    }
}