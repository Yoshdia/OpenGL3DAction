#pragma once
#include "GameObject.h"

class EventSystem :
	public GameObject
{
public:
	EventSystem(const Vector3& _pos);
	~EventSystem();

	void UpdateGameObject(float _deltaTime)override;
private:
	virtual void UpdateEventObject() {};
	protected:
	bool trigger;
};

