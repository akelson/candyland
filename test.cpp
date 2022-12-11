#include <gtest/gtest.h>

#include "candy.h"

Card make_color(Color color, bool two = false, int instance = 0)
{
    int instance_found = 0;
    for (size_t i = 0; i < NUM_CARDS; i++)
    {
        Card c(i);

        if (SpecialCard::NONE == c.specialCard())
        {
            const ColorCard cc = c.colorCard();
            if (cc.color == color && cc.two == two)
            {
                if (instance_found == instance)
                {
                    return c;
                }
                instance_found++;
            }
        }
    } // end for

    assert(false);
    return Card(0);
}

Card make_special(SpecialCard card)
{
    return Card(CardIDs::START_SPECIAL + static_cast<CardIDs>(card));
}

TEST(TestCandy, special_none)
{
    EXPECT_EQ(SpecialCard::NONE, Card(CardIDs::START_SPECIAL - 1).specialCard());
    EXPECT_NE(SpecialCard::NONE, Card(CardIDs::START_SPECIAL + 0).specialCard());
    EXPECT_NE(SpecialCard::NONE, Card(CardIDs::START_SPECIAL + 1).specialCard());
    EXPECT_NE(SpecialCard::NONE, Card(CardIDs::START_SPECIAL + 2).specialCard());
    EXPECT_NE(SpecialCard::NONE, Card(CardIDs::START_SPECIAL + 3).specialCard());
}

int count(ColorCard c_search, bool two = false)
{
    int count = 0;
    for(size_t i = 0; i < NUM_CARDS; i++)
    {
        const Card c(i);
        if (SpecialCard::NONE == c.specialCard() && c.colorCard() == c_search) count++;
    }
    return count;
}

TEST(TestCandy, count_deck)
{
    // Single colors
    EXPECT_EQ(count(ColorCard(Color::RED)), 3);
    EXPECT_EQ(count(ColorCard(Color::PURPLE)), 3);
    EXPECT_EQ(count(ColorCard(Color::YELLOW)), 4);
    EXPECT_EQ(count(ColorCard(Color::BLUE)), 4);
    EXPECT_EQ(count(ColorCard(Color::ORANGE)), 4);
    EXPECT_EQ(count(ColorCard(Color::GREEN)), 4);

    // Double colors
    EXPECT_EQ(count(ColorCard(Color::RED, true)), 3);
    EXPECT_EQ(count(ColorCard(Color::PURPLE, true)), 3);
    EXPECT_EQ(count(ColorCard(Color::YELLOW, true)), 3);
    EXPECT_EQ(count(ColorCard(Color::BLUE, true)), 3);
    EXPECT_EQ(count(ColorCard(Color::ORANGE, true)), 3);
    EXPECT_EQ(count(ColorCard(Color::GREEN, true)), 3);
}

TEST(TestCandy, play_0)
{
    Player p;
    const Card c = make_color(Color::RED);
    EXPECT_EQ(false, p.play(c));
    EXPECT_EQ(p.pos_, 0);
}

TEST(TestCandy, play_1)
{
    Player p;
    const Card c = make_color(Color::ORANGE);
    EXPECT_EQ(false, p.play(c));
    EXPECT_EQ(p.pos_, 4);
}

TEST(TestCandy, play_2)
{
    Player p;
    const Card c = make_color(Color::RED, true);
    EXPECT_EQ(false, p.play(c));
    EXPECT_EQ(p.pos_, 6);
}

TEST(TestCandy, play_3)
{
    Player p;
    const Card c = make_color(Color::GREEN, true);
    EXPECT_EQ(false, p.play(c));
    EXPECT_EQ(p.pos_, 11);
}

TEST(TestCandy, play_river_shortcut)
{
    Player p;
    EXPECT_EQ(false, p.play(make_color(Color::BLUE)));
    EXPECT_EQ(p.pos_, 33);
}

TEST(TestCandy, play_dot_shortcut)
{
    Player p;
    EXPECT_EQ(false, p.play(make_color(Color::BLUE, true)));
    EXPECT_EQ(false, p.play(make_color(Color::GREEN, true)));
    EXPECT_EQ(p.pos_, 23);
}

TEST(TestCandy, play_win)
{
    Player p;
    EXPECT_EQ(false, p.play(make_color(Color::RED)));
    EXPECT_EQ(false, p.play(make_color(Color::RED)));
    EXPECT_EQ(false, p.play(make_color(Color::RED)));
    EXPECT_EQ(false, p.play(make_color(Color::RED)));
    EXPECT_EQ(false, p.play(make_color(Color::RED)));
    EXPECT_EQ(false, p.play(make_color(Color::RED)));
    EXPECT_EQ(false, p.play(make_color(Color::RED)));
    EXPECT_EQ(false, p.play(make_color(Color::RED)));
    EXPECT_EQ(false, p.play(make_color(Color::RED)));
    EXPECT_EQ(false, p.play(make_color(Color::RED)));
    EXPECT_EQ(false, p.play(make_color(Color::RED)));
    EXPECT_EQ(false, p.play(make_color(Color::RED)));
    EXPECT_EQ(false, p.play(make_color(Color::RED)));
    EXPECT_EQ(true, p.play(make_color(Color::RED)));
}

