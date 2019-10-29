#include "DebugBox.h"
#include "MeshComponent.h"
#include "Renderer.h"
#include "InputSystem.h"
#include "ColliderComponent.h"

DebugBox::DebugBox()
{
	MeshComponent* meshComponent = new MeshComponent(this);
	meshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/untitled.gpmesh"));
	SetPosition(Vector3(100, 0, 0));
	SetScale(50);
	std::function<void(const ColliderComponent*)>  Enter = std::bind(&DebugBox::OnTriggerEnter, this, std::placeholders::_1);
	std::function<void(const ColliderComponent*)>  Stay = std::bind(&DebugBox::OnTriggerStay, this, std::placeholders::_1);
	tag = Tag::GroundTag;
	ColliderComponent* collider = new ColliderComponent(this, 100, Vector3(10, 10, 10), myObjectId,Enter,Stay,tag);
}


DebugBox::~DebugBox()
{
}

void DebugBox::GameObjectInput(const InputState & _keyState)
{
	if (_keyState.Keyboard.GetKeyValue(SDL_SCANCODE_0)==1)
		printf("\ndebugBoxPosition = {%f,%f,%f}", position.x, position.y, position.z);
}
