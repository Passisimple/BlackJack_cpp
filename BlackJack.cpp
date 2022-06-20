#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <random>
#include <limits>
#include "blackjack.h"



int main()
{    
    int const Card_num = 52; // Number of Cards in a deck
    int const Card_Type = 4; // Type of Cards
    int const Card_Typenum = Card_num/Card_Type; // How many cards of that type!
    std::string const CardTypes[4] = {"Clubs","Diamonds","Hearts","Spades"};
    std::string const CardNames[13] = {"Ace","Two","Three","Four","Five","Six","Seven","Eight","Nine","Ten","Jack","Queen","King"};
    // initialize the game
    bool new_game = true;
    while (new_game)
    {
    player player1;    // Define a player!
    player Dealer;     // Dealer Defined!
    Dealer.set_name("Dealer");
    Dealer.set_money(100);
    // initialize the deck with struct card variables
    std::vector<card> Deck(Card_num);
    for (int i=0 ;i < Card_num;i++){
        int Cardvalue = i%Card_Typenum+1;
        int Typecount = i/Card_Typenum;

        Deck[i].Cardtype = CardTypes[Typecount]; // Assigning Card Type
        if (Cardvalue<=10){ // Assigning Card Value
            Deck[i].Value = Cardvalue; }
        else{
            Deck[i].Value = 10; // Maximum Value Possible except Ace  
        }
        Deck[i].Cardname = CardNames[Cardvalue-1]; //Assining Cardname
    };
    // Intro
    std::cout << "**************   Welcome to BLACKJACK!!   **************" << std::endl;
    std::cout << "**************Written by Ali Fatih Kuloğlu**************" << std::endl;
    std::cout << "**************         20/06/2022         **************" << std::endl;
    std::cout << "Minimum bet is 5$!" << std::endl;
    std::cout << "Do you want to enter your name and set your money? (y/n)" << std::endl;
    

    std::string input;
    int input_num;
    std::cin >> input;
    if ((input == "y") || (input == "Y")){
        std::cout << "Enter the name!" << std::endl;
        std::cin >> input; 
        player1.set_name(input);
        std::cout << "Enter the Money!" << std::endl;
        // Forcing an integer output here!
            while(!(std::cin >> input_num) || (input_num<5)){ // First Term Creates an error state
            std::cin.clear(); // clear the error state
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the input
            std::cout << "Invalid input. Must be an integer that is greater then 5. Try again: " << std::endl;
        }
        player1.set_money(input_num);
    }
    
    bool new_round = true;
    while (new_round){
        // Initialize round variables
        int P_hand = 0;
        int D_hand = 0;
        int Drawn_Card = 0;
        bool player_move = true; // Players & Dealers ability take cards. Two Flags determine when the round will end
        bool Dealer_move = true;
        int bet_p = 5;
        int total_bet = bet_p*2; 
        // Set some references to private member functions
        std::vector<card> &player_cards = player1.get_cards();
        std::vector<card> &dealer_cards = Dealer.get_cards();
        int &p_money = player1.get_money();
        int &d_money = Dealer.get_money();
        // Checking if players have enough money to bet for minimum amount
        if ((p_money-bet_p <0)){
        std::cout << player1.get_name() << " doesn't have enough left..." ;
        std::cout << " can't start a new round" << std::endl;
        new_round = false; // if there is no money set the round flag to 0 end finish the game 
        break;
        }
        else if  (d_money-bet_p <0)
        {
        std::cout << "Congrats " << player1.get_name() << " you emptied the safe. ";
        std::cout <<Dealer.get_name() << " doesn't have enough money left..." ;
        std::cout << " Can't start a new round" << std::endl;
        new_round = false; 
        break;
        }

        std::cout << "New round...." << std::endl;
        // Shuffle the deck & bet
        shuffle(Deck);
        bet_raise(bet_p,p_money,d_money);
        // Deal the cards. For multiple player vector notation can easily be achieved.
        for(int i=0;i<2;++i){
            player1.hit(player_cards,Deck,Drawn_Card,P_hand);
            Dealer.hit(dealer_cards,Deck,Drawn_Card,D_hand);
        }

        player1.p_hand(player_cards,P_hand);
        while(player_move || Dealer_move){
            std::cout << "------------------------------- \n" ;
            std::cout << " Menu: " << std::endl;
            std::cout << " Press 1 to check your hand! \n Press 2 to say 'Hit me' \n Press 3 to check dealer's hand \n " ;
            std::cout << "Press 4 to pass your turn \n Press 5 to increase the bet! \n Press 6 to check your money \n ";
            std::cout << "Press 7 to check dealer's money \n Press 8 to start a new game \n Press 9 to quit! \n";
            std::cout << "------------------------------- \n" ;
            // Forcing User to enter an integer from the menu
            while(!(std::cin >> input_num)){
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Must be an integer. Try again: " << std::endl;
            }

            // Dorwn below is self-exlanatory; calling functions & setting flags
            switch (input_num)
            {
            case 1:
                player1.p_hand(player_cards,P_hand);
                break;
            case 2:
                if (Drawn_Card == 52){
                    std::cout << "There isn't any card left in the deck. Very funny!." << std::endl;
                    player_move = false;
                    Dealer_move = false;
                    break;
                }
                if (player_move){
                player1.hit(player_cards,Deck,Drawn_Card,P_hand);
                Dealer.d_hit(dealer_cards,Deck,Drawn_Card,D_hand,Dealer_move);
                }
                else {
                    std::cout << "You passed last turn. Dealer decides now." << std::endl;
                    Dealer.d_hit(dealer_cards,Deck,Drawn_Card,D_hand,Dealer_move);
                }
                break;
            case 3:
                Dealer.d_hand(dealer_cards);
                break;
            case 4:
                if (Drawn_Card == 52){
                    std::cout << "There isn't any card left in the deck. Very funny!." << std::endl;
                    player_move = false;
                    Dealer_move = false;
                    break;
                }
                Dealer.d_hit(dealer_cards,Deck,Drawn_Card,D_hand,Dealer_move);
                player_move = false;
                break;
            case 5:
                std::cout << "Please Enter the amount you wish to increase." << std::endl;
                while(!(std::cin >> input_num) || (input_num >= (std::min(p_money,d_money)))){
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Input must be an integer and bet can't be higher than yours or Dealer's remaining money";
                std::cout << " which is " << std::min(p_money,d_money) << " dollars. Try again: " << std::endl;
                }
                total_bet += input_num*2;
                bet_raise(input_num,p_money,d_money);
                break;
            case 6:
                check_money(player1);
                break;
            case 7:
                check_money(Dealer);
                break;
            case 8:
                std::cout << "Okay. Starting a new game!" << std::endl;
                player_move = false;
                Dealer_move = false;
                new_round = false;
                goto exit_loop;
                break;
            case 9:
                std::cout << "Goodbye!" << std::endl;
                return 0;
                break;
            default:
                std::cout << "Enter a number on the Menu!" << std::endl;
                break;
            }
        }
        int r = result(P_hand,D_hand); // Game result
        bet_r(r,total_bet,p_money,d_money); // Bet results and returning money to winner
        add_deck(Deck,player_cards,dealer_cards); // Add the cards back to the Deck
    }
    exit_loop: ;
    }
    return 0;
}
