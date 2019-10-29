#include "DebugBox.h"
#include "MeshComponent.h"
#include "Renderer.h"
#include "InputSystem.h"

DebugBox::DebugBox()
{
	MeshComponent* meshComponent = new MeshComponent(this);
	meshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/untitled.gpmesh"));
	SetPosition(Vector3(100, 0, 0));
	SetScale(50);
}


DebugBox::~DebugBox()
{
}

void DebugBox::GameObjectInput(const InputState & _keyState)
{
	if (_keyState.Keyboard.GetKeyValue(SDL_SCANCODE_0)==1)
		printf("\ndebugBoxPosition = {%f,%f,%f}", position.x, position.y, position.z);
}
