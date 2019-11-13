#pragma once
#include "GameObject.h"
#include <string>

enum EnemyMoveDirection
{
	right = 1,
	left = -1,
};

enum EnemyActions
{
	walk,
	noActive,
	foundMove,
	attack,
};

class EnemyBase abstract:
	public GameObject
{
public:
	EnemyBase(const std::string& meshName);
	~EnemyBase();
	void UpdateGameObject(float _deltaTime)override;

protected:
	void OnTriggerStay(ColliderComponent* colliderPair) override;
	void OnTriggerEnter(ColliderComponent* colliderPair)override;
	virtual void UpdateEnemyObject(float _deltaTime) {};
	class FootSole* footSole;
	class ForwardGroundCheck* forwardDownGroundCheck;
	class ForwardGroundCheck* forwardGroundCheck;
	class ForwardGroundCheck* findingPlayerCheck;

	static const float GroundCheckPos;
	static const float NockBackPower;
	Vector3 forceVector;
	void NockBack();
	EnemyMoveDirection moveDirection;
	//一定数まで行くとアクションが変更されるカウントとその最大数
	int actionChangeCount;
	int actionChangeCountMax;
	int defaultCountMax;


	EnemyActions actionName;
	void ActionChange() ;
	virtual void BranchActionChange() { };
	virtual void ShuffleCountMax() {};
};



