#include "RangeAttackPlayerAnimationClip.h"
#include "Renderer.h"


RangeAttackPlayerAnimationClip::RangeAttackPlayerAnimationClip()
{
	animation[0].sprite = RENDERER->GetTexture("Assets/Image/attack1.png");
	animation[0].waitTimeForNextTexture = 10;
	animation[1].sprite = RENDERER->GetTexture("Assets/Image/attack2.png");
	animation[1].waitTimeForNextTexture = 10;

	loop = true;
}


RangeAttackPlayerAnimationClip::~RangeAttackPlayerAnimationClip()
{
}
