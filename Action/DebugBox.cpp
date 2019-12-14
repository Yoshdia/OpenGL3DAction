#include "DebugBox.h"
#include "MeshComponent.h"
#include "Renderer.h"
#include "InputSystem.h"
#include "ColliderComponent.h"

DebugBox::DebugBox(Vector3 p, Vector3 _size, Tag _tag)
{
	MeshComponent* meshComponent = new MeshComponent(this);
	meshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/Stage/untitled.gpmesh"));
	SetPosition(p);
	SetScale(_size);
	tag = _tag;
	ColliderComponent* collider = new ColliderComponent(this, 100, _size*2, myObjectId, GetTriggerEnterFunc(), GetTriggerStayFunc(), tag);

}


DebugBox::~DebugBox()
{
}

void DebugBox::GameObjectInput(const InputState & _keyState)
{
	if (_keyState.Keyboard.GetKeyValue(SDL_SCANCODE_0)==1)
		printf("\ndebugBoxPosition = {%f,%f,%f}", position.x, position.y, position.z);
}
