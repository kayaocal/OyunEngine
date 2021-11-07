#include <iostream>
#include "EditorApp.h"

int main()
{
	std::cout<<"Editor started!"<<std::endl;
	
	EditorApp editor{ "My Editor", "Editor Test" };

	while (editor.Loop())
	{

	}
	
	return 0;
}