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
@brief �Q�[���̐i�s���s��
*/
class Game
{
public:
	Game();
	~Game();

    /*
    @brief	����������
    @return true : ����, false : ���s
    */
	bool Initialize();
	/*
	@brief  �I������
	*/
	void Termination();
	/*
	@brief  �Q�[�����[�v
	*/
	void GameLoop();

	static int debug;
private:
	/*
	@brief  ���͊֘A�̏���
	*/
    void ProcessInput();
	/*
	@brief  �`��֘A�̏���
	*/
    void GenerateOutput();

	/*
	@brief  �Q�[���̃A�b�v�f�[�g����
	*/
	void UpdateGame();

	/*
	@brief   ���[�h�����f�[�^�̉��
	*/
	void UnloadData();

	// FPS�v���N���X
	FPS* fps;
    // ���͊Ǘ��N���X
	InputSystem* inputSystem;
	//�Q�[���𑱂��邩�ǂ���
    bool isRunning;
};

