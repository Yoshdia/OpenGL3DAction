#pragma once
#include "GameObject.h"

class SkeltonObjectChecker;

class WarpPointSearchEnemy :
	public GameObject
{
public:
	WarpPointSearchEnemy(Vector3 _pos=Vector3(0,0,0));
	~WarpPointSearchEnemy();

	bool GetEndSearch() { return searchedPoint; };
	void UpdateGameObject(float _deltaTime)override;
	void SetFirstPosition(Vector3 _position, Vector3 _enemyPosition);
private:
	enum MoveDirection
	{
		right = 1,
		left = -1
	};
	MoveDirection moveDirection;
	bool searchedPoint;
	bool isGround;
	//�����ɒn�ʂ����邩�B�ڒn��Ԃ��ێ�����
	SkeltonObjectChecker* footGroundChecker;
	//�i�s�����ɒn�ʂ����邩�B�Ȃ������ꍇ�����ɒ�~����
	SkeltonObjectChecker* forwardGroundChecker;
	//�i�s�����ɕǂ����邩�B�������ꍇ�����ɒ�~����
	SkeltonObjectChecker* forwardWallChecker;
};

