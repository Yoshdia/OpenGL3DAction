#include "TitleSceneObject.h"

TitleSceneObject::TitleSceneObject(std::function<void(SceneName)> _SetSceneFunc) :
	SceneObjectBase(_SetSceneFunc),
	t(0)
{
	printf("/******/\n");
	printf("*Title*\n");
	printf("/******/\n");
}

TitleSceneObject::~TitleSceneObject()
{
}

void TitleSceneObject::UpdateGameObject(float _deltaTime)
{
	if (t >= 100)
	{
		SetSceneFunc(SceneName::PlayScene);
	}
	else
	{
		t++;
	}
}
