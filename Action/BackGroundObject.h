#pragma once
#include "GameObject.h"
#include <string>

class BackGroundObject :
	public GameObject
{
public:
	BackGroundObject(const Vector3& _pos, const Vector3& _size, const std::string& _fileName);
	~BackGroundObject();

	void UpdateGameObject(float deltaTime)override;
private:
};

