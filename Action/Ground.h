#pragma once
#include "GameObject.h"

/*
@file Ground.h
@brief プレイヤーと判定のある地面クラス
*/
class Ground :
	public GameObject
{
public:
	/*
	@param _p 座標
	@param _size サイズ
	@param _objectTag タグ
	*/
	Ground(const Vector3& _p,const Vector3& _size,const Tag& _objectTag=Tag::GroundTag);
	~Ground();
};

