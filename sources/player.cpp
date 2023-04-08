//
// Created by malaklinux on 3/27/23.
//
#include <string>
#include "player.hpp"
#include <stdexcept>
#include "iostream"

using namespace std;
namespace ariel {
    Player::Player(string name) {
        this->name = name;
        this->stack_size = 0;
        this->cards_taken = 0;
        this->win_rate = 0;
        this->total_round_wins = 0;
        this->playerIterator = 0;
        //this->initial_cards
    }

    void Player::setName(string name) {
        this->name = name;
    }

    void Player::setRate(double rate) {
        this->win_rate = rate;
    }

    void Player::setDeck(Card card) {
        this->initial_cards[playerIterator++] = card;
    }
    void Player::updatePlayerIterator(){
        this->playerIterator++;
    }
    void Player::resetPlayerIterator(){
        this->playerIterator = 0;
    }

    void Player::setStackSize(int size) {
        this->stack_size = size;
    }

    void Player::updateTotalRoundWins() {
        this->total_round_wins++;
    }

    void Player::updateCardsTaken(int num) {
        this->cards_taken += num;
    }

    string Player::getName() {
        return this->name;
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

    Card Player::getCard() {
        if (stack_size < 0) {
            throw invalid_argument("Player Has No Cards Left.");
        }
        return this->initial_cards[playerIterator];
    }


    Card *Player::getDeck() {
        return this->initial_cards.data();
    }
}