#include <iostream>
#include "EditorApp.h"


int main()
{
	std::cout<<"Editor started!"<<std::endl;
	
	EditorApp simpleRender{ "OyunEngine", "Oyun Engine" , 800, 600};

	while (simpleRender.Loop())
	{

	}
	
	return 0;
}