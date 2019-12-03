#include "IdlePlayerAnimationClip.h"
#include "Renderer.h"



IdlePlayerAnimationClip::IdlePlayerAnimationClip()
{
	animation[0].sprite = RENDERER->GetTexture("Assets/Image/Idle1.png");
	animation[0].waitTimeForNextTexture = 20;
	animation[1].sprite = RENDERER->GetTexture("Assets/Image/Idle2.png");
	animation[1].waitTimeForNextTexture = 20;
	animation[2].sprite = RENDERER->GetTexture("Assets/Image/Idle3.png");
	animation[2].waitTimeForNextTexture = 20;
	loop = true;
}


IdlePlayerAnimationClip::~IdlePlayerAnimationClip()
{
}
