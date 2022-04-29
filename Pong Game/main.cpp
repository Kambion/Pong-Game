#include <iostream>
#include "Game.hpp"

#ifdef __cplusplus
extern "C"
#endif
int main(int argc, char** argv) {
	Game game{};
	game.run();
	return 0;
};
