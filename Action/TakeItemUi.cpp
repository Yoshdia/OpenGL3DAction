#include "TakeItemUi.h"

/*
@param _pos 開始座標
@param _targetSlot 目的地
@param _spriteName 画像アドレス
@param _size 画像サイズ
*/
TakeItemUi::TakeItemUi(const Vector3& _pos, const Vector3& targetSlot, const std::string& _spriteName, const Vector3& _size) :
	UserInterfaceBase(_pos, _spriteName, _size, 100),
	life(240)
{
	target = targetSlot;
}

TakeItemUi::~TakeItemUi()
{
}

/*
@fn 座標から目標まで移動し、生存時間をカウントダウンする
*/
void TakeItemUi::UpdateGameObject(float _deltaTime)
{
	SetPosition(Vector3::Lerp(position, target, 0.05f));
	if (life < 0)
	{
		SetState(State::Dead);
	}
	else
	{
		life--;
	}
}
