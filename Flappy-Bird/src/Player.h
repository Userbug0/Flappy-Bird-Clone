#pragma once

#include <Athena.h>
#include "ParticlesGenerator.h"

using namespace Athena;


class Player
{
public:
	void Init();

	void OnUpdate(Time frameTime);
	void OnRender();

private:
	Ref<Texture2D> m_Rocket;

	ParticlesGenerator m_Generator;
	ParticleDesc m_EngineParticle;
	ParticleDesc m_SmokeParticle;

	Vector2 m_Position;
	Vector2 m_Velocity;
	float rotation;
};
