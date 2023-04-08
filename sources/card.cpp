//
// Created by malaklinux on 3/27/23.
//
#include "card.hpp"

namespace ariel {
    Card::Card() {
    }

    Card::Card(string number, string symbol) {
        this->number = number;
        this->symbol = symbol;
    }

    string Card::getSymbol() {
        return this->symbol;
    }

    string Card::getNumber() {
        return this->number;
    }


    void Card::setNumber(string number) {
        this->number = number;
    }

    void Card::setSymbol(string symbol) {
        this->symbol = symbol;
    }
}