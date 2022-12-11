#ifndef CANDY_H
#define CANDY_H

#include <array>
#include <random>

enum Color {
    RED,
    PURPLE,
    YELLOW,
    BLUE,
    ORANGE,
    GREEN
};

constexpr int NUM_COLORS = GREEN + 1;

enum struct SpecialCard {
    PEPPERMINT,
    PEANUT,
    ICECREAM,
    LOLLIPOP,
    NONE
};

enum CardIDs
{
    // Three sets of doubles for each color
    START_DBL_CLRS = 0,

    // At least three sets of singles for each color
    START_SINGLE_CLRS = START_DBL_CLRS + 3 * NUM_COLORS,

    // One extra of Yellow through Green
    START_EXTRA_SINGLE_CLRS = START_SINGLE_CLRS + 3 * NUM_COLORS,

    // Four special cards
    START_SPECIAL = START_EXTRA_SINGLE_CLRS + Color::GREEN - Color::YELLOW + 1,

    NUM_CARDS = 44
};

constexpr int MAJOR_CYCLES = 13;

struct ColorCard
{
    ColorCard(Color color, bool two = false) : color(color), two(two) {}
    Color color;
    bool two;

    auto operator<=>(const ColorCard&) const = default;
};

struct Card 
{
    Card(size_t id = 0) : index_(id) {}

    SpecialCard specialCard() const;
    ColorCard colorCard() const;

    size_t index_;
};

struct Deck
{
    Deck();

    void shuffle();

    std::array<Card, NUM_CARDS> cards;
    std::random_device rd;
};


struct Player
{
    int pos_ = -1;
    bool skip_turn_ = false;

    bool play(const Card&);
    void playSpecial(const SpecialCard&);

    auto operator<=>(const Player&) const = default;
};

#endif // CANDY_H