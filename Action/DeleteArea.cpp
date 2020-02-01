#include "DeleteArea.h"
#include "ColliderComponent.h"

DeleteArea::DeleteArea(GameObject* _parent) :
	GameObject(true)
{
	tag = Tag::DeleteZone;
	ColliderComponent* collider = new ColliderComponent(this, 100, Vector3(1000, 1, 400), myObjectId, GetTriggerEnterFunc(), GetTriggerStayFunc(), tag);
	owner = _parent;
	SetPosition(owner->GetPosition() + Vector3(0, 200, 500));
}

DeleteArea::~DeleteArea()
{
}

void DeleteArea::UpdateGameObject(float _deltaTime)
{
	SetPosition(owner->GetPosition()+Vector3(0,400, 500));
}
