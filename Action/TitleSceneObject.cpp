#include "TitleSceneObject.h"
#include "Renderer.h"

TitleSceneObject::TitleSceneObject(std::function<void(SceneName)> _SetSceneFunc) :
	SceneObjectBase(_SetSceneFunc),
	t(0)
{
	printf("/******/\n");
	printf("*Title*\n");
	printf("/******/\n");

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
	RENDERER->GetMesh("Assets/Model/Stage/SM_Env_Ice_Cliffs_CliffWall_01b.gpmesh");
	RENDERER->GetTexture("Assets/Image/Candle/Candle.png");
	RENDERER->GetTexture("Assets/Image/Effect/BrokenHeart.png");
	RENDERER->GetTexture("Assets/Image/Candle/CandleNoFire.png");
	RENDERER->GetTexture("Assets/Image/Item/MarauderBow.png");
	RENDERER->GetTexture("Assets/Image/Item/WarHammer.png");
	RENDERER->GetTexture("Assets/Image/Item/WoodenClub.png");
}

TitleSceneObject::~TitleSceneObject()
{
}

void TitleSceneObject::UpdateGameObject(float _deltaTime)
{
	if (t >= 1)
	{
		SetSceneFunc(SceneName::PlayScene);
	}
	else
	{
		t++;
	}
}
