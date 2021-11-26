#include <iostream>
#include <Engine.h>

#include "EditorGameSubsystem.h"

class EditorSubsystem :public Oyun::GameSubsystem
{
	EditorSubsystem()
		:Oyun::GameSubsystem()
	{

	}
	~EditorSubsystem() {};
};


int main()
{
	using namespace Oyun;
	Oyun::StartEngine(dynamic_cast<Oyun::GameSubsystem*>(Editor::EditorGameSubsystem::Instantiate().GetPtr()));
	Oyun::RunGame();
	return 0;
}