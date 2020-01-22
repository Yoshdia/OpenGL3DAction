#include "ParticleObject.h"
#include "ParticleComponent.h"
#include "Texture.h"
#include "Renderer.h"

ParticleObject::ParticleObject(const std::string& _fileName):
	GameObject()
{
	ParticleComponent* particle = new ParticleComponent(this);
	particle->SetTextureID(RENDERER->GetTexture(_fileName)->GetTextureID());
}

ParticleObject::~ParticleObject()
{
}
