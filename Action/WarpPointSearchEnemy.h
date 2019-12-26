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
	//足元に地面があるか。接地状態を維持する
	SkeltonObjectChecker* footGroundChecker;
	//進行方向に地面があるか。なかった場合そこに停止する
	SkeltonObjectChecker* forwardGroundChecker;
	//進行方向に壁があるか。あった場合そこに停止する
	SkeltonObjectChecker* forwardWallChecker;
};

