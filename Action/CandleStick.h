#pragma once
#include "GameObject.h"
class CandleStick :
	public GameObject
{
public:
	CandleStick(Vector3 _pos=Vector3(0,0,0));
	~CandleStick();

	void UpdateGameObject(float _deltaTime)override;
private:
	//void OnTriggerStay(ColliderComponent* colliderPair) override;
	void OnTriggerEnter(ColliderComponent* colliderPair) override;
	class ColliderComponent* collider;
	class ParticleComponent* stickParticle;
	class Texture* fire;
	class ParticleComponent* lightParticle;
	bool ignition;
};

