#include <benchmark/benchmark.h>

#include <iostream>

#include "candy.h"
#include "sim.h"

static void BM_play(benchmark::State& state)
{
    Player p;
    for (auto _ : state)
    {
        p.play(Card(state.range(0)));
    }
}

BENCHMARK(BM_play)->Arg(0)->Arg(40);

static void BM_shuffle(benchmark::State& state)
{
    Deck deck;
    for (auto _ : state)
    {
        deck.shuffle();
    }
}

BENCHMARK(BM_shuffle);

static void BM_playGame(benchmark::State& state)
{
    Deck deck;
    Stats stats;
    std::vector<Player> players(4);
    deck.g.seed();
    deck.shuffle();
    GameStats stats_g{};

    for (auto _ : state)
    {
        stats_g = GameStats{};
        playGame(players, deck, stats.player_stats, stats_g, true);
        for (auto &p : players) p.reset();
    }
}

BENCHMARK(BM_playGame);