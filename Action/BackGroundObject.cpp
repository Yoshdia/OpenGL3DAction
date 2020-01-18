#include "BackGroundObject.h"
#include "Renderer.h"
#include "MeshComponent.h"
#include "RotateComponent.h"

#include "ParticleComponent.h"
#include "Texture.h"

BackGroundObject::BackGroundObject():
	GameObject(true)
{
	//ParticleComponent* particle = new ParticleComponent(this,50);
	//particle->SetColor(Vector3(1, 1, 1));
	//particle->SetScale(3000);
	//particle->SetTextureID(RENDERER->GetTexture("Assets/Image/back.png")->GetTextureID());
	//SetPosition(Vector3(0,0,200));
	SetPosition(Vector3(-500, -9000, 100));
	MeshComponent* meshComponent = new MeshComponent(this);
	meshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/Stage/SM_Env_Ice_Cliffs_CliffWall_01b.gpmesh"));
	RotateComponent* ro = new RotateComponent(this);
	ro->SetRotation(90, Vector3::UnitY);
	SetScale(Vector3(0.1f, 5, 5));
}


BackGroundObject::~BackGroundObject()
{
}
