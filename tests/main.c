#include <minunit.h>
#include <malloc.h>
#include <stdio.h>
#include "../src/game.h"


static Game *game;


void setup(void) {
	game = create_game();
}

static void roll_multiple(int count, int pins) {
	for (int i = 1; i <= count; i++) {
		roll(game, pins);
	}
}

static void roll_spare() {
	roll_multiple(2, 5);
}

static void roll_strike() {
	roll(game, 10);
}

void test_default(void) {
	game->current = 0;

	mu_assert_int_eq(0, game->current);
}

void test_roll(void) {
	roll(game, 2);
	roll(game, 4);

	mu_assert_int_eq(6, get_score(game));
}

void test_failed_game(void) {
	roll_multiple(20, 0);

	mu_assert_int_eq(0, get_score(game));
}

void test_spare(void) {
	roll_spare();
	roll(game, 4);
	roll_multiple(15, 1);

	mu_assert_int_eq(33, get_score(game));
}

void test_strike(void) {
	roll_strike();
	roll_multiple(2, 3);
	roll_strike();

	mu_assert_int_eq(32, get_score(game));
}

int main(void) {
	MU_SUITE_CONFIGURE(setup, NULL);
	MU_RUN_TEST(test_default);
	MU_RUN_TEST(test_roll);
	MU_RUN_TEST(test_failed_game);
	MU_RUN_TEST(test_spare);
	MU_RUN_TEST(test_strike);
	MU_REPORT();

	return 0;
}