#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
#include<random>
// Define a Card structure e.g {Spades,'Two',2}
struct card{
        std::string Cardtype;
        std::string Cardname;
        int Value;
};
// Define a Class that will create  player objects
class player{
    private:
        std::string name = "Player";
        int money = 100;
        std::vector<card> cards;
    public:
        // Game Related functions
        void hit(std::vector<card>& cards, std::vector<card>& deck,int &Drawn_Card,int &Hand);
        void d_hit(std::vector<card>& cards, std::vector<card>& deck,int &Drawn_Card,int &Hand,bool &d_turn);
        void p_hand(std::vector<card>& cards, int &Hand);
        void d_hand(std::vector<card>& cards);
        // Getter & Setters for class
        std::string &get_name();
        void set_name(std::string name1);
        int &get_money();
        void set_money(int money1);
        std::vector<card> &get_cards();
        void set_cards(std::vector<card> Carddeck);
}; 
// General functions
void shuffle(std::vector<card>& Deck);
int  result(int P_hand,int D_hand);
void bet_raise(int amount, int &p_money,int &d_money);
void bet_r(int r,int bet, int &p_money,int &d_money);
void add_deck(std::vector<card>& deck,std::vector<card>& p_cards,std::vector<card>& d_cards);
void check_money(player person);