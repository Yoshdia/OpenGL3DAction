#pragma once
#include "ParticleObject.h"
class CandleFireObject :
	public ParticleObject
{
public:
	CandleFireObject(const Vector3& _pos);
	~CandleFireObject();

	void UpdateGameObject(float _deltaTime)override;
private:
	float alfa;
};

