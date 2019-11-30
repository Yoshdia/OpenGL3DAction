#include "MovePlayerAnimationClip.h"
#include "Renderer.h"

MovePlayerAnimationClip::MovePlayerAnimationClip() :
	AnimationSpriteClip()
{
	animation[0].sprite = RENDERER->GetTexture("Assets/Image/move1.png");
	animation[0].waitTimeForNextTexture = 10;
	animation[1].sprite = RENDERER->GetTexture("Assets/Image/move2.png");
	animation[1].waitTimeForNextTexture = 10;
	animation[1].sprite = RENDERER->GetTexture("Assets/Image/move3.png");
	animation[1].waitTimeForNextTexture = 10;
}

MovePlayerAnimationClip::~MovePlayerAnimationClip()
{
}
