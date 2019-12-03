#include "AttackPlayerAnimationClip.h"
#include "Renderer.h"


AttackPlayerAnimationClip::AttackPlayerAnimationClip()
{
	animation[0].sprite = RENDERER->GetTexture("Assets/Image/Attack1.png");
	animation[0].waitTimeForNextTexture = 5;	
	animation[1].sprite = RENDERER->GetTexture("Assets/Image/Attack2.png");
	animation[1].waitTimeForNextTexture = 5;
	loop = false;

}


AttackPlayerAnimationClip::~AttackPlayerAnimationClip()
{
}
