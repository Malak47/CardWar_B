//
// Created by malaklinux on 3/27/23.
//
#include "game.hpp"
#include <string>
#include "iostream"

using namespace std;

namespace ariel {

//--------------------------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------C O N S T R U C T O R-------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------------------
    Game::Game(Player &player1, Player &player2) : player1(player1), player2(player2) {
        this->player1 = player1;
        this->player2 = player2;
        player1.setStackSize(26);
        player2.setStackSize(26);
        deck.shuffleDeck();
        setPlayersDecks();
        this->winnerPerRound = 0;
    }

//--------------------------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------G E T S   &   S E T S-------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------------------
    void Game::setPlayersDecks() {
        int i = 0;
        if (&player1 == &player2) {
            return;
        }
        while (i < 52) {
            player1.setDeck(deck.getDeck()[i++]);
            player2.setDeck(deck.getDeck()[i++]);
        }
        player1.resetPlayerIterator();
        player2.resetPlayerIterator();
    }

//--------------------------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------G A M E    P L A Y----------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------------------
    void Game::playAll() {
        while (player1.stacksize() > 0 && player2.stacksize() > 0) {
            playTurn();
        }
    }

    void Game::playTurn() {
        Errors();
        int cardsToAdd = 0;
        bool flag = true;
        if (player1.stacksize() > 0 && player2.stacksize() > 0) {
            playRound(flag);
            cardsToAdd++;

            //Draw but still has cards.
            if (winnerPerRound == 0) {
                while (player1.stacksize() > 1 && player2.stacksize() > 1 && winnerPerRound == 0) {
                    //Skip round
                    flag = false;
                    playRound(flag);
                    cardsToAdd++;

                    //Play round
                    flag = true;
                    playRound(flag);
                    cardsToAdd++;
                }
                if (player1.stacksize() < 2 && player2.stacksize() < 2 && winnerPerRound == 0) {
                    player1.updateCardsTaken(1);
                    player2.updateCardsTaken(1);
                }
            }
            if (winnerPerRound == 1) {
                player1.updateCardsTaken(cardsToAdd * 2);
            } else if (winnerPerRound == 2) {
                player2.updateCardsTaken(cardsToAdd * 2);
            } else if (player1.stacksize() < 2 && player2.stacksize() < 2) {
                player1.updateCardsTaken(cardsToAdd);
                player2.updateCardsTaken(cardsToAdd);
            }
            prints.setLog(prints.getStr());
            if (winnerPerRound != 0) {
                prints.updateLogIndex();
            }
            player1.setRate(((double) player1.getTotalRoundWins() / prints.getLogIndex()));
            player2.setRate(((double) player2.getTotalRoundWins() / prints.getLogIndex()));
        } else {
            throw invalid_argument("===============> ERROR:: Invalid Game <===============");
        }
    }

    void Game::playRound(bool flag) {
        player1.setStackSize(player1.stacksize() - 1);                                           //stack--
        player2.setStackSize(player2.stacksize() - 1);                                           //stack--
        if (flag) {
            prints.saveLog(player1, player2, winnerPerRound);
            CheckWhichCardWins(player1.getCard(), player2.getCard());
        }
        player1.updatePlayerIterator();                                                             //iter++
        player2.updatePlayerIterator();                                                             //iter++
    }


//--------------------------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------Card Deck Functions---------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------------------
    void Game::CheckWhichCardWins(Card p1Card, Card p2Card) {
        int p1IndexVal = 0, p2IndexVal = 0, i = 0;
        string number[13]{"2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace"};
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
            player2.updateTotalRoundWins();
            prints.getStr() += " " + player2.getName() + " wins.";
        } else if (p1IndexVal == 0 && p2IndexVal == 12) {
            winnerPerRound = 1;
            player1.updateTotalRoundWins();
            prints.getStr() += " " + player1.getName() + " wins.";
        } else if (p1IndexVal > p2IndexVal) {
            winnerPerRound = 1;
            player1.updateTotalRoundWins();
            prints.getStr() += " " + player1.getName() + " wins.";
        } else if (p1IndexVal < p2IndexVal) {
            winnerPerRound = 2;
            player2.updateTotalRoundWins();
            prints.getStr() += " " + player2.getName() + " wins.";
        } else {
            winnerPerRound = 0;
            prints.updateDrawAmount();
            prints.getStr() += " Draw. ";
        }

    }

//--------------------------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------Handling Errors-------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------------------
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
        if (player1.getCard().getNumber() == player2.getCard().getNumber() &&
            player1.getCard().getSymbol() == player2.getCard().getSymbol()) {
            throw invalid_argument("===============> ERROR:: Players With The Same Card <===============");
        }
        if (&(player1) == &(player2)) {
            throw invalid_argument("===============> ERROR:: One Player In The Game <===============");
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

//--------------------------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------P R I N T S-----------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------------------

    void Game::printLastTurn() {
        if (player1.stacksize() == 26 && player2.stacksize() == 26) {
            cout << "===============> WARNING:: Game Has Not Started Yet <===============\n";
            return;
        }
        prints.printLastTurn();
    }

    void Game::printLog() {
        if (player1.stacksize() == 26 && player2.stacksize() == 26) {
            cout << "===============> WARNING:: Game Has Not Started Yet <===============\n";
            return;
        }
        prints.printLog();
    }

    void Game::printStats() {
        if (player1.stacksize() == 26 && player2.stacksize() == 26) {
            cout << "===============> WARNING:: Game Has Not Started Yet <===============\n";
            return;
        }
        prints.printStats(player1, player2);
    }

    void Game::printWiner() {
        prints.printWiner(player1, player2);
    }

    void Game::myPrint() {
        prints.myPrint(player1, player2, winnerPerRound);
    }
}