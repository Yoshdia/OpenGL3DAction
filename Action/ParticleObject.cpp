#include "ParticleObject.h"
#include "ParticleComponent.h"
#include "Texture.h"
#include "Renderer.h"

ParticleObject::ParticleObject(const Vector3& _pos, const std::string& _fileName):
	GameObject()
{
	SetPosition(_pos);
	ParticleComponent* particle = new ParticleComponent(this);
	particle->SetTextureID(RENDERER->GetTexture(_fileName)->GetTextureID());
	particle->SetScale(160);
}

ParticleObject::~ParticleObject()
{
}

