#pragma once

#include <Athena.h>

#include "ParticlesController.h"

using namespace Athena;


class ParticlesGenerator
{
private:
	struct Particle;

public:
	ParticlesGenerator();

	void OnUpdate(Time frameTime);
	void OnEvent(Event& event);
	void Emit(const ParticleDesc& desc);

private:
	void GetEmitterPosition(float seconds);
	void RenderParticle(const Particle& particle);

	bool OnWindowResized(WindowResizedEvent& event);

private:
	struct Particle
	{
		Vector2 Position;
		Vector2 Velocity;
		Color ColorBegin, ColorEnd;
		float SizeBegin, SizeEnd;

		float LifeTime, LifeRemaning;

		bool Active = false;
	};

	std::vector<Particle> m_ParticlePool;
	uint32_t m_PoolIndex = 1000;

	Vector2 m_EmitterPosition;
	float m_ElapsedTime;
};
