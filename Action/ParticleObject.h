#pragma once
#include "GameObject.h"
#include <string>

class ParticleObject :
	public GameObject
{
public:
	ParticleObject(const Vector3& _pos, const std::string& _fileName,const float& _scale,const int& drawOrder=100);
	~ParticleObject();
protected:
	class ParticleComponent* particle;
};

