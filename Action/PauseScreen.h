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
	//ゲームを再開するUI
	class UserInterfaceBase* playButton;
	//タイトルへ戻るUI
	class UserInterfaceBase* backTitleButton;
	//casolによって選択されているUIの位置を表示するための半透明の黒い板
	class UserInterfaceBase* selectedButtonLeft;
	//casolによって選択されているUIの位置を表示するための半透明の黒い板
	class UserInterfaceBase* selectedButtonRight;
	//playButton、backTitleButtonのサイズ
	static const float UiSize;
	//選択中のカーソル位置
	int casol;
	//選択時の決定入力
	bool inputSelectedButton;
	//選択中のカーソル位置
	int inputDirection;
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

