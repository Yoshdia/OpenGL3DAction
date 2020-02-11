#include "PlaySceneObject.h"
#include "Renderer.h"
#include "StageCreater.h"

#include "TestModel.h"
#include "PlayerCharacter.h"
#include "GameEndEventSystem.h"
#include "InputSystem.h"
#include "PauseScreen.h"
#include "ParticleObject.h"

#include "UserInterfaceBase.h"
#include "BombParticleEffect.h"

#include "DebugBox.h"

const Vector3 PlaySceneObject::EventWordObjectPos = Vector3(0, 250, 0);
const Vector3 PlaySceneObject::EventWordObjectSize = Vector3(2, 2, 2);

PlaySceneObject::PlaySceneObject(std::function<void(SceneName)> _SetSceneFunc) :
	SceneObjectBase(_SetSceneFunc),
	player(nullptr),
	bossEnemy(nullptr),
	pausingScreen(nullptr),
	gameClear(false),
	gameOver(false),
	endingCount(400),
	endingDelay(100),
	createdEventWordObject(false),
	endEffectPos(Vector3(0, 0, 0))
{
	// Setup lights
	RENDERER->SetAmbientLight(Vector3(0.4f, 0.4f, 0.4f));
	DirectionalLight& dir = RENDERER->GetDirectionalLight();
	dir.direction = Vector3(1.0f, 0.7f, -0.7f);
	//dir.diffuseColor = Vector3(1.0f, 1.0f, 1.0f);
	dir.diffuseColor = Vector3(0.78f, 0.88f, 1.0f);
	dir.specColor = Vector3(0.8f, 0.8f, 0.8f);

	//new TestModel;
	StageCreater* stageCreater = new StageCreater();

	//�X�e�[�W���t�@�C�����J��
	if (!stageCreater->OpenFile())
	{
		//�v���C���[�𐶐�
		player = stageCreater->CreatePlayer();
		//�X�e�[�W�𐶐�����
		stageCreater->CreateStage();
		//�Փ˔�����s��Ȃ��w�i�𐶐�
		stageCreater->CreateBackGround();
		//�{�X�ւ̃|�C���^���擾
		bossEnemy = stageCreater->GetBossEnemy();
		//�{�X���������ꂽ���W�����̂܂܃N���A���̃G�t�F�N�g�����ʒu��
		endEffectPos = bossEnemy->GetPosition();
	}
}


PlaySceneObject::~PlaySceneObject()
{
	if (pausingScreen != nullptr)
	{
		pausingScreen = nullptr;
	}
}

void PlaySceneObject::UpdateGameObject(float _deltaTime)
{
	if (!gameClear && !gameOver)
	{
		SceneChangeEvents();
	}
	else
	{
		if (EventWordObjectDelay())
		{
			if (endingCount < 0)
			{
				SetSceneFunc(SceneName::TitleScene);
				pauzingEvent = PauzingEvent::NoneEvent;
			}
			else
			{
				endingCount--;
			}
		}
	}
}

void PlaySceneObject::GameObjectInput(const InputState& _keyState)
{
	//�|�[�Y��ʂ�
	if (_keyState.Keyboard.GetKeyState(SDL_SCANCODE_F1) ||
		(_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_X)) &&
		_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_START))
	{
		if (pausingScreen == nullptr)
		{
			pausingScreen = new PauseScreen();
			pauzingEvent = PauzingEvent::PausingEvent;
		}
	}
}

void PlaySceneObject::PausingUpdateGameObject()
{
	if (pausingScreen != nullptr) 
	{
		if (pausingScreen->GetEndPause())
		{
			pauzingEvent = PauzingEvent::NoneEvent;
			delete pausingScreen;
			pausingScreen = nullptr;
		}
		if (pausingScreen->GetRePlayFlag())
		{
			pauzingEvent = PauzingEvent::NoneEvent;
			SetSceneFunc(SceneName::TitleScene);

		}
	}

	if (pauzingEvent == PauzingEvent::GameOverEvent)
	{
		gameOver = true;
		UpdateGameObject(0);
	}
}

/*
@fn �{�X�N���X�����j���ꂽ�Ƃ��N���A�t���O�����Ă�
*/
void PlaySceneObject::SceneChangeEvents()
{
	bool isChangedScene = false;
	if (bossEnemy != nullptr)
	{
		if (bossEnemy->GetState() == State::Dead)
		{
			isChangedScene = true;
			gameClear = true;
		}
	}
}
/*
@fn �N���A�A�Q�[���I�[�o�[��ʂ�\������܂ł̑ҋ@���Ԃ��Ǘ�����ʂ�\������
*/
bool PlaySceneObject::EventWordObjectDelay()
{
	if (createdEventWordObject)
	{
		return true;
	}
	if (endingDelay < 0)
	{
		if (gameClear)
		{
			new UserInterfaceBase(EventWordObjectPos, "Assets/Image/Ui/GameClear.png", EventWordObjectSize);
		}
		else
		{
			new UserInterfaceBase(EventWordObjectPos, "Assets/Image/Ui/GameOver.png", EventWordObjectSize);
		}
		new BombParticleEffect(endEffectPos, Vector3(10, 20, 0));
		new BombParticleEffect(endEffectPos, Vector3(-10, 20, 0));
		new BombParticleEffect(endEffectPos, Vector3(10, 18, 0));
		new BombParticleEffect(endEffectPos, Vector3(10, 14, 0));
		new BombParticleEffect(endEffectPos, Vector3(10, 11, 0));
		new BombParticleEffect(endEffectPos, Vector3(10, 8, 0));
		new BombParticleEffect(endEffectPos, Vector3(10, 5, 0));
		new BombParticleEffect(endEffectPos, Vector3(-10, 18, 0));
		new BombParticleEffect(endEffectPos, Vector3(-10, 14, 0));
		new BombParticleEffect(endEffectPos, Vector3(-10, 1, 0));
		new BombParticleEffect(endEffectPos, Vector3(-10, 8, 0));
		new BombParticleEffect(endEffectPos, Vector3(-10, 5, 0));
		createdEventWordObject = true;
		return true;
	}
	else
	{
		endingDelay--;
	}
	return false;
}

