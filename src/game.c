#include <malloc.h>
#include <stdbool.h>
#include "game.h"


Game *create_game(void) {
	Game *game = malloc(sizeof(Game));
	game->rolls = malloc(20 * sizeof(int));
	game->current = 0;

	return game;
}

void roll(Game *game, int pins) {
	game->rolls[game->current++] = pins;
}

static bool is_strike(Game *game, int frame_index) {
	return game->rolls[frame_index] == 10;
}

static bool is_spare(Game *game, int frame_index) {
	return game->rolls[frame_index] + game->rolls[frame_index + 1] == 10;
}

static int get_strike_score(Game *game, int frame_index) {
    return 10 + game->rolls[frame_index + 1] + game->rolls[frame_index + 2];
}

static int get_spare_score(Game *game, int frame_index) {
	return 10 + game->rolls[frame_index + 2];
}

static int get_default_score(Game *game, int frame_index) {
	return game->rolls[frame_index] + game->rolls[frame_index + 1];
}

int get_score(Game *game) {
	int score = 0;
    int frame_index = 0;

    for (int frame = 0; frame < 10; frame++) {
        if (is_strike(game, frame_index)) {
            score += get_strike_score(game, frame_index);
			frame_index++;
        } else if (is_spare(game, frame_index)) {
            score += get_spare_score(game, frame_index);
            frame_index += 2;
        } else {
            score += get_default_score(game, frame_index);
            frame_index += 2;
        }
    }
    return score;
}