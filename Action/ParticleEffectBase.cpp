#include "ParticleEffectBase.h"
#include "Renderer.h"
#include "Texture.h"

ParticleEffectBase::ParticleEffectBase(const Vector3 & _pos, const Vector3 & _velocity,const int& _lifeCount):
	GameObject(),
	lifeCount(_lifeCount),
	velocity(_velocity)
{
	SetPosition(_pos);
	particleComponent = new ParticleComponent(this);
	particleComponent->SetTextureID(RENDERER->GetTexture("Assets/Image/16.png")->GetTextureID());
	particleComponent->SetColor(Vector3(1.0f, 1.0f, 1.0f));
	particleComponent->SetScale(10);
}

ParticleEffectBase::~ParticleEffectBase()
{
}

void ParticleEffectBase::UpdateGameObject(float _deltaTime)
{
	UpdateParticleObject(_deltaTime);
	SetPosition(position + velocity);
}

void ParticleEffectBase::UpdateParticleObject(float _deltaTime)
{
	LifeCountDown();
}

void ParticleEffectBase::LifeCountDown()
{
	if (lifeCount <= 0)
	{
		SetState(State::Dead);
	}
	else
	{
		lifeCount--;
	}
}
