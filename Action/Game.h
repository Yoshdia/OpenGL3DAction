#pragma once

#include "SDL.h"
#include <unordered_map>
#include <vector>
#include <string>

class FPS;
class GameObject;
class InputSystem;

/*
@file Game.h
@brief ゲームの進行を行う
*/
class Game
{
public:
	Game();
	~Game();

    /*
    @brief	初期化処理
    @return true : 成功, false : 失敗
    */
	bool Initialize();
	/*
	@brief  終了処理
	*/
	void Termination();
	/*
	@brief  ゲームループ
	*/
	void GameLoop();

	static int debug;
private:
	/*
	@brief  入力関連の処理
	*/
    void ProcessInput();
	/*
	@brief  描画関連の処理
	*/
    void GenerateOutput();

	/*
	@brief  ゲームのアップデート処理
	*/
	void UpdateGame();

	/*
	@brief   ロードしたデータの解放
	*/
	void UnloadData();

	// FPS計測クラス
	FPS* fps;
    // 入力管理クラス
	InputSystem* inputSystem;
	//ゲームを続けるかどうか
    bool isRunning;
};

