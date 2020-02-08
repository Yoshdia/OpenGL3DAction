#pragma once
#include "UserInterfaceBase.h"

/*
@file HaveLifeCountUI.h
@fn 主にプレイヤーの体力が減少したときの演出で用いられる、生存時間を持ったUI
*/
class HaveLifeCountUI :
	public UserInterfaceBase
{
public:
	/*
	@param _pos スクリーン座標
	@param _spriteName 画像へのアドレス
	@param _lifeCount 生存時間
	@param _size サイズ
	@param _drawOrder 描画順
	*/
	HaveLifeCountUI(const Vector3& _pos, const std::string& _spriteName, int _lifeCount, const Vector3& _size = Vector3(1, 1, 1), const int& _drawOrder = 100);
	~HaveLifeCountUI();

	/*
	@fn 生存時間をカウントする
	*/
	void UpdateGameObject(float _deltaTime)override;
private:
	int lifeCount;
};


