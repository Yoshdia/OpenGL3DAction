#pragma once
#include "GameObject.h"
#include <string>

/*
@file UserInterfaceBase.h
@brief UIの基底クラス
*/
class UserInterfaceBase :
	public GameObject
{
public:
	/*
	@param _pos スクリーン座標
	@param _spriteName 画像へのアドレス
	@param _size サイズ
	@param _drawOrder 描画順
	*/
	UserInterfaceBase(const Vector3& _pos,const std::string& _spriteName, const Vector3& _size=Vector3(1,1,1), const int& _drawOrder=100);
	~UserInterfaceBase();
	protected:
	class SpriteComponent* spriteComponent;
};

