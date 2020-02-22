#pragma once
#include "GameObject.h"

/*
@file PauseScreen.h
@brief ポーズ画面
@sa PlaySceneObject
*/
class PauseScreen :
	public GameObject
{
public:
	PauseScreen();
	~PauseScreen();

	void PausingUpdateGameObject()override;
	/*
	@fn 指定の入力が会った時にフラグを建てる
	*/
	void GameObjectInput(const InputState& _keyState)override;

private:
	//ポーズ画面の終了
	bool endPause;
	//ポーズ画面でリプレイを選択された
	bool rePlay;

	GameObject* replayButton;
	GameObject* returnButton;


public: //ゲッターセッター
	/*
@return ポーズ画面の終了フラグ
*/
	bool GetEndPause() { return endPause; }

	/*
@return ポーズ画面のやり直しフラグ
*/
	bool GetRePlayFlag() { return rePlay; }
};

