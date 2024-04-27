#include <iostream>
#include <limits>

#include "sim.h"

// Question: Can a game of Candy Land last forever?

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
        << "-- Number of turns per game -- " << std::endl
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

    constexpr size_t N = 1e6;
    stats.game_stats.reserve(N);

    for (int i = 0; i < N; i++)
    {
        GameStats stats_g{};
        deck.shuffle();
        playGame(players, deck, stats.player_stats, stats_g, true);
        stats.games++;
        stats.game_stats.push_back(stats_g);
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