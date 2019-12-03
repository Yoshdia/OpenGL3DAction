#include "RangeAttackPlayerAnimationClip.h"
#include "Renderer.h"


RangeAttackPlayerAnimationClip::RangeAttackPlayerAnimationClip()
{
	animation[0].sprite = RENDERER->GetTexture("Assets/Image/range1.png");
	animation[0].waitTimeForNextTexture = 10;
	animation[1].sprite = RENDERER->GetTexture("Assets/Image/range2.png");
	animation[1].waitTimeForNextTexture = 10;
	animation[2].sprite = RENDERER->GetTexture("Assets/Image/range3.png");
	animation[2].waitTimeForNextTexture = 10;
	loop = false;
}


RangeAttackPlayerAnimationClip::~RangeAttackPlayerAnimationClip()
{
}
