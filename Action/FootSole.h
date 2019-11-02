#pragma once
#include "GameObject.h"

/*
 @file FootSole.h
 @brief GameObjectの足元に配置するパネル状のオブジェクト、groundTagを所持しているオブジェクトに接触するとフラグを倒す
	*/
class FootSole :
	public GameObject
{
public:
	/*
   @param parentPosition 親になるオブジェクトの座標アドレス
   @param _jumped 親になるオブジェクトのジャンプフラグアドレス。FootSoleがgroundTagと接触したときにfalseにする
 */
	FootSole(Vector3& parentPosition, bool& _jumped);
	~FootSole();

	void UpdateGameObject(float _deltaTime)override;
private:
	void OnTriggerStay(ColliderComponent* colliderPair)override;
	//親オブジェクトの座標
	Vector3* parentPosition;
	//groundTagと接触しているか
	bool *noLand;
	//自信の座標、parentPositionと足しでpositionにする
	Vector3 footPos;
};

