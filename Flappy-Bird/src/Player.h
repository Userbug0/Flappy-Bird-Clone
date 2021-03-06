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
	float GetRotation() const { return m_Rotation; }
	uint32_t GetScore() const { return uint32_t((m_Position.x + 10.f) / 10.f); }

private:
	Ref<Texture2D> m_Rocket;

	ParticlesGenerator m_ParticleSystem;
	ParticleDesc m_EngineParticle;
	ParticleDesc m_SmokeParticle;

	Vector2 m_Position = { -10.f, 0 };
	Vector2 m_Velocity = { 4.f, 0 };
	float m_Rotation = -90.f;

	float m_Gravity = 15.f;
	float m_EnginePower = 30.f;

	float m_ElapsedTime = 0;
	float m_SmokeInterval = 0.4f;
	float m_SmokeNextTime = m_SmokeInterval;
};
