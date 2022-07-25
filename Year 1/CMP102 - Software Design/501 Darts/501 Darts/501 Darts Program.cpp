#include <iostream>
#include <process.h>
using namespace std;
#include "Gameplay.h"

int main()
{
	Gameplay object;
	object.startup();
	object.final();
	system("pause");
}
