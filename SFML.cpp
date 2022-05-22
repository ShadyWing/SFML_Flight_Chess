
#include <iostream>
#include "Game.h"
using namespace std;


int main(int argc, int* argv[])
{
	Game FlyingChess;

	while (FlyingChess.window.isOpen())
	{
		FlyingChess.Run();
	}

	return 0; 
}