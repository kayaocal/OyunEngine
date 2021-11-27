#include <Engine.h>
#include "EditorGameSubsystem.h"


int main()
{
	using namespace Oyun;
	Oyun::StartEngine(dynamic_cast<Oyun::GameSubsystem*>(Editor::EditorGameSubsystem::Instantiate().GetPtr()));
	return 0;
}