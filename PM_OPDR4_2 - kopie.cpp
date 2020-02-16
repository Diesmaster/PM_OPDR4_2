#include <iostream>
#include  "C:\Users\chris\source\repos\PM_OPDR4_2\PM_OPDR4_2\Header.h"
using namespace std;

int main()
{
	game mother;
	for (int x = 0; x < mother.gethoeveel(); x++) {
		mother.makegobordpub();
		mother.denkbordsetup();
		while (mother.getboolwinnen() == false) {
			mother.menu();
			mother.endgame();
		}
		//mother.Thanos();
	}
	cout << "its over and done" << endl;
}