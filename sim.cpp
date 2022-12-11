#include <iostream>
#include <map>
#include <vector>
#include <limits>

#include "candy.h"

// Question: Can a game of Candy Land last forever?

struct PlayerStats
{
    int turns;
    int wins;
};

struct GameStats
{
    int turns;
};

struct Stats
{
    std::map<int, PlayerStats> player_stats;
    std::vector<GameStats> game_stats; 
    int games = 0; 
};

void playGame(
    std::vector<Player> &players,
    Deck &deck,
    Stats &stats,
    bool reshuffle)
{
    GameStats stats_g{};
    stats.games++;
    auto c = deck.cards.begin();
    for (;;)
    {
        for (size_t i_p = 0; i_p < players.size(); i_p++)
        {
            auto &p = players[i_p];
            auto &stats_p = stats.player_stats[i_p];
            stats_g.turns++;
            stats_p.turns++;
            if (!p.skip_turn_)
            {
                bool win = p.play(*c++);
                if (win) 
                {
                    stats_p.wins++;
                    stats.game_stats.push_back(stats_g);
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

void output_vals_stats(std::vector<GameStats> &vals)
{
    double sum = 0;
    double max_val = std::numeric_limits<double>::min();
    double min_val = std::numeric_limits<double>::max();
    for (auto val : vals)
    {
        auto x = val.turns;
        sum += x;
        if (x > max_val) max_val = x;
        if (x < min_val) min_val = x;
    }

    std::cout
        << "mean: " << std::to_string(sum/vals.size()) << " "
        << "min: " << std::to_string(min_val) << " "
        << "max: " << std::to_string(max_val) << " "
        << std::endl;
}

int main()
{
    Deck deck;
    Stats stats{};
    std::vector<Player> players(4);

    for (int i = 0; i < 1e6; i++)
    {
        deck.shuffle();
        playGame(players, deck, stats, true);
        for (auto &p : players)
        {
            p = Player();
        }
    }

    std::cout
        << "Games: "
        << std::to_string(stats.games)
        << std::endl;

    for (int i = 0; i < stats.player_stats.size(); i++)
    {
        auto& stats_p = stats.player_stats[i];
        float win_pct = float(100 * stats_p.wins) / stats.games;
        std::cout << "Player " << std::to_string(i + 1) << " win %: " 
            << std::to_string(win_pct)
            << std::endl;
    }
    output_vals_stats(stats.game_stats);
}