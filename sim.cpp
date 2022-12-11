#include <iostream>
#include <map>
#include <vector>

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
    GameStats stats_g;;
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

int main()
{
    Deck deck;
    Stats stats{};
    std::vector<Player> players(4);

    for (int i = 0; i < 100000; i++)
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
}