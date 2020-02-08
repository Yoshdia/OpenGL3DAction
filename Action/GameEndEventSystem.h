#pragma once
#include "EventSystem.h"
/*
@file GameEndEventSystem.h
@brief プレイヤーと衝突したときにフラグを建てるクラス
*/
class GameEndEventSystem :
	public EventSystem
{
public:
	/*
	@param _pos 座標
	*/
	GameEndEventSystem(const Vector3& _pos);
	~GameEndEventSystem();
private:
	/*
	@fn プレイヤーと衝突したときにフラグを建てるクラス
	*/
	void OnTriggerEnter(ColliderComponent* _pair)override;
	bool end;
public://ゲッターセッター
	/*
	@return プレイヤーと接触したか
	*/
	bool GetEndFlag() { return end; }
};

