#pragma once
#include "GameObject.h"

class ForwardGroundCheck :
	public GameObject
{
public:
	ForwardGroundCheck(GameObject* _parent,Vector3 _pos,Vector3 _colliderSize,Tag _pairTag);
	~ForwardGroundCheck();
	
	void UpdateGameObject(float _deltaTime)override;
	bool GetGround() { return noGround; }
	bool GetGroundEnter() {return noGroundEnter;}
	void ResetGroundFlag(bool _flag) { noGround = _flag; }
	void SetCheckPos(Vector3 _pos) { myPos = _pos; }
	Vector3 GetColliderPairPosition() { return colliderPairPos; }
private:
	void OnTriggerStay(ColliderComponent* colliderPair) override;
	void OnTriggerEnter(ColliderComponent* colliderPair)override;

	Tag pairTag;
	Vector3 myPos;
	GameObject* parent;

	Vector3 colliderPairPos;

	bool noGround;
	bool noGroundEnter;
};

