
typedef struct {
	int current;
	int *rolls;
} Game;


Game *create_game(void);

void roll(Game *game, int pins);

int get_score(Game *game);