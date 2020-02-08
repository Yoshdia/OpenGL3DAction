#include "TitleSceneObject.h"
#include "Renderer.h"
#include "InputSystem.h"
#include "MainCameraObject.h"
#include "NoActionEnemyForLoad.h"
#include "MainCameraObject.h"
#include "BackGroundObject.h"
#include "UserInterfaceBase.h"

TitleSceneObject::TitleSceneObject(std::function<void(SceneName)> _SetSceneFunc) :
	SceneObjectBase(_SetSceneFunc)
{
	printf("/*****/\n");
	printf("*Title*\n");
	printf("/*****/\n");

	RENDERER->GetMesh("Assets/Model/collisionMask.gpmesh");
	RENDERER->GetMesh("Assets/Model/Weapon/SK_Blunt_CinderBlock.gpmesh");
	RENDERER->GetSkeleton("Assets/Model/Weapon/SK_Blunt_CinderBlock.gpskel");
	RENDERER->GetMesh("Assets/Model/Weapon/SK_Forging_ForgeHammer01.gpmesh");
	RENDERER->GetSkeleton("Assets/Model/Weapon/SK_Forging_ForgeHammer01.gpskel");
	RENDERER->GetMesh("Assets/Model/Weapon/SK_Blunt_CinderBlock.gpmesh");
	RENDERER->GetSkeleton("Assets/Model/Weapon/SK_Blunt_CinderBlock.gpskel");
	RENDERER->GetMesh("Assets/Model/Weapon/SK_Dual_Blade_Arrow.gpmesh");
	RENDERER->GetSkeleton("Assets/Model/Weapon/SK_Dual_Blade_Arrow.gpskel");
	RENDERER->GetMesh("Assets/Model/Weapon/SK_Blunt_SpikedClub.gpmesh");
	RENDERER->GetSkeleton("Assets/Model/Weapon/SK_Blunt_SpikedClub.gpskel");
	RENDERER->GetTexture("Assets/Image/Candle/Candle.png");
	RENDERER->GetTexture("Assets/Image/Effect/BrokenHeart.png");
	RENDERER->GetTexture("Assets/Image/Candle/CandleNoFire.png");
	RENDERER->GetTexture("Assets/Image/Item/MarauderBow.png");
	RENDERER->GetTexture("Assets/Image/Item/WarHammer.png");
	RENDERER->GetTexture("Assets/Image/Item/WoodenClub.png");
	RENDERER->SetAmbientLight(Vector3(0.4f, 0.4f, 0.4f));
	DirectionalLight& dir = RENDERER->GetDirectionalLight();
	dir.direction = Vector3(1.0f, 0.7f, -0.7f);
	//dir.diffuseColor = Vector3(1.0f, 1.0f, 1.0f);
	dir.diffuseColor = Vector3(0.78f, 0.88f, 1.0f);
	dir.specColor = Vector3(0.8f, 0.8f, 0.8f);

	mainCamera->SetViewMatrixLerpObject(Vector3(0,0,0), Vector3(0, 70, -120));
	BackGroundObject* back = new BackGroundObject(Vector3(0, 0, 100), Vector3(300, 300, 1), "BlackFloor");

	new NoActionEnemyForLoad(Vector3(0,0,0),EnemyType::MeleeType);
	new NoActionEnemyForLoad(Vector3(-70,0,0),EnemyType::TankType);
	new NoActionEnemyForLoad(Vector3(60,0,0),EnemyType::ShieldType);
	new NoActionEnemyForLoad(Vector3(25,80,10),EnemyType::RangeType);
	new NoActionEnemyForLoad(Vector3(-25,80,10),EnemyType::MageType);

	Vector3 PressUiPos = Vector3(-100,-250,0);
	new UserInterfaceBase(PressUiPos, "Assets/Image/UI/PressUi.png", Vector3(2.5f, 2.5f, 2.5f));
	new UserInterfaceBase(PressUiPos+Vector3(250, 0, 0), "Assets/Image/UI/button_a.png", Vector3(1.1, 1.1, 1.1));
}

TitleSceneObject::~TitleSceneObject()
{
}

void TitleSceneObject::GameObjectInput(const InputState& _keyState)
{
	if (_keyState.Keyboard.GetKeyState(SDL_SCANCODE_RETURN)||
		_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_B) || 
		_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_A))
	{
		SetSceneFunc(SceneName::LoadScene);
	}
}

void TitleSceneObject::UpdateGameObject(float _deltaTime)
{
	
}
