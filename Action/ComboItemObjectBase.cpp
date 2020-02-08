#include "ComboItemObjectBase.h"
#include "ColliderComponent.h"
#include "ParticleComponent.h"
#include "Renderer.h"
#include "Texture.h"
#include "SkeltonObjectChecker.h"

std::unordered_map<int, ComboItemName> ComboItemObjectBase::comboItems;

/*
@param _pos 座標
@param _name アイテムの種類
*/
ComboItemObjectBase::ComboItemObjectBase(const Vector3 & _pos, const ComboItemName& _name) :
	GameObject()
{
	SetPosition(_pos);
	velocity = Vector3(0, 10, 0);
	tag = Tag::ComboItem;
	ColliderComponent* colliderPair = new ColliderComponent(this, 100, Vector3(80, 80, 80), myObjectId, GetTriggerEnterFunc(), GetTriggerStayFunc(), tag);
	ParticleComponent*par = new ParticleComponent(this);
	par->SetScale(50);
	std::string fileName="";
	switch (_name)
	{
	case(ComboItemName::ThrowComboItem):
		fileName = "Assets/Image/Item/MarauderBow.png";
		break;
	case(ComboItemName::RotateComboItem):
		fileName = "Assets/Image/Item/WoodenClub.png";
		break;
	case(ComboItemName::HammerComboItem):
		fileName = "Assets/Image/Item/WarHammer.png";
		break;
	case(ComboItemName::SlashSwordComboItem):
		fileName = "Assets/Image/Item/SharpenedInfantrySword.png";
		break;
	}
	par->SetTextureID(RENDERER->GetTexture(fileName)->GetTextureID());
	noGround = new SkeltonObjectChecker(this, Vector3(0, -30, 0), Vector3(5, 1, 5), Tag::GroundTag);
	comboItems.emplace(myObjectId,_name);
}

ComboItemObjectBase::~ComboItemObjectBase()
{
}

/*
@fn 跳躍して落下する
*/
void ComboItemObjectBase::UpdateGameObject(float _deltaTime)
{
	if (noGround->GetNoTouchingFlag())
	{
		velocity.y-=(20*_deltaTime);
		if (velocity.y <= -10)
		{
			velocity.y = -10;
		}
	}
	else
	{
		velocity.y = 0;
	}
		SetPosition(velocity + position);
}

/*
	@fn オブジェクトIDでそのオブジェクトのアイテムを検索する
	@param _objectID オブジェクトID
	@return 検索結果
	*/
ComboItemName ComboItemObjectBase::SearchComboId(const int & _objectId)
{
	auto iter = comboItems.find(_objectId);
	if (iter != comboItems.end())
	{
		ComboItemName name = iter->second;
		return name;
	}
	return ComboItemName::NoComboItem;
}
