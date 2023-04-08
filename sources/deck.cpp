//
// Created by malaklinux on 4/8/23.
//
#include <string>
#include "deck.hpp"
#include <random>
#include <algorithm>
#include <iostream>

using namespace std;

namespace ariel {

    Deck::Deck() {
        createDeck();
    }

    void Deck::shuffleDeck() {
        unsigned seed = time(nullptr);
        shuffle(&(this->deck[0]), &(this->deck[51]), default_random_engine(seed));
    }

    void Deck::createDeck() {
        string number[13]{"2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace"};
        string symbol[4]{"Hearts", "Spades", "Clubs", "Diamonds"};
        int i = 0, j = 0;
        unsigned long k = 0;
        while (i < 4) {
            while (j < 13) {
                this->deck[k++] = Card(number[j++], symbol[i]);
            }
            j = 0;
            i++;
        }

    }

    Card *Deck::getDeck() {
        return this->deck.data();
    }

    void Deck::printDeckCards() {
        int i = 0;
        while (i < 52) {
            cout << getDeck()[i++].getNumber() << " ";
        }
    }

}

