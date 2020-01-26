#pragma once
#include "GameObject.h"
#include <string>

class ParticleObject :
	public GameObject
{
public:
	ParticleObject(const Vector3& _pos, const std::string& _fileName);
	~ParticleObject();
};

