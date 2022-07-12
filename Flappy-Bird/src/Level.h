#pragma once

#include <Athena.h>
#include "Player.h"

using namespace Athena;


struct Pillar
{
	Vector3 TopPosition;
	Vector2 TopScale = { 12, 16 };

	Vector3 BottomPosition;
	Vector2 BottomScale = { 12, 16 };
};


class Level
{
public:
	Level() = default;
	void Init();
	void Reset();

	void OnUpdate(Time frameTime);
	void OnRender();

	void GameOver();

	const Player& GetPlayer() const { return m_Player; }
	bool IsGameOver() const { return m_GameOver; }

private:
	void CreatePillar(size_t index, float offset);
	bool CollisionTest();

private:
	Player m_Player;

	bool m_GameOver = false;

	Ref<Texture2D> m_PillarTexture;
	std::vector<Pillar> m_Pillars;
	size_t m_PillarIndex = 0;
	float m_PillarTarget = 30;
	Vector3 m_PillarHSV = { 0.0f, 0.8f, 0.8f };;
};
