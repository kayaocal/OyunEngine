#include <iostream>
#include "SimpleRenderApp.h"


int main()
{
	std::cout<<"Editor started!"<<std::endl;
	
	SimpleRenderApp simpleRender{ "Renderer", "Render Test" , 800, 600};

	while (simpleRender.Loop())
	{

	}
	
	return 0;
}