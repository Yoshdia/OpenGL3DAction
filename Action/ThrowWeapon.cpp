#include "ThrowWeapon.h"
#include "MeshComponent.h"
#include "Renderer.h"


ThrowWeapon::ThrowWeapon(const Vector3& _pos)
{
	SetPosition(_pos);
	meshComponent = new MeshComponent(this);
	meshComponent->SetMesh(RENDERER->GetMesh("Assets/Bike.gpmesh"));
}


ThrowWeapon::~ThrowWeapon()
{
}

void ThrowWeapon::UpdateGameObject(float _deltaTime)
{
	SetPosition(Vector3(position.x+=10, position.y, position.z));
}
