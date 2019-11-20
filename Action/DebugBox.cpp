#include "DebugBox.h"
#include "MeshComponent.h"
#include "Renderer.h"
#include "InputSystem.h"
#include "ColliderComponent.h"

DebugBox::DebugBox(Vector3 p)
{
	MeshComponent* meshComponent = new MeshComponent(this);
	meshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/untitled.gpmesh"));
	SetPosition(p);
	SetScale(50);
	tag = Tag::GroundTag;
	ColliderComponent* collider = new ColliderComponent(this, 100, Vector3(100, 100, 100), myObjectId,GetTriggerEnterFunc(),GetTriggerStayFunc(),tag);
}

DebugBox::DebugBox(Vector3 p, Tag _tag)
{
	MeshComponent* meshComponent = new MeshComponent(this);
	meshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/untitled.gpmesh"));
	SetPosition(p);
	SetScale(50);
	tag = _tag;
	ColliderComponent* collider = new ColliderComponent(this, 100, Vector3(100, 100, 100), myObjectId, GetTriggerEnterFunc(), GetTriggerStayFunc(), tag);

}


DebugBox::~DebugBox()
{
}

void DebugBox::GameObjectInput(const InputState & _keyState)
{
	if (_keyState.Keyboard.GetKeyValue(SDL_SCANCODE_0)==1)
		printf("\ndebugBoxPosition = {%f,%f,%f}", position.x, position.y, position.z);
}
