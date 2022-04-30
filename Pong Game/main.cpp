#include <iostream>
#include "Game.hpp"

#ifdef __cplusplus
extern "C"
#endif
int main(int argc, char** argv) {
	srand(time(NULL));
	Game game{};
	game.run();
	return 0;
};
