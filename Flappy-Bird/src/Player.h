#pragma once

#include <Athena.h>
#include "ParticlesGenerator.h"

using namespace Athena;


class Player
{
public:
	Player() = default;
	void Init();
	void Reset();

	void OnUpdate(Time frameTime);
	void OnRender();

	const Vector2& GetPosition() const { return m_Position; }

private:
	Ref<Texture2D> m_Rocket;

	ParticlesGenerator m_ParticleSystem;
	ParticleDesc m_EngineParticle;
	ParticleDesc m_SmokeParticle;

	Vector2 m_Position = { -0.5f, 0 };
	Vector2 m_Velocity = { 0.1f, 0 };
	float m_Rotation = -90.f;

	float m_Gravity = 2.f;
	float m_EnginePower = 5.f;

	float m_ElapsedTime = 0;
	float m_SmokeInterval = 1.f;
	float m_SmokeNextTime = m_SmokeInterval;
};
