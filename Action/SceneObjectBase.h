#pragma once
#include "GameObject.h"
#include <functional>

/*
@enum SceneName
シーン名
*/
enum SceneName
{
	TitleScene,
	PlayScene,
	ResultScene,
	LoadScene,
	NoneScene,
};

/*
@file SceneObjectBase.h
@brief シーンオブジェクトの基底クラス
@detail シーンをオブジェクトにした理由は、オブジェクトの生成とシーンの変更をだけを行えるクラスが必要な時にオブジェクトとして用いることができると気付いたため
*/
class SceneObjectBase :
	public GameObject
{
public:
	/*
	@param _SetSceneFunc シーン変更関数
	@sa GameObjectManager.h
	*/
	SceneObjectBase(std::function<void(SceneName)> _SetSceneFunc);
	~SceneObjectBase();

protected:
	// シーン変更関数
	std::function<void(SceneName)> SetSceneFunc;
};

