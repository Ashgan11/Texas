#include "PokerGame.h"
#include "CardAndDeck.h"

int main()
{
    //PokerGame game;
    //game.playGame();
    Deck d;
    Card stack[7]{
        d.dealCard(),
        d.dealCard(),
        d.dealCard(),
        d.dealCard(),
        d.dealCard(),
        d.dealCard(),
        d.dealCard()
    };
    Hand h(stack);
    std::cout << h.toString();
    return 0;
}