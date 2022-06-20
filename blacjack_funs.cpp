#include"blackjack.h"
#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
#include<random>

// Function to shuffle the Deck vector of card structs
void shuffle(std::vector<card>& Deck){
    for (unsigned i = 0; i < Deck.size() - 1; i++)
        {
        std::random_device rd; // random number from random device of the system
        std::mt19937 gen(rd()); // random number generator with Mersenne-Twister engine
        std::shuffle (Deck.begin(), Deck.end(), gen);
        }
};
// adds a card struct to players cards vector from the deck
void player::hit(std::vector<card>& cards, std::vector<card>& deck,int &Drawn_Card,int &Hand){
    cards.push_back(deck.back());
    Drawn_Card += 1; // increase the number of cards drawn from the deck
    deck.pop_back();
    int n    = cards.size(); 
    Hand = 0;
    int nAce = 0;
    for (int i=0;i<n;i++){ // Chcks on How many aces are present in the players hand
        Hand += cards[i].Value;
        if (cards[i].Cardname == "Ace"){
            nAce += 1;
        }
    }
    for (int i = 0; i<nAce; i++){
        if (Hand+10 <= 21){
            Hand += 10;  // Calcuates the maximum value of a hand that does not exceed 21
        }
    }
};
// Prints the players hand and the cards it has
void player::p_hand(std::vector<card> &cards, int &Hand){
    int n = cards.size();
    std::cout << "Your Cards: " << std::endl;
    for (int i = 0 ; i < n ; i++){
    std::cout << cards[i].Cardname<< "   of   "<< cards[i].Cardtype<< std::endl;
    }
    std::cout << "You have ==>   "<<Hand << std::endl;
    if (Hand == 21){
        std::cout << "BLACKJACK!" << std::endl;
    }
    if (Hand > 21){
        std::cout << "Busted!" << std::endl;
    }
}
// Prints the open card of the dealer an number of the cards it has
void player::d_hand(std::vector<card> &cards){
    int n = cards.size();
    std::cout << "Dealer has: "<< cards[0].Cardname<< " of "<< cards[0].Cardtype;
    if (cards[0].Cardname == "Ace"){
        std::cout << " ( " << cards[0].Value << " or " << cards[0].Value+10 << " ) ";
    }
    else {
        std::cout << " ( " << cards[0].Value <<  " ) ";
    }
    std::cout << " and a total of " << n << " cards" << std::endl;
}
// Decider function for dealerto pull or pass
void player::d_hit(std::vector<card>& cards, std::vector<card>& deck,int &Drawn_Card,int &Hand, bool &d_turn){
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> distr(0, 99);
    int rand = distr(gen); // This random number adds uncertainty and a deciding factor
    bool Ace = false;
    int prob[21] = {100,100,100,100,100,100,100,100,100,100,100,100,100,95,80,60,40,20,5,1,0}; // Probability for Dealer to pull cards from 1 to 21
    if (d_turn){
        int n    = cards.size();
        for (int i=0;i<n;i++){
            if (cards[i].Cardname == "Ace"){ // Checks if dealer has ace!
                Ace = true;
                break;
            }
        }
        if (Hand <=21) {
            if (Ace){
                prob[(Hand-1)] *= 2; // Doubles the chance of pulling a card for dealer if it has ace
            }
            if (rand<prob[(Hand-1)]){
                player::hit(cards,deck,Drawn_Card,Hand); //Dealer pulls
                std::cout << "Dealer Takes a Card" << std::endl;
            }
            else
            {   
                std::cout << "Dealer Pass" << std::endl;
                d_turn = false;
            }
        }
        else 
        {   
            std::cout << "Dealer Pass" << std::endl;
            d_turn = false;
        }
    }
}
// Compares the hands and returns th result
int result(int P_hand,int D_hand)
{
    std::cout << "You have " << P_hand <<  " Dealer has " << D_hand << std::endl;
    if (((P_hand > D_hand)&& (P_hand <= 21)) || ((P_hand <= 21) && (D_hand >21)))
    {   
        std::cout << "You won!" << std::endl;
        return 1;
    }
    else if (((D_hand > P_hand)&& (D_hand <= 21)) || ((D_hand <= 21) && (P_hand >21)))
    {
        std::cout << "Dealer won!" << std::endl;
        return 2;
    }
    else
    {
        std::cout << "A Tie!" << std::endl;
        return 0;
    }
    
}
// Checks if players has money to bet and withdraws money
void bet_raise(int amount, int &p_money,int &d_money)
{
    if (((p_money-amount) >= 0) && ((d_money-amount) >= 0)){
        p_money -= amount;
        d_money -= amount;
        std::cout << "Bets are in!" << std::endl;
    }
    else if (p_money-amount <0){
        std::cout << "You don't have enough money." << std::endl;
    }
    else {
        std::cout << "Dealer doesn't have enough money." << std::endl;
    }
}
// prints money variable of the player object
void check_money(player person){
        std::cout << person.get_name() <<" has " << person.get_money() << " dollars left." << std::endl;
}
// Adds total amount of money to member of the winner
void bet_r(int r,int bet, int &p_money,int &d_money){
        if (r==1){
            p_money += bet;
        }
        else if (r==2){
            d_money += bet;
        }
        else {
            p_money += bet/2;
            d_money += bet/2;
        }
}
// returns the cards to the main deck
void add_deck(std::vector<card>& deck,std::vector<card>& p_cards,std::vector<card>& d_cards){
    int p = p_cards.size();
    int d = d_cards.size();
    for (int i = 0; i<p;i++){
        deck.push_back(p_cards.back());
        p_cards.pop_back();
    }
        for (int i = 0; i<d;i++){
        deck.push_back(d_cards.back());
        d_cards.pop_back();
    }
}
// getter and setters for player class. Getters return a reference 
std::string &player::get_name(){
    return name;
}
void player::set_name(std::string name1){
    name = name1;
}
int &player::get_money(){
    return money;
};
void player::set_money(int money1){
    money = money1;
};
std::vector<card> &player::get_cards(){
    return cards;
};
void player::set_cards(std::vector<card> Carddeck){
    cards = Carddeck;
};