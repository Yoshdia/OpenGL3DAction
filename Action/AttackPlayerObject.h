#pragma once
#include "GameObject.h"
#include "ComboItemObjectBase.h"

/*
@file AttackPlayerObject.h
@brief Playerに近接コンボ、遠距離攻撃を行わせるクラス
*/
class AttackPlayerObject :
	public GameObject
{
public:
	AttackPlayerObject(GameObject* _owner);
	~AttackPlayerObject();
	void UpdateGameObject(float _deltaTime)override;
	void SetInput(const bool& _lInput, const bool& _rInput) { inputLeftChange = _lInput; inputRightChange =_rInput; }
	/*
	@fn 近距離攻撃
	@param _direction 攻撃時のプレイヤーの向き
	@param _slot 攻撃スロット
	@param _range このコンボが遠距離攻撃かどうか
	@return プレイヤーに付与する行動不可な時間
	*/
	float Attack(const float& _direction, const int& _slot, bool& _range);
private:
	void OnTriggerStay(ColliderComponent* _colliderPair) ;
	ComboItemObjectBase* DropComboItem(const ComboItemName& _name,const int& slot);
	void DeleteSlot(const int& _slot);

	static const Vector3 RightIconPos;
	static const Vector3 LeftIconPos;

	bool inputLeftChange;
	bool inputRightChange;
	GameObject* owner;
	//つけ外しを行う攻撃スロット
	class ComboMeanPlayerBase* firstSlotAttack;
	//つけ外しを行う攻撃スロット
	class ComboMeanPlayerBase* secondSlotAttack;
	//近距離攻撃のコンボを次につなげる猶予時間。これが0になるとコンボ状態をリセットする
	float waitTimeForNextAttack;

	int changeCount;
	class UserInterfaceBase* leftIcon;
	class UserInterfaceBase* rightIcon;
	class UserInterfaceBase* lButtonGuide;
	class UserInterfaceBase* lButtonIcon;
	class UserInterfaceBase* rButtonGuide;
	class UserInterfaceBase* rButtonIcon;
	bool itemCollided;
};

/*
☆攻撃クラスの追加手順
�@矢や剣のような、各々の挙動のみを制御する武器クラス:GameObjectを作成
�A武器クラスを受けとった座標、向きに発生させる攻撃クラス:AttackBaseを作成
�B攻撃クラスをコンボごとに生成するコンボクラス:ComboMeanPlayerBaseを作成
~付け替えを行う場合~
�CComboItemObjectBase内の列挙型で宣言
�DこのクラスAttackPlayerObject内でその攻撃クラスを付け替えるため関数に文章を加える
*/
