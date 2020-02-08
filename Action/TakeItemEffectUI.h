#pragma once
#include "UserInterfaceBase.h"

/*
@file TakeItemEffectUI.h
@brief アイテムを取得したときに使用される、サイズを拡大しながら一定サイズまでいくと更新を止める
*/
class TakeItemEffectUI :
	public UserInterfaceBase
{
public:
	/*
	@param _pos スクリーン座標
	*/
	TakeItemEffectUI(const Vector3& _pos);
	~TakeItemEffectUI();
	/*
	@fn サイズを拡大しながら一定サイズまでいくと更新を止める
	*/
	void UpdateGameObject(float _deltaTime)override;
private:
	float spriteScale;
};

