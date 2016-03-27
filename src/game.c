#include <malloc.h>
#include <stdbool.h>
#include <string.h>
#include "game.h"


typedef struct {
    int current;
    int rolls[20];
} Game;

static Game game;


void new_game(void) {
    game.current = 0;
    memset(game.rolls, 0, sizeof(game.rolls));
}

void roll(int pins) {
	game.rolls[game.current++] = pins;
}

static bool is_strike(int frame_index) {
	return game.rolls[frame_index] == 10;
}

static bool is_spare(int frame_index) {
	return game.rolls[frame_index] + game.rolls[frame_index + 1] == 10;
}

static int get_strike_score(int frame_index) {
    return 10 + game.rolls[frame_index + 1] + game.rolls[frame_index + 2];
}

static int get_spare_score(int frame_index) {
	return 10 + game.rolls[frame_index + 2];
}

static int get_default_score(int frame_index) {
	return game.rolls[frame_index] + game.rolls[frame_index + 1];
}

int get_score(void) {
    int score = 0;
    int frame_index = 0;

    for (int frame = 0; frame < 10; frame++) {
        if (is_strike(frame_index)) {
            score += get_strike_score(frame_index);
			frame_index++;
        } else if (is_spare(frame_index)) {
            score += get_spare_score(frame_index);
            frame_index += 2;
        } else {
            score += get_default_score(frame_index);
            frame_index += 2;
        }
    }
    return score;
}