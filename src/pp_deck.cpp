#include <algorithm>
#include "pp_deck.h"

void Deck::Shuffle()
{
    std::random_shuffle(cards.begin(), cards.end());
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

void Deck::MoveTopCards(Deck& destinationDeck, int count)
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

void Deck::MoveCardAt(Deck& targetDeck, int index)
{
    targetDeck.AddCard(cards.at(index));
    cards.erase(cards.begin() + index);
}

void Deck::MoveTopCardTo(Deck& destinationDeck, int destinationIndex)
{
    destinationDeck.AddCardAt(cards.back(), destinationIndex);
    cards.pop_back();
}

PlayingCard& Deck::CardAt(int index)
{
    return cards.at(index);
}
