#include "DebugBox.h"
#include "MeshComponent.h"
#include "Renderer.h"
#include "InputSystem.h"
#include "ColliderComponent.h"

/*
@param _p 座標
@param _size サイズ
@param _tag タグ
*/
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
}
