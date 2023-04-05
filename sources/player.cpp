//
// Created by malaklinux on 3/27/23.
//
#include <string>
#include "player.hpp"
#include <stdexcept>

using namespace std;
namespace ariel {
    Player::Player() {
        this->name = "Unknown" + std::to_string(std::rand() % 10 + 1);  //Giving the player name: Unknown+random number
        this->stack_size = 0;
        this->cards_taken = 0;
        this->win_rate = 0;
        this->total_round_wins = 0;
        this->deck = NULL;
    }

    Player::Player(string name) {
        this->name = name;
        this->stack_size = 0;
        this->cards_taken = 0;
        this->win_rate = 0;
        this->total_round_wins = 0;
        this->deck = NULL;
    }

    void Player::setName(string name) {
        this->name = name;
    }

    void Player::setRate(double rate) {
        this->win_rate = rate;
    }

    void Player::updateTotalRoundWins() {
        this->total_round_wins++;
    }

    string Player::getName() {
        return this->name;
    }

    void Player::setStackSize(int size) {
        this->stack_size = size;
    }

    void Player::updateCardsTaken() {
        this->cards_taken++;
    }

    int Player::stacksize() {
        return this->stack_size;
    }

    int Player::cardesTaken() {
        return this->cards_taken;
    }

    double Player::getRate() {
        return this->win_rate;
    }

    int Player::getTotalRoundWins() {
        return this->total_round_wins;
    }

    Card *Player::getDeck() {
        if (stack_size < 0) {
            throw invalid_argument("Player Has No Cards Left.");
        }
        return this->deck;
    }

    void Player::setDeck(Card *cards) {
        this->deck = cards;
    }
}