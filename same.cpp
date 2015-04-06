#include <iostream>
#include "SameGame.h"

using namespace std;

int main(int argc, char const *argv[])
{
	SameGame sg("matrix.txt");

    sg.show();
    sg.lets_play();
    
	return 0;
}