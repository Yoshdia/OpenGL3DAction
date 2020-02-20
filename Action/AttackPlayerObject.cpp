#include "AttackPlayerObject.h"
#include "RotateTripleWeaponCombo.h"
#include "ThrowWeaponCombo.h"
#include "ColliderComponent.h"
#include "ComboItemObjectBase.h"
#include "DoubleHammerCombo.h"
#include "UserInterfaceBase.h"
#include "TakeItemEffectUI.h"
#include "TripleSlashSwordCombo.h"
#include "TakeItemUi.h"

const Vector3 AttackPlayerObject::LeftIconPos = Vector3(300, -400, 0);
const Vector3 AttackPlayerObject::RightIconPos = Vector3(500, -400, 0);
const float AttackPlayerObject::IconSize = 0.85f;
const float AttackPlayerObject::BottonSize = 0.3f;

/*
@param _owner 親オブジェクト
*/
AttackPlayerObject::AttackPlayerObject(GameObject* _owner) :
	GameObject(),
	owner(_owner),
	waitTimeForNextAttack(0),
	itemChangeWaitCount(0),
	itemCollided(false)
{
	//左スロットを初期化
	firstSlotAttack = new RotateTripleWeaponCombo();
	//左スロットの武器アイコンを初期化
	leftIcon = new UserInterfaceBase(LeftIconPos, firstSlotAttack->GetComboIconFileName());
	leftIcon->SetScale(IconSize);
	//左スロットの操作説明UIを初期化
	UserInterfaceBase* xButton = new UserInterfaceBase(LeftIconPos, "Assets/Image/UI/button_x.png", Vector3(BottonSize, BottonSize, BottonSize), 1000);
	//左スロットの上部に設置するトリガーUIを初期化
	lButtonIcon = new   UserInterfaceBase(LeftIconPos + Vector3(0, 50, 0), "Assets/Image/UI/bumper1_l1.png", Vector3(BottonSize, BottonSize, BottonSize), 550);
	lButtonGuide = new   UserInterfaceBase(Vector3(-25, 50, 0), "Assets/Image/UI/bumper1_l1.png", Vector3(BottonSize, BottonSize, BottonSize), 500);
	lButtonGuide->SetState(State::Dead);

	//右スロットを初期化
	secondSlotAttack = new RotateTripleWeaponCombo();
	//右スロットの武器アイコンを初期化
	rightIcon = new UserInterfaceBase(RightIconPos, secondSlotAttack->GetComboIconFileName());
	rightIcon->SetScale(IconSize);
	//右スロットの操作説明UIを初期化
	UserInterfaceBase* yButton = new UserInterfaceBase(RightIconPos, "Assets/Image/UI/button_y.png", Vector3(BottonSize, BottonSize, BottonSize), 1000);
	//右スロットの上部に設置するトリガーUIを初期化
	rButtonIcon = new   UserInterfaceBase(RightIconPos + Vector3(0, 50, 0), "Assets/Image/UI/bumper1_r1.png", Vector3(BottonSize, BottonSize, BottonSize), 550);
	rButtonGuide = new   UserInterfaceBase(Vector3(25, 50, 0), "Assets/Image/UI/bumper1_r1.png", Vector3(BottonSize, BottonSize, BottonSize), 500);
	rButtonGuide->SetState(State::Dead);

	//アイテムとのみ衝突するタグ
	tag = SubPlayerObject;
	//衝突クラス
	ColliderComponent* colliderPair = new ColliderComponent(this, 100, Vector3(30, 30, 30), gameObjectId, GetTriggerEnterFunc(), GetTriggerStayFunc(), tag);
}

AttackPlayerObject::~AttackPlayerObject()
{
}

void AttackPlayerObject::UpdateGameObject(float _deltaTime)
{
	//親オブジェクトの位置に移動
	SetPosition(owner->GetPosition());
	//攻撃入力が行われずにコンボ受付猶予がゼロになったとき
	if (waitTimeForNextAttack < 0)
	{
		//コンボ状態をリセットする
		firstSlotAttack->ComboReset();
		//コンボ状態をリセットする
		secondSlotAttack->ComboReset();
	}
	else
	{
		waitTimeForNextAttack--;
	}
	//アイテムの取得インターバルカウントを減少
	if (itemChangeWaitCount >= 0)
	{
		itemChangeWaitCount--;
	}
	//何らかのアイテムと衝突しているとき
	if (itemCollided)
	{
		//画面中央にアイテム変更用UIを設置
		lButtonGuide->SetState(State::Active);
		rButtonGuide->SetState(State::Active);
		itemCollided = false;
	}
	else
	{
		//画面中央のアイテム変更用UIを撤去
		lButtonGuide->SetState(State::Dead);
		rButtonGuide->SetState(State::Dead);
	}
}

/*
@fn 近距離攻撃
@param _direction 攻撃時のプレイヤーの向き
@param _slot 攻撃スロット
@param _range このコンボが遠距離攻撃かどうか
@return プレイヤーに付与する行動不可な時間
*/
float AttackPlayerObject::Attack(const float& _direction, const int& _slot, bool& _range)
{
	//プレイヤーに付与する行動不可な時間
	float playerCanNotMoveTime = 0.0f;

	//スロットを識別
	if (_slot == 1)
	{
		if (firstSlotAttack != nullptr)
		{
			//親オブジェクトの位置で攻撃する
			firstSlotAttack->Attack(owner->GetPosition(), _direction, playerCanNotMoveTime, waitTimeForNextAttack);
			//攻撃クラスから、遠距離攻撃であるかを受け取る
			_range = firstSlotAttack->GetRangeFlag();
		}
	}
	else
	{
		if (secondSlotAttack != nullptr)
		{
			//親オブジェクトの位置で攻撃する
			secondSlotAttack->Attack(owner->GetPosition(), _direction, playerCanNotMoveTime, waitTimeForNextAttack);
			//攻撃クラスから、遠距離攻撃であるかを受け取る
			_range = secondSlotAttack->GetRangeFlag();
		}
	}

	return playerCanNotMoveTime;
}

