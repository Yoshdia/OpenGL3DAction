#pragma once
#include "GameObject.h"
#include <string>

/*
@file ParticleObject.h
@brief パーティクルオブジェクト。固定オブジェクトなどに使用
*/
class ParticleObject :
	public GameObject
{
public:
	/*
	@param _pos 座標
	@param _fileName 画像アドレス
	@param _scale サイズ
	@param drawOrder 描画順
	*/
	ParticleObject(const Vector3& _pos, const std::string& _fileName,const float& _scale,const int& drawOrder=100);
	~ParticleObject();
protected:
	//パーティクルの管理と描画を行うクラス
	class ParticleComponent* particle;
};

