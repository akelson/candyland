#include <map>
#include <vector>

#include "candy.h"

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
    std::map<int, PlayerStats> &stats_p,
    GameStats &stats_g,
    bool reshuffle);