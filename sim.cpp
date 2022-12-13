#include "sim.h"

void playGame(
    std::vector<Player> &players,
    Deck &deck,
    std::map<int, PlayerStats> &stats_p,
    GameStats &stats_g,
    bool reshuffle)
{
    auto c = deck.cards.begin();
    for (;;)
    {
        for (size_t i_p = 0; i_p < players.size(); i_p++)
        {
            auto &p = players[i_p];
            auto &stats_i_p = stats_p[i_p];
            stats_g.turns++;
            stats_i_p.turns++;
            if (!p.skip_turn_)
            {
                bool win = p.play(*c++);
                if (win) 
                {
                    stats_i_p.wins++;
                    return;
                }

                if (deck.cards.end() == c)
                {
                    if (reshuffle) deck.shuffle();
                    c = deck.cards.begin();
                }
            }
            else
            {
                p.skip_turn_ = false;
            }
        }
    }
}
