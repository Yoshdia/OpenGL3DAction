#pragma once
#include "GameObject.h"
#include <string>

/*
@file BackGroundObject.h
@brief 主に背景となるオブジェクトを表示する
*/
class BackGroundObject :
	public GameObject
{
public:
	/*
	@param _pos 座標
	@param _size サイズ
	@param _fileName メッシュデータのアドレス
	*/
	BackGroundObject(const Vector3& _pos, const Vector3& _size, const std::string& _fileName);
	~BackGroundObject();

	void UpdateGameObject(float deltaTime)override;
private:
};

