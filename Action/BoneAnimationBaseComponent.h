#pragma once
#include "Component.h"

/*
 @file BoneAnimationBaseComponent.h
 @brief ボーンアニメーションを行うクラスの基底クラス
*/
class BoneAnimationBaseComponent :
	public Component
{
public:
	/*
	@fn メッシュデータクラスを確保
	*/
	BoneAnimationBaseComponent(GameObject* _owner, int updateOrder = 100);
	~BoneAnimationBaseComponent();

	/*
	 @fn 派生クラスで決定する関数と発光関数Flash()を更新する
	*/
	void Update(float _deltaTime)override;

protected:
	//メッシュデータを所有し描画するクラス
	class SkeletalMeshComponent* skeltalMeshComponent;
private:
	/*
	 @fn 派生クラス先の更新関数
	*/
	virtual void UpdateAnimationComponent(float _deltaTime) {};
	/*
	 @fn 発光を行うフラグが建っているとき、メッシュカラーを増減させメッシュデータに色情報を渡す
	*/
	void Flash();
	//発光を行うか
	bool startFlash;
	//元の色から白へ色を増加させているフラグ　false=減少
	bool plusFlashColor;
	//色情報　このクラスは色を複雑に設定しないのでfloat
	float flashColor;
public: //ゲッターセッター
	/*
	 @fn 発光の開始
	*/
	void SetStartFlash() { startFlash = true; plusFlashColor = true; }
};

