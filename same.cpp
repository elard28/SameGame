#include <iostream>
#include "SameGame.h"

using namespace std;

int main(int argc, char const *argv[])
{
	if(argc<2)
    {
        cout<<"sin archivo que tomar"<<endl;
        return 0;
    }

    string ar=argv[1];

    char *tex=new char[ar.length()+1];
    strcpy(tex,ar.c_str());

	SameGame sg(tex);

    sg.show();
    sg.lets_play();
    
	return 0;
}