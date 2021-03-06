#include <minunit.h>
#include "../src/game.h"


void setup(void) {
	new_game();
}

static void roll_multiple(int count, int pins) {
	for (int i = 1; i <= count; i++) {
		roll(pins);
	}
}

static void roll_spare() {
	roll_multiple(2, 5);
}

static void roll_strike() {
	roll(10);
}

void test_roll(void) {
	roll(2);
	roll(4);

	mu_assert_int_eq(6, get_score());
}

void test_failed_game(void) {
	roll_multiple(20, 0);

	mu_assert_int_eq(0, get_score());
}

void test_spare(void) {
	roll_spare();
	roll(4);
	roll_multiple(15, 1);

	mu_assert_int_eq(33, get_score());
}

void test_strike(void) {
	roll_strike();
	roll_multiple(2, 3);
	roll_strike();

	mu_assert_int_eq(32, get_score());
}

int main(void) {
	MU_SUITE_CONFIGURE(setup, NULL);
	MU_RUN_TEST(test_roll);
	MU_RUN_TEST(test_failed_game);
	MU_RUN_TEST(test_spare);
	MU_RUN_TEST(test_strike);
	MU_REPORT();

	return 0;
}