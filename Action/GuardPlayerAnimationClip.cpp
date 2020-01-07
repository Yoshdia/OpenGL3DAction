#include "GuardPlayerAnimationClip.h"
#include "Renderer.h"



GuardPlayerAnimationClip::GuardPlayerAnimationClip() :
	AnimationSpriteClip()
{
	animation[0].sprite = RENDERER->GetTexture("Assets/Image/Guard1.png");
	animation[0].waitTimeForNextTexture = 15;
	animation[1].sprite = RENDERER->GetTexture("Assets/Image/Guard2.png");
	animation[1].waitTimeForNextTexture = 100;
	loop = false;
}


GuardPlayerAnimationClip::~GuardPlayerAnimationClip()
{
}
