#include "ParticleObject.h"
#include "ParticleComponent.h"
#include "Texture.h"
#include "Renderer.h"

ParticleObject::ParticleObject(const Vector3& _pos, const std::string& _fileName, const float& _scale, const int& drawOrder):
	GameObject()
{
	SetPosition(_pos);
	particle = new ParticleComponent(this, drawOrder);
	particle->SetTextureID(RENDERER->GetTexture(_fileName)->GetTextureID());
	particle->SetScale(_scale);
}

ParticleObject::~ParticleObject()
{
}

