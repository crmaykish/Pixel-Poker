#ifndef CARD_H
#define CARD_H

enum PlayingCardSuit {HEART, DIAMOND, CLUB, SPADE};
enum PlayingCardValue {TWO = 2, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE};

struct PlayingCard
{
    PlayingCardSuit Suit;
    PlayingCardValue Value;

    bool operator < (const PlayingCard& pc)
    {
        return Value < pc.Value;
    }
};

#endif