TEST(TestCandy, play_almost_win)
{
    Player p;
    EXPECT_EQ(false, p.play(make_color(Color::RED)));
    EXPECT_EQ(false, p.play(make_color(Color::RED)));
    EXPECT_EQ(false, p.play(make_color(Color::RED)));
    EXPECT_EQ(false, p.play(make_color(Color::RED)));
    EXPECT_EQ(false, p.play(make_color(Color::RED)));
    EXPECT_EQ(false, p.play(make_color(Color::RED)));
    EXPECT_EQ(false, p.play(make_color(Color::RED)));
    EXPECT_EQ(false, p.play(make_color(Color::RED)));
    EXPECT_EQ(false, p.play(make_color(Color::RED)));
    EXPECT_EQ(false, p.play(make_color(Color::RED)));
    EXPECT_EQ(false, p.play(make_color(Color::RED)));
    EXPECT_EQ(false, p.play(make_color(Color::RED)));
    EXPECT_EQ(false, p.play(make_color(Color::RED)));
    EXPECT_EQ(false, p.play(make_color(Color::GREEN)));
    EXPECT_EQ(true, p.play(make_color(Color::RED)));
}

TEST(TestCandy, play_peppermint)
{
    Player p1;
    EXPECT_EQ(false, p1.play(make_color(Color::YELLOW, true)));
    EXPECT_EQ(false, p1.play(make_color(Color::YELLOW, true)));

    Player p2;
    EXPECT_EQ(false, p2.play(make_color(Color::BLUE, true)));
    EXPECT_EQ(false, p2.play(make_special(SpecialCard::PEPPERMINT)));
    EXPECT_EQ(false, p2.play(make_color(Color::YELLOW)));

    EXPECT_EQ(p1.pos_, p2.pos_);
}

TEST(TestCandy, play_peanut)
{
    Player p1;
    EXPECT_EQ(false, p1.play(make_color(Color::BLUE)));

    Player p2;
    EXPECT_EQ(false, p2.play(make_special(SpecialCard::PEANUT)));
    EXPECT_EQ(false, p2.play(make_color(Color::BLUE)));

    EXPECT_EQ(p1.pos_, p2.pos_);
}

TEST(TestCandy, play_lollipop)
{
    Player p1;
    EXPECT_EQ(false, p1.play(make_color(Color::RED, true)));
    EXPECT_EQ(false, p1.play(make_color(Color::RED, true)));
    EXPECT_EQ(false, p1.play(make_color(Color::RED, true)));
    EXPECT_EQ(false, p1.play(make_color(Color::RED, true)));
    EXPECT_EQ(false, p1.play(make_color(Color::GREEN)));

    Player p2;
    EXPECT_EQ(false, p2.play(make_special(SpecialCard::LOLLIPOP)));
    EXPECT_EQ(false, p2.play(make_color(Color::GREEN)));

    EXPECT_EQ(p1.pos_, p2.pos_);
}

TEST(TestCandy, play_icecream)
{
    Player p1;
    EXPECT_EQ(false, p1.play(make_color(Color::RED, true)));
    EXPECT_EQ(false, p1.play(make_color(Color::RED, true)));
    EXPECT_EQ(false, p1.play(make_color(Color::RED, true)));
    EXPECT_EQ(false, p1.play(make_color(Color::RED, true)));
    EXPECT_EQ(false, p1.play(make_color(Color::RED, true)));
    EXPECT_EQ(false, p1.play(make_color(Color::RED)));
    EXPECT_EQ(false, p1.play(make_color(Color::BLUE)));

    Player p2;
    EXPECT_EQ(false, p2.play(make_special(SpecialCard::ICECREAM)));
    EXPECT_EQ(false, p2.play(make_color(Color::BLUE)));

    EXPECT_EQ(p1.pos_, p2.pos_);
}

TEST(TestCandy, play_licorice)
{
    Player p1;
    EXPECT_EQ(false, p1.play(make_color(Color::RED, true)));
    EXPECT_EQ(false, p1.play(make_color(Color::RED, true)));
    EXPECT_EQ(false, p1.play(make_color(Color::RED)));
    EXPECT_EQ(false, p1.skip_turn_);
    EXPECT_EQ(false, p1.play(make_color(Color::PURPLE)));
    EXPECT_EQ(true, p1.skip_turn_);
    p1.skip_turn_ = false;
    EXPECT_EQ(false, p1.play(make_color(Color::RED, true)));
    EXPECT_EQ(false, p1.play(make_color(Color::RED)));
    EXPECT_EQ(false, p1.skip_turn_);
    EXPECT_EQ(false, p1.play(make_color(Color::YELLOW, true)));
    EXPECT_EQ(true, p1.skip_turn_);
}