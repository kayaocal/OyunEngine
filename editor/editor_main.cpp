#include <iostream>
#include "App.h"

int main()
{
	std::cout<<"Editor started!"<<std::endl;
	
	App editor{ "My Editor", "Editor Test" };

	while (editor.Loop())
	{

	}
	
	return 0;
}