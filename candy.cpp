#include <iostream>
#include <stdexcept>

#include "candy.h"

SpecialCard Card::specialCard() const
{
    if (index_ >= CardIDs::START_SPECIAL)
    {
        return static_cast<SpecialCard>(index_ - CardIDs::START_SPECIAL);
    }

    return SpecialCard::NONE;
}

ColorCard Card::colorCard() const
{
    ColorCard card(Color::RED);

    // Three doubles of each color
    // All doubles mapped to lowest indices
    if (index_ < CardIDs::START_SINGLE_CLRS)
    {
        card.two = true;
        card.color = static_cast<Color>(index_ % NUM_COLORS);
        return card;
    }

    // At least three singles of each color
    // All singles mapped to indices after doubles
    if (index_ < CardIDs::START_EXTRA_SINGLE_CLRS)
    {
        card.color = static_cast<Color>(index_ % NUM_COLORS);
        return card;
    }

    // One extra single of Yellow through Green
    if (index_ < CardIDs::START_SPECIAL)
    {
        card.color = static_cast<Color>((index_ + Color::YELLOW) % NUM_COLORS);
        return card;
    }

    throw std::out_of_range(std::string("Invalid color card index. ") + std::to_string(index_));
}

bool Player::play(const Card& card)
{
    if (SpecialCard::NONE != card.specialCard()) [[unlikely]]
    {
        playSpecial(card.specialCard());
        return false;
    }

    ColorCard color_card = card.colorCard();

    const int cur_color = pos_ % NUM_COLORS;

    // Distance to move.
    const int distance = color_card.color - cur_color;

    // If already at or past new color on current "major frame" then move to
    // next "major frame".
    if (distance <= 0)
    {
        pos_ += NUM_COLORS;
    }

    pos_ += distance;

    if (color_card.two)
    {
        pos_ += NUM_COLORS;
    }

    // Now handle special squares
    switch (pos_) [[unlikely]]
    {
        case 0 * NUM_COLORS + Color::BLUE:
            // Ride the river shortcut
            pos_ += 5 * NUM_COLORS;
            break;
        case 2 * NUM_COLORS + Color::GREEN:
            // Take the dot shortcut
            pos_ += 1 * NUM_COLORS;
            break;
        case 4 * NUM_COLORS + Color::PURPLE:
        case 8 * NUM_COLORS + Color::YELLOW:
            // Licorice
            skip_turn_ = true;
            break;
    }

    // Did player win?
    return pos_ >= 13 * NUM_COLORS;
}

void Player::playSpecial(const SpecialCard& card)
{
    switch (card)
    {
    case SpecialCard::ICECREAM:
        pos_ = 10 * NUM_COLORS + Color::YELLOW;
        break;

    case SpecialCard::LOLLIPOP:
        pos_ = 7 * NUM_COLORS + Color::ORANGE;
        break;

    case SpecialCard::PEANUT:
        pos_ = 5 * NUM_COLORS + Color::RED;
        break;

    case SpecialCard::PEPPERMINT:
        pos_ = 3 * NUM_COLORS + Color::PURPLE;
        break;
    
    default:
        break;
    }

    // Error
    return;
}

Deck::Deck()
{
    for (size_t i = 0; i < NUM_CARDS; i++)
    {
        cards[i] = Card(i);
    }
}

void Deck::shuffle()
{
    std::default_random_engine g(rd());
    std::shuffle(cards.begin(), cards.end(), g);
}