/*
@fn アイテムと衝突しているときに入力が行われていたら攻撃を変更する
*/
void AttackPlayerObject::OnTriggerStay(ColliderComponent* _colliderPair)
{
	if (_colliderPair->GetObjectTag() == Tag::ComboItem)
	{
		//アイテム取得のインターバルがゼロの時
		if (itemChangeWaitCount <= 0)
		{
			//取得用の入力が行われていたら
			if (inputLeftChange || inputRightChange)
			{
				//変更するアイテム名を取得
				ComboItemName name = ComboItemObjectBase::SearchComboId(_colliderPair->GetId());
				//左スロットの入力
				if (inputLeftChange)
				{
					//設置されていたアイテムを非アクティブにする
					_colliderPair->GetOwner()->SetState(State::Dead);
					//現在所持しているクラスのアイテムをその場に置く
					firstSlotAttack->DropMyItem(position);
					//取得したアイテムの名前をもとに、現在の攻撃クラスを開放し新たな攻撃クラスをセットする
					DropComboItem(name, 1);
					//取得したアイテムの画像を画面中央から取得したスロットの方向へ進ませる
					new TakeItemUi(Vector3(0, 0, 0), LeftIconPos, firstSlotAttack->GetComboIconFileName(), Vector3(0.8f, 0.8f, 0.8f));
				}
				//右スロットの入力
				else if (inputRightChange)
				{
					//設置されていたアイテムを非アクティブにする
					_colliderPair->GetOwner()->SetState(State::Dead);
					//現在所持しているクラスのアイテムをその場に置く
					secondSlotAttack->DropMyItem(position);
					//取得したアイテムの名前をもとに、現在の攻撃クラスを開放し新たな攻撃クラスをセットする
					DropComboItem(name, 2);
					//取得したアイテムの画像を画面中央から取得したスロットの方向へ進ませる
					new TakeItemUi(Vector3(0, 0, 0), RightIconPos, secondSlotAttack->GetComboIconFileName(), Vector3(0.8f, 0.8f, 0.8f));
				}

			}
		}
		//アイテムと衝突
		itemCollided = true;
	}
}

/*
@fn 現在所持している攻撃クラスを開放しその攻撃クラスのアイテムをその場に設置して引数の攻撃を取得する
@param _name 取得したアイテム名
@param _slot 変更を行う攻撃スロットナンバー
*/
ComboItemObjectBase* AttackPlayerObject::DropComboItem(const ComboItemName& _name, const int& _slot)
{
	//アイテムを取得したのでアイテム取得インターバルを追加
	itemChangeWaitCount = 25;
	//現在の攻撃スロットを開放しアイテム名をもとに攻撃をセット
	switch (_name)
	{
	case(ComboItemName::RotateComboItem):
		DeleteSlot(_slot);
		if (_slot == 1)
		{
			firstSlotAttack = new RotateTripleWeaponCombo;
		}
		else
		{
			secondSlotAttack = new RotateTripleWeaponCombo;
		}
		break;
	case(ComboItemName::ThrowComboItem):
		DeleteSlot(_slot);
		if (_slot == 1)
		{
			firstSlotAttack = new ThrowWeaponCombo;
		}
		else
		{
			secondSlotAttack = new ThrowWeaponCombo;
		}
		break;
	case(ComboItemName::HammerComboItem):
		DeleteSlot(_slot);
		if (_slot == 1)
		{
			firstSlotAttack = new DoubleHammerCombo;
		}
		else
		{
			secondSlotAttack = new DoubleHammerCombo;
		}
		break;
	case(ComboItemName::SlashSwordComboItem):
		DeleteSlot(_slot);
		if (_slot == 1)
		{
			firstSlotAttack = new TripleSlashSwordCombo;
		}
		else
		{
			secondSlotAttack = new TripleSlashSwordCombo;
		}
		break;
	}
	if (_slot == 1)
	{
		leftIcon = new UserInterfaceBase(LeftIconPos, firstSlotAttack->GetComboIconFileName(), Vector3(IconSize, IconSize, IconSize), 150);
		new TakeItemEffectUI(LeftIconPos);
	}
	else
	{
		rightIcon = new UserInterfaceBase(RightIconPos, secondSlotAttack->GetComboIconFileName(), Vector3(IconSize, IconSize, IconSize), 150);
		new TakeItemEffectUI(RightIconPos);
	}
	return nullptr;
}

/*
@fn　スロットを解放する
@param _slot 解放したいスロットナンバー
*/
void AttackPlayerObject::DeleteSlot(const int& _slot)
{
	if (_slot == 1)
	{
		if (firstSlotAttack != nullptr)
		{
			delete firstSlotAttack;
		}
		if (leftIcon != nullptr)
		{
			delete leftIcon;
		}
	}
	else
	{
		if (secondSlotAttack != nullptr)
		{
			delete secondSlotAttack;
		}
		if (rightIcon != nullptr)
		{
			delete rightIcon;
		}
	}
}
