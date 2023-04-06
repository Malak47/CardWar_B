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
#include <iomanip>

using namespace std;


namespace ariel {

    Game::Game() : player1(*new Player()), player2(*new Player()) {
        player1.setName("Player1");
        player2.setName("Player2");
        player1.setStackSize(26);
        player2.setStackSize(26);
        winnerPerRound = 0;
        str = "";
    }

    Game::Game(Player &player1, Player &player2) : player1(player1), player2(player2) {
        this->player1 = player1;
        this->player2 = player2;
        player1.setStackSize(26);
        player2.setStackSize(26);
        winnerPerRound = 0;
        str = "";
    }

    void Game::playAll() {
        while (player1.stacksize() > 0 && player1.stacksize() > 0) {
            playTurn();
        }
    }

    void Game::playTurn() {
        this->setp1Deck(player1.getDeck()[curr]);
        this->setp2Deck(player2.getDeck()[curr]);
        if (winnerPerRound == 0) {
            str += player1.getName() + " played " + player1.getDeck()[curr].getNumber() + " of " +
                   player1.getDeck()[curr].getSymbol() + " " +
                   player2.getName() + " played " + player2.getDeck()[curr].getNumber() + " of "
                   + player2.getDeck()[curr].getSymbol() + ".";
        } else {
            str = player1.getName() + " played " + player1.getDeck()[curr].getNumber() + " of " +
                  player1.getDeck()[curr].getSymbol() + " " +
                  player2.getName() + " played " + player2.getDeck()[curr].getNumber() + " of "
                  + player2.getDeck()[curr].getSymbol() + ".";
        }
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

            this->curr = curr + 1;
            //Draw but still has cards.
            if (winnerPerRound == 0 && player1.stacksize() > 2 && player2.stacksize() > 2) {
                //Skip round
                this->setp1Deck(player1.getDeck()[curr]);
                this->setp2Deck(player2.getDeck()[curr]);
                player1.setStackSize(player1.stacksize() - 1);
                player2.setStackSize(player2.stacksize() - 1);

                this->curr = curr + 1;
                playTurn();
            } else if (winnerPerRound == 0 && player1.stacksize() < 2 && player2.stacksize() < 2) {
                Game game(player1, player2);

                game.playAll();
            }
            log[logIndex] = str;
            if (winnerPerRound != 0) {
                logIndex++;
            }
            player1.setRate((double) (player1.getTotalRoundWins() / logIndex));
            player2.setRate((double) (player2.getTotalRoundWins() / logIndex));
        }
            // Draw -> new game
        else if (player1.stacksize() == 0 && player2.stacksize() == 0 &&
                 player1.cardesTaken() == player2.cardesTaken()) {
            winnerPerRound = 0;
            Game game(player1, player2);
            game.playAll();
        }

    }

