#include <iostream>

using namespace std;

#include "BigWorldGame.h"

int main(int argc, char **argv)
{
	cout << "BigWorld\n";

	BigWorldGame game;

	game.Run();

#if FALSE
	cout << "\nPress enter to continue.\n";

	getchar();
#endif

	return 0;
}