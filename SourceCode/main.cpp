#include "Game.h"
#include <ctime>

int main(int argc, char *argv[]){
	srand(time(nullptr));
	Game g;
	g.Run();


	return 0;
}

