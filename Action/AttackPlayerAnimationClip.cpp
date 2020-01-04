#include "AttackPlayerAnimationClip.h"
#include "Renderer.h"


AttackPlayerAnimationClip::AttackPlayerAnimationClip():
	AnimationSpriteClip()
{
	animation[0].sprite = RENDERER->GetTexture("Assets/Image/Attack1.png");
	animation[0].waitTimeForNextTexture = 10;	
	animation[1].sprite = RENDERER->GetTexture("Assets/Image/Attack2.png");
	animation[1].waitTimeForNextTexture = 10;
	loop = false;

}


AttackPlayerAnimationClip::~AttackPlayerAnimationClip()
{
}
