#include "JumpPlayerAnimationClip.h"
#include "Renderer.h"



JumpPlayerAnimationClip::JumpPlayerAnimationClip():
	AnimationSpriteClip()
{
	animation[0].sprite = RENDERER->GetTexture("Assets/Image/Jump.png");
	animation[0].waitTimeForNextTexture = 100;
	loop = false;
}


JumpPlayerAnimationClip::~JumpPlayerAnimationClip()
{
}