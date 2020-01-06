//=============================================================================
//	@file	Game.h
//	@brief	ゲーム全体の進行をまとめる
//	@autor	居本 和哉
//	@date	2019/10/3
//=============================================================================

//-----------------------------------------------------------------------------
//	@brief	プリプロセッサ
//-----------------------------------------------------------------------------
#pragma once

//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "SDL.h"
#include <unordered_map>
#include <vector>
#include <string>

//-----------------------------------------------------------------------------
//	@brief	前方宣言
//-----------------------------------------------------------------------------
class FPS;
class GameObject;
class InputSystem;

//-----------------------------------------------------------------------------
//	@brief	Gameクラス
//-----------------------------------------------------------------------------
class Game
{
public:
//===================== パブリック関数 ======================//

	Game();
	~Game();

    /**
    @brief	初期化処理
    @return true : 成功, false : 失敗
    */
	bool Initialize();
	/**
	@brief  終了処理
	*/
	void Termination();
	/**
	@brief  ゲームループ
	*/
	void GameLoop();

	static int debug;
private:
//===================== プライベート関数 ======================//

	/**
	@brief  入力関連の処理
	*/
    void ProcessInput();
	/**
	@brief  描画関連の処理
	*/
    void GenerateOutput();

	/**
	@brief  ゲームのアップデート処理
	*/
	void UpdateGame();

	/**
	@brief   ロードしたデータの解放
	*/
	void UnloadData();

//===================== プライベート変数 ======================//

	// FPS計測クラス
	FPS* fps;
    // 入力管理クラス
	InputSystem* inputSystem;
	//ゲームを続けるかどうか
    bool isRunning;
};

