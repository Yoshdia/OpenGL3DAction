#pragma once
#include "GameObject.h"

class ForwardGroundCheck :
	public GameObject
{
public:
	ForwardGroundCheck(GameObject* _parent);
	~ForwardGroundCheck();
	
	void UpdateGameObject(float _deltaTime)override;
	bool GetGround() { return noGround; }
	void SetCheckPos(Vector3 _pos) { myPos = _pos; }
	void ResetGroundFlag(bool _flag) { noGround = _flag; }
private:
	void OnTriggerStay(ColliderComponent* colliderPair) override;
	void OnTriggerEnter(ColliderComponent* colliderPair)override;

	Vector3 myPos;
	GameObject* parent;

	bool noGround;
};

