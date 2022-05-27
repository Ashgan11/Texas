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
    Card otherStack[7]{
        Card(3, 2),
        Card(4, 0),
        Card(4, 1),
        Card(7, 1),
        Card(7, 2),
        Card(13, 1),
        Card(13, 3)
    };
    Hand h(stack);
    //Hand h(otherStack);
    h.getName();
    std::cout << h.toString();
    std::cout << h.getName();
    return 0;
}