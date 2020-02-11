#pragma once
#include "UserInterfaceBase.h"
/*
@file TakeItemUi.h
@brief アイテム取得した際に、画面中央にアイコンが出現しアイテムの位置へ飛んでいく演出
*/
class TakeItemUi :
	public UserInterfaceBase
{
public:
	/*
	@param _pos 開始座標
	@param _targetSlot 目的地
	@param _spriteName 画像アドレス
	@param _size 画像サイズ
	*/
	TakeItemUi(const Vector3& _pos, const Vector3& targetSlot, const std::string& _spriteName, const Vector3& _size);
	~TakeItemUi();

	/*
	@fn 座標から目標まで移動し、生存時間をカウントダウンする
	*/
	void UpdateGameObject(float _deltaTime)override;
private:
	//目的地
	Vector3 target;
	//生存時間
	int life;
};

