#include "AvoidancingPlayerAnimation.h"
#include "Renderer.h"
#include "Texture.h"

AvoidancingPlayerAnimation::AvoidancingPlayerAnimation()
{
	animation[0].sprite = RENDERER->GetTexture("Assets/Image/Kaiten1.png");
	animation[0].waitTimeForNextTexture = 1;	
	animation[1].sprite = RENDERER->GetTexture("Assets/Image/Kaiten2.png");
	animation[1].waitTimeForNextTexture = 1;	
	animation[2].sprite = RENDERER->GetTexture("Assets/Image/Kaiten3.png");
	animation[2].waitTimeForNextTexture = 1;	
	animation[3].sprite = RENDERER->GetTexture("Assets/Image/Kaiten4.png");
	animation[3].waitTimeForNextTexture = 1;
	animation[4].sprite = RENDERER->GetTexture("Assets/Image/Kaiten5.png");
	animation[4].waitTimeForNextTexture = 1;
	animation[5].sprite = RENDERER->GetTexture("Assets/Image/Kaiten6.png");
	animation[5].waitTimeForNextTexture = 1;
	animation[6].sprite = RENDERER->GetTexture("Assets/Image/Kaiten7.png");
	animation[6].waitTimeForNextTexture = 1;
	animation[7].sprite = RENDERER->GetTexture("Assets/Image/Kaiten8.png");
	animation[7].waitTimeForNextTexture = 1;
	loop = true;
}


AvoidancingPlayerAnimation::~AvoidancingPlayerAnimation()
{
}
