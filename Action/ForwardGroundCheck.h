#pragma once
#include "GameObject.h"

class ForwardGroundCheck :
	public GameObject
{
public:
	ForwardGroundCheck(GameObject* _parent,Vector3 _pos);
	~ForwardGroundCheck();
	
	void UpdateGameObject(float _deltaTime)override;
	bool GetGround() { return noGround; }
	bool GetGroundEnter() {return noGroundEnter;}
	void ResetGroundFlag(bool _flag) { noGround = _flag; }
	void SetCheckPos(Vector3 _pos) { myPos = _pos; }
private:
	void OnTriggerStay(ColliderComponent* colliderPair) override;
	void OnTriggerEnter(ColliderComponent* colliderPair)override;

	Vector3 myPos;
	GameObject* parent;

	bool noGround;
	bool noGroundEnter;
};

