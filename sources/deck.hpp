//
// Created by malaklinux on 4/8/23.
//

#ifndef S_S_B_2A_DECK_H
#define S_S_B_2A_DECK_H

#include <array>
#include "card.hpp"

using namespace std;

namespace ariel {
    const int deckCardsNumber = 52;

    class Deck {
    private:
        array<Card, deckCardsNumber> deck;

    public:
        Deck();

        void shuffleDeck();

        void createDeck();

        Card *getDeck();

        void printDeckCards();
    };
}
#endif //S_S_B_2A_DECK_H
