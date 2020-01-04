#include "AttackRoopPlayerAnimationClip.h"
#include "Renderer.h"


AttackRoopPlayerAnimationClip::AttackRoopPlayerAnimationClip()
	:AnimationSpriteClip()
{
	animation[0].sprite = RENDERER->GetTexture("Assets/Image/Attack3.png");
	animation[0].waitTimeForNextTexture = 5;
	animation[1].sprite = RENDERER->GetTexture("Assets/Image/Attack4.png");
	animation[1].waitTimeForNextTexture = 5;
	loop = true;
}


AttackRoopPlayerAnimationClip::~AttackRoopPlayerAnimationClip()
{
}
