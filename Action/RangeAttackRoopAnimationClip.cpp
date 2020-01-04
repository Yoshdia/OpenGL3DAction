#include "RangeAttackRoopAnimationClip.h"
#include "Renderer.h" 


RangeAttackRoopAnimationClip::RangeAttackRoopAnimationClip()
	:AnimationSpriteClip()
{
	animation[0].sprite = RENDERER->GetTexture("Assets/Image/attack3.png");
	animation[0].waitTimeForNextTexture = 12;
	animation[1].sprite = RENDERER->GetTexture("Assets/Image/attack4.png");
	animation[1].waitTimeForNextTexture = 12;
	loop = true;
}


RangeAttackRoopAnimationClip::~RangeAttackRoopAnimationClip()
{
}
