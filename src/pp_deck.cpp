#include <algorithm>
#include "pp_deck.h"

Deck::Deck(bool standardDeck, bool shuffled)
{
    if (standardDeck)
    {
        AddCard({HEART, ACE});
        AddCard({HEART, ACE});
        AddCard({HEART, TWO});
        AddCard({HEART, THREE});
        AddCard({HEART, FOUR});
        AddCard({HEART, FIVE});
        AddCard({HEART, SIX});
        AddCard({HEART, SEVEN});
        AddCard({HEART, EIGHT});
        AddCard({HEART, NINE});
        AddCard({HEART, TEN});
        AddCard({HEART, JACK});
        AddCard({HEART, QUEEN});
        AddCard({HEART, KING});
        AddCard({DIAMOND, ACE});
        AddCard({DIAMOND, TWO});
        AddCard({DIAMOND, THREE});
        AddCard({DIAMOND, FOUR});
        AddCard({DIAMOND, FIVE});
        AddCard({DIAMOND, SIX});
        AddCard({DIAMOND, SEVEN});
        AddCard({DIAMOND, EIGHT});
        AddCard({DIAMOND, NINE});
        AddCard({DIAMOND, TEN});
        AddCard({DIAMOND, JACK});
        AddCard({DIAMOND, QUEEN});
        AddCard({DIAMOND, KING});
        AddCard({CLUB, ACE});
        AddCard({CLUB, TWO});
        AddCard({CLUB, THREE});
        AddCard({CLUB, FOUR});
        AddCard({CLUB, FIVE});
        AddCard({CLUB, SIX});
        AddCard({CLUB, SEVEN});
        AddCard({CLUB, EIGHT});
        AddCard({CLUB, NINE});
        AddCard({CLUB, TEN});
        AddCard({CLUB, JACK});
        AddCard({CLUB, QUEEN});
        AddCard({CLUB, KING});
        AddCard({SPADE, ACE});
        AddCard({SPADE, TWO});
        AddCard({SPADE, THREE});
        AddCard({SPADE, FOUR});
        AddCard({SPADE, FIVE});
        AddCard({SPADE, SIX});
        AddCard({SPADE, SEVEN});
        AddCard({SPADE, EIGHT});
        AddCard({SPADE, NINE});
        AddCard({SPADE, TEN});
        AddCard({SPADE, JACK});
        AddCard({SPADE, QUEEN});
        AddCard({SPADE, KING});

        if (shuffled)
        {
            Shuffle();
        }
    }
}

void Deck::Shuffle()
{
    std::random_shuffle(cards.begin(), cards.end());
}

void Deck::Clear()
{
    cards.clear();
}

bool Deck::IsEmpty()
{
    return cards.empty();
}

int Deck::Size()
{
    return cards.size();
}

void Deck::AddCard(PlayingCard card)
{
    cards.push_back(card);
}

void Deck::AddCardAt(PlayingCard card, int index)
{
    cards.insert(cards.begin() + index, card);
}

void Deck::MoveTopCards(Deck &destinationDeck, int count)
{
    for (int i = 0; i < count; i++)
    {
        if (!IsEmpty())
        {
            destinationDeck.AddCard(cards.back());
            cards.pop_back();
        }
    }
}

void Deck::MoveCardAt(Deck &targetDeck, int index)
{
    targetDeck.AddCard(cards.at(index));
    cards.erase(cards.begin() + index);
}

void Deck::MoveTopCardTo(Deck &destinationDeck, int destinationIndex)
{
    destinationDeck.AddCardAt(cards.back(), destinationIndex);
    cards.pop_back();
}

PlayingCard &Deck::CardAt(int index)
{
    return cards.at(index);
}
