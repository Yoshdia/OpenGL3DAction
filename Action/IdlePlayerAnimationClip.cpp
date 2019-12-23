#include "IdlePlayerAnimationClip.h"
#include "Renderer.h"



IdlePlayerAnimationClip::IdlePlayerAnimationClip()
{
	animation[0].sprite = RENDERER->GetTexture("Assets/Image/Idle1.png");
	animation[0].waitTimeForNextTexture = 100;
	animation[1].sprite = RENDERER->GetTexture("Assets/Image/Idle1.png");
	animation[1].waitTimeForNextTexture = 100;
	loop = true;
}


IdlePlayerAnimationClip::~IdlePlayerAnimationClip()
{
}
