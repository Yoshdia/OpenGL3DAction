#pragma once
#include "GameObject.h"
#include "ParticleComponent.h"

class ParticleEffectBase :
	public GameObject
{
public:
	ParticleEffectBase(const Vector3& _pos,const Vector3& _velocity,const int& _lifeCount);
	~ParticleEffectBase();

	void UpdateGameObject(float _deltaTime)override;
private:
	virtual void UpdateParticleObject(float _deltaTime);

protected:
	ParticleComponent* particleComponent;
	Vector3 velocity;
	void LifeCountDown();
	int lifeCount;
};

