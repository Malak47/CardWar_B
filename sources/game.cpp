//
// Created by malaklinux on 3/27/23.
//
#include "game.hpp"
#include "card.hpp"
#include <string>
#include <stdexcept>
#include <random>
#include <algorithm>
#include "iostream"

using namespace std;


namespace ariel {
    //string number[]{"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};
    //string symbol[]{"Hearts♥", "Diamonds♦", "Spades♠", "Clubs♣"};
//    string symbol[]{"♥", "♦", "♠", "♣"};

    Game::Game() : player1(*new Player()), player2(*new Player()) {
        player1.setName("Player1");
        player2.setName("Player2");
        player1.setStackSize(26);
        player2.setStackSize(26);
        winnerPerRound = 0;
    }

    Game::Game(Player &player1, Player &player2) : player1(player1), player2(player2) {
        this->player1 = player1;
        this->player2 = player2;
        player1.setStackSize(26);
        player2.setStackSize(26);
        winnerPerRound = 0;
    }

    void Game::playAll() {
        while (player1.stacksize() > 0 && player1.stacksize() > 0) {
            playTurn();

        }
    }

    void Game::playTurn() {
        this->setp1Deck(player1.getDeck()[curr]);
        this->setp2Deck(player2.getDeck()[curr]);

        Errors();
        bool exit = isValidPlayer(&player1) || isValidPlayer(&player2);
        if (!exit) {
            throw invalid_argument("===============> ERROR:: Invalid Players Parameters  <===============");
        }
        if (player1.stacksize() <= 0 || player2.stacksize() <= 0) {
            throw invalid_argument("===============> ERROR:: Invalid Players Parameters  <===============");
        }

        if (player1.stacksize() > 0 && player2.stacksize() > 0) {
            player1.setStackSize(player1.stacksize() - 1);
            player2.setStackSize(player2.stacksize() - 1);
            CheckWhichCardWins(this->getp1Deck()[curr], this->getp2Deck()[curr]);
            cout << player1.getDeck()[curr].getNumber() << " " << winnerPerRound << " " << player2.getDeck()[curr].getNumber() << "-\n";
            this->curr = curr + 1;
            //Draw but still has cards.
            if (winnerPerRound == 0 && player1.stacksize() > 2 && player2.stacksize() > 2) {
                //Skip round
                this->setp1Deck(player1.getDeck()[curr]);
                this->setp2Deck(player2.getDeck()[curr]);
                player1.setStackSize(player1.stacksize() - 1);
                player2.setStackSize(player2.stacksize() - 1);
                cout << player1.getDeck()[curr].getNumber() << " " << winnerPerRound << " " << player2.getDeck()[curr].getNumber() << "--\n";
                this->curr = curr + 1;
                playTurn();
            } else if (winnerPerRound == 0 && player1.stacksize() < 2 && player2.stacksize() < 2) {
                Game game(player1, player2);
                cout << player1.getDeck()[curr].getNumber() << " " << winnerPerRound << " " << player2.getDeck()[curr].getNumber() << "---\n";

                game.playAll();
            }

        }
            // Draw -> new game
        else if (player1.stacksize() == 0 && player2.stacksize() == 0 &&
                 player1.cardesTaken() == player2.cardesTaken()) {
            winnerPerRound = 0;
            Game game(player1, player2);
            game.playAll();
        }

    }

/*    void Game::startGame(){
        this->setp1Deck(player1.getDeck()[curr]);
        this->setp2Deck(player2.getDeck()[curr]);

    }*/
    void Game::CheckWhichCardWins(Card p1Card, Card p2Card) {
        int p1IndexVal = 0, p2IndexVal = 0, i = 0;

        while (i < 13) {
            if (p1Card.getNumber() == number[i]) {
                p1IndexVal = i;
                break;
            }
            i++;
        }
        i = 0;
        while (i < 13) {
            if (p2Card.getNumber() == number[i]) {
                p2IndexVal = i;
                break;
            }
            i++;
        }
        if (p1IndexVal == 12 && p2IndexVal == 0) {
            winnerPerRound = 2;
        } else if (p1IndexVal == 0 && p2IndexVal == 12) {
            winnerPerRound = 1;
        } else if (p1IndexVal > p2IndexVal) {
            winnerPerRound = 1;
        } else if (p1IndexVal < p2IndexVal) {
            winnerPerRound = 2;
        } else {
            winnerPerRound = 0;
        }
    }

    void Game::setp1Deck(Card card) {

        this->p1Deck[this->p1++] = card;
    }

    void Game::setp2Deck(Card card) {
        this->p2Deck[this->p2++] = card;
    }

    Card *Game::getp1Deck() {
        return this->p1Deck;
    }

    Card *Game::getp2Deck() {
        return this->p2Deck;
    }


    void Game::printLastTurn() { return; }

    void Game::printLog() { return; }

    void Game::printStats() { return; }

    void Game::printWiner() { return; }

    void Game::shuffleDeck() {
        Card deck[52];
        createCards(deck);
        unsigned seed = time(nullptr);
        shuffle(&(deck[0]), &(deck[51]), default_random_engine(seed));
        Card p1_cards[26], p2_cards[26];
        int i = 0, j = 0, k = 0;

        while (k < 52) {
            p1_cards[i++] = deck[k++];
            p2_cards[j++] = deck[k++];
        }

        player1.setDeck(p1_cards);
        player2.setDeck(p2_cards);

        //PRINT CARDS OF EACH PLAYER !!
        k = 0;
        cout << "PLAYER1" << "\n";
        while (k < 26) {
            cout << p1_cards[k].getNumber() << "" << p1_cards[k].getSymbol() << " ";
            k++;
        }
        k = 0;
        cout << "\n" << "PLAYER2" << "\n";
        while (k < 26) {
            cout << p2_cards[k].getNumber() << "" << p2_cards[k].getSymbol() << " ";
            k++;
        }
        cout << "\n";
/*        k = 0;
        while (k < 26) {
            cout << player1.getCard()->getNumber();
            k++;
        }*/

    }

    void Game::Errors() {
        if (!isValidPlayer(&player1)) {
            throw invalid_argument("===============> ERROR:: Invalid Player 1 <===============");
        }
        if (!isValidPlayer(&player2)) {
            throw invalid_argument("===============> ERROR:: Invalid Player 2 <===============");
        }
        if (player1.stacksize() != player2.stacksize()) {
            throw invalid_argument("===============> ERROR:: Players Have Unequal Stack Sizes <===============");
        }
        if (player1.cardesTaken() + player2.cardesTaken() > 52) {
            throw invalid_argument("===============> ERROR:: Too Many Cards Have Been Taken <===============");
        }
    }

    bool Game::isValidPlayer(Player *player) {
        if (!player || player->stacksize() < 0 || player->stacksize() > 26 ||
            player->cardesTaken() < 0 || player->cardesTaken() > 52 ||
            player->getRate() < 0 || player->getName().empty()) {
            return false;
        }
        return true;
    }

    Card *Game::createCards(Card deck[]) {
        int i = 0, j = 0, k = 0;
        while (i < 4) {
            while (j < 13) {
                deck[k++] = Card(number[j++], symbol[i]);
            }
            j = 0;
            i++;
        }
        return deck;
    }

/*    void Game::setWinner(short winner) {
        this->winnerPerRound = winner;
    }

    short Game::getWinner() {
        return this->winnerPerRound;
    }*/

}