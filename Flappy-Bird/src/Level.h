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
	Level() = default;
	void Init();
	void Reset();

	void OnUpdate(Time frameTime);
	void OnRender();

	const Player& GetPlayer() const { return m_Player; }

private:
	Player m_Player;
	Ref<Texture2D> m_PillarTexture;

	std::vector<Pillar> m_Pillars;
};
