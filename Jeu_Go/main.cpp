#include"Goban.h"
#include<iostream>
using namespace std;
int main(int argc , char** argv)
{	
	system("clear");
	int n=9;
	if (argc == 2){
		int m=atoi(argv[1]);
		if(m>0 || m<=19)
			n=m;
	}
	Goban g(n);
	g.gestionPartie();

	return 0;
}
