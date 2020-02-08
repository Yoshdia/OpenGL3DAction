#pragma once
#include "GameObject.h"

/*
@file EventSystem.h
@brief イベントシステムクラス着て暮らす 条件を満たすと更新を終了する
*/
class EventSystem :
	public GameObject
{
public:
	/*
	@param _pos 座標
	*/
	EventSystem(const Vector3& _pos);
	~EventSystem();

	void UpdateGameObject(float _deltaTime)override;
protected:
	//条件を満たしたか
	bool trigger;
private:
	/*
	@fn 派生クラスの更新関数
	*/
	virtual void UpdateEventObject() {};
};

