#pragma once
#include "UserInterfaceBase.h"
class HaveLifeCountUI :
	public UserInterfaceBase
{
public:
	HaveLifeCountUI(const Vector3& _pos, const std::string& spriteName, int _lifeCount, const Vector3& _size = Vector3(1, 1, 1), const int& _drawOrder = 100);
	~HaveLifeCountUI();
	void UpdateGameObject(float _deltaTime)override;
private:
	int lifeCount;
};


