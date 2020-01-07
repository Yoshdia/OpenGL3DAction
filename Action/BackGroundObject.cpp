#include "BackGroundObject.h"
#include "ParticleComponent.h"
#include "Renderer.h"
#include "Texture.h"

BackGroundObject::BackGroundObject():
	GameObject(true)
{
	ParticleComponent* particle = new ParticleComponent(this);
	particle->SetColor(Vector3(1, 1, 1));
	particle->SetScale(3000);
	particle->SetTextureID(RENDERER->GetTexture("Assets/Image/back.png")->GetTextureID());
	SetPosition(Vector3(0,0,200));
}


BackGroundObject::~BackGroundObject()
{
}
