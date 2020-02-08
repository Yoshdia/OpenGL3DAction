#include "ResultSceneObject.h"

ResultSceneObject::ResultSceneObject(std::function<void(SceneName)> _SetSceneFunc) :
	SceneObjectBase(_SetSceneFunc),
	t(0)
{
	printf("/*****/\n");
	printf("*Result*\n");
	printf("/*****/\n");
}

ResultSceneObject::~ResultSceneObject()
{
}

void ResultSceneObject::UpdateGameObject(float _deltaTime)
{
	if (t >= 100)
	{
		SetSceneFunc(SceneName::TitleScene);
	}
	else
	{
		t++;
	}
}
