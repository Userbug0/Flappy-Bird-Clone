#pragma once

#include <Athena.h>
#include "Player.h"

using namespace Athena;


struct Pillar
{

};


class Level
{
public:
	void Init();

	void OnUpdate(Time frameTime);
	void OnRender();
	void OnEvent(Event& event);

private:
	Player m_Player;
	Ref<Texture2D> m_PillarTexture;

	std::vector<Pillar> m_Pillars;
};
