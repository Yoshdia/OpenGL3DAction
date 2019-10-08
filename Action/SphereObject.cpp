#include "SphereObject.h"
#include "Game.h"
#include "MeshComponent.h"
#include "SphereCollider.h"
#include "Renderer.h"
#include "Collision.h"

SphereObject::SphereObject()
	:GameObject()
{
	meshComp = new MeshComponent(this);
	meshComp->SetMesh(RENDERER->GetMesh("Assets/Sphere.gpmesh"));
	sphereCollider = new SphereCollider(this, GetOnCollisionFunc());
	sphereCollider->SetObjectSphere(Sphere(Vector3(0.0f,0.0f,0.0f),1.0f));
	SetPosition(Vector3(200.0f,-75.0f,0.0f));
	SetScale(10.0f);
}


SphereObject::~SphereObject()
{
}
