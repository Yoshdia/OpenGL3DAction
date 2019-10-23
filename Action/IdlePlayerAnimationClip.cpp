#include "IdlePlayerAnimationClip.h"
#include "Renderer.h"



IdlePlayerAnimationClip::IdlePlayerAnimationClip()
{
	animation[0].sprite = RENDERER->GetTexture("Assets/Image/idle1.png");
	animation[0].waitTimeForNextTexture = 20;
	animation[1].sprite = RENDERER->GetTexture("Assets/Image/idle2.png");
	animation[1].waitTimeForNextTexture = 20;
	animation[2].sprite = RENDERER->GetTexture("Assets/Image/idle3.png");
	animation[2].waitTimeForNextTexture = 20;
	animation[3].sprite = RENDERER->GetTexture("Assets/Image/idle4.png");
	animation[3].waitTimeForNextTexture = 20;

}


IdlePlayerAnimationClip::~IdlePlayerAnimationClip()
{
}
