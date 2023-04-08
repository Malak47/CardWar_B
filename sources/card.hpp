//
// Created by malaklinux on 3/27/23.
//

#ifndef S_S_B_2A_CARD_H
#define S_S_B_2A_CARD_H

#include <string>

using namespace std;

namespace ariel {

    class Card {
    private:
        string symbol;
        string number;

    public:
        Card();

        Card(string number, string symbol);

        string getSymbol();

        string getNumber();

        void setSymbol(string symbol);

        void setNumber(string number);

    };
}
#endif //S_S_B_2A_CARD_H