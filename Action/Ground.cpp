#include "Ground.h"
#include "ColliderComponent.h"
#include "MeshComponent.h"
#include "Renderer.h"

Ground::Ground(const Vector3 & _p, const Vector3 & _size, const Tag& _objectTag)
{
	MeshComponent* meshComponent = new MeshComponent(this);
	std::string firstName = "Assets/Model/Stage/";
	std::string lastName = ".gpmesh";
	std::string fileName = "blueFloor1";

	int random = rand() % 100;
	if (random <= 30)
	{
		fileName = "blueFloor1";
	}
	else if(random<=60)
	{
		fileName = "blueFloor2";
	}
	else if (random <= 95)
	{
		fileName = "blueFloor3";
	}
	else if (random <= 100)
	{
		fileName = "blueFloor4";
	}

	meshComponent->SetMesh(RENDERER->GetMesh(firstName+fileName+lastName));
	SetPosition(_p);
	SetScale(_size);
	tag = _objectTag;
	ColliderComponent* collider = new ColliderComponent(this, 100, _size * 2, myObjectId, GetTriggerEnterFunc(), GetTriggerStayFunc(), tag);
}

Ground::~Ground()
{
}
