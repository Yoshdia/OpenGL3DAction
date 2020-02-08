#pragma once
#include "GameObject.h"

/*
@file DebugBox.h
@brief デバッグ用のオブジェクト
*/
class DebugBox :
	public GameObject
{
public:
	/*
	@param _p 座標
	@param _size サイズ
	@param _tag タグ
	*/
	DebugBox(Vector3 p,Vector3 _size=Vector3(50,50,50),Tag _tag=Tag::GroundTag);
	~DebugBox();

	void GameObjectInput(const InputState& _keyState)override;
};