//    void Game::playTurn() {
//
//        Errors();
//        bool exit = isValidPlayer(&player1) || isValidPlayer(&player2);
//        if (!exit) {
//            throw invalid_argument("===============> ERROR:: Invalid Players Parameters  <===============");
//        }
//        if (player1.stacksize() <= 0 || player2.stacksize() <= 0) {
//            throw invalid_argument("===============> ERROR:: Invalid Players Parameters  <===============");
//        }
//        // Round is done.
//        playRound();
//        saveLog();
//        CheckWhichCardWins(this->getp1Deck()[curr], this->getp2Deck()[curr]);
//        myPrint();
//        this->curr = curr + 1;
//
//        // if cardsTaken is equal + stack empty-> new game
//        if (player1.stacksize() == 0 && player2.stacksize() == 0 && player1.cardesTaken() == player2.cardesTaken()) {
//            winnerPerRound = 0;
//            Game game2(player1, player2);
//            game2.playAll();
//        }
//        numberOfDrawsPerRound = 0;
//        // if round was Draw
//        while (winnerPerRound == 0) {
//            //Draw but still has cards.
////            if (player1.stacksize() > 1 && player2.stacksize() > 1) {
//            //Skip round
//            playRound();
//            myPrint();
//            this->curr = curr + 1;
//
//            //play round
//            playRound();
//            saveLog();
//            CheckWhichCardWins(this->getp1Deck()[curr], this->getp2Deck()[curr]);
//            numberOfDrawsPerRound++;
//            myPrint();
//            this->curr = curr + 1;
//        }
//
//        if (winnerPerRound == 1) {
//            while (numberOfDrawsPerRound > 0) {
//                player1.updateCardsTaken();
//                player1.updateCardsTaken();
//                numberOfDrawsPerRound--;
//            }
//        } else if (winnerPerRound == 2) {
//            while (numberOfDrawsPerRound > 0) {
//                player2.updateCardsTaken();
//                player2.updateCardsTaken();
//                numberOfDrawsPerRound--;
//            }
//        }
//
//
//        log[logIndex] = str;
//        if (winnerPerRound != 0) {
//            logIndex++;
//        }
//        player1.setRate((double) ((double) player1.getTotalRoundWins() / logIndex));
//        player2.setRate((double) ((double) player2.getTotalRoundWins() / logIndex));
//
//
//    }

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
            player2.updateCardsTaken();
            player2.updateTotalRoundWins();
            str += " " + player2.getName() + " wins.";
        } else if (p1IndexVal == 0 && p2IndexVal == 12) {
            winnerPerRound = 1;
            player1.updateCardsTaken();
            player1.updateTotalRoundWins();
            str += " " + player1.getName() + " wins.";
        } else if (p1IndexVal > p2IndexVal) {
            winnerPerRound = 1;
            player1.updateCardsTaken();
            player1.updateTotalRoundWins();
            str += " " + player1.getName() + " wins.";
        } else if (p1IndexVal < p2IndexVal) {
            winnerPerRound = 2;
            player2.updateCardsTaken();
            player2.updateTotalRoundWins();
            str += " " + player2.getName() + " wins.";
        } else {
            winnerPerRound = 0;
            drawAmount++;
            //numberOfDrawsPerRound++;
            str += " Draw. ";
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

// Alice played Queen of Hearts Bob played 5 of Spades. Alice wins.
// Alice played 6 of Hearts Bob played 6 of Spades. Draw. Alice played 10 of Clubs Bob played 10 of Diamonds. draw. Alice played Jack of Clubs Bob played King of Diamonds. Bob wins.
    void Game::printLastTurn() {
        cout << log[logIndex - 1] << "\n";
    }

// prints all the turns played one line per turn (same format as game.printLastTurn())
    void Game::printLog() {
        for (int i = 0; i < logIndex; ++i) {
            cout << log[i] << "\n";
        }
    }

// for each player prints basic statistics: win rate, cards won, <other stats you want to print>. Also print the draw rate and amount of draws that happand. (draw within a draw counts as 2 draws. )
    void Game::printStats() {

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

    void Game::printWiner() {
        if (player1.cardesTaken() > player2.cardesTaken()) {
            cout << player1.getName() << "\n";
        } else if (player2.cardesTaken() > player1.cardesTaken()) {
            cout << player2.getName() << "\n";
        } else {
            throw invalid_argument("===============> ERROR:: There is No Winner <===============");
        }
    }

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

        for (int l = 0; l < 26; ++l) {
            cout << "[" << player1.getDeck()[l].getNumber() << "," << player2.getDeck()[l].getNumber() << "] ";
        }
        cout << "\n\n";
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

    void Game::saveLog() {
        if (winnerPerRound == 0) {
            str += player1.getName() + " played " + player1.getDeck()[curr].getNumber() + " of " +
                   player1.getDeck()[curr].getSymbol() + " " +
                   player2.getName() + " played " + player2.getDeck()[curr].getNumber() + " of "
                   + player2.getDeck()[curr].getSymbol() + ".";
        } else {
            str = player1.getName() + " played " + player1.getDeck()[curr].getNumber() + " of " +
                  player1.getDeck()[curr].getSymbol() + " " +
                  player2.getName() + " played " + player2.getDeck()[curr].getNumber() + " of "
                  + player2.getDeck()[curr].getSymbol() + ".";
        }
    }

    void Game::playRound() {
        this->setp1Deck(player1.getDeck()[curr]);
        this->setp2Deck(player2.getDeck()[curr]);
        player1.setStackSize(player1.stacksize() - 1);
        player2.setStackSize(player2.stacksize() - 1);
    }

    void Game::myPrint() {
        cout << "["
             << player1.getDeck()[curr].getNumber()
             << ","
             << winnerPerRound
             << ","
             << player2.getDeck()[curr].getNumber()
             << ","
             << player1.stacksize() + player1.cardesTaken() + player2.stacksize() + player2.cardesTaken()
             << "] ";
    }
}