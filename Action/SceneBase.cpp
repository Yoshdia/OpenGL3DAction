//=============================================================================
//	@file	SceneBase.cpp
//	@brief	�V�[���N���X�̊��N���X
//	@autor	���{ �a��
//	@date	2019/10/3
//=============================================================================


#include "SceneBase.h"
#include "PlayScene.h"
#include "Game.h"

SceneBase::SceneBase()
{
}

SceneBase::~SceneBase()
{
}

SceneBase* SceneBase::StartGame()
{
    return new PlayScene();
}
