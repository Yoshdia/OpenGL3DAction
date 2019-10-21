#include "MovePlayerAnimationClip.h"
#include "Renderer.h"

MovePlayerAnimationClip::MovePlayerAnimationClip() :
	AnimationSpriteClip()
{
	animation[0].sprite = RENDERER->GetTexture("Resouce/Img/once.png");
	animation[0].waitTimeForNextTexture = 20;
	animation[1].sprite = RENDERER->GetTexture("Resouce/Img/twice.png");
	animation[1].waitTimeForNextTexture = 40;
	animation[2].sprite = RENDERER->GetTexture("Resouce/Img/third.png");
	animation[2].waitTimeForNextTexture = 60;
	animation[3].sprite = RENDERER->GetTexture("Resouce/Img/fourth.png");
	animation[3].waitTimeForNextTexture = 10;
	
	animation[4].sprite = nullptr;
	animation[4].waitTimeForNextTexture = 0;
}

MovePlayerAnimationClip::~MovePlayerAnimationClip()
{
}
