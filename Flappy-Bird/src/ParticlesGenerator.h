#pragma once

#include <Athena.h>

#include "ParticlesController.h"

using namespace Athena;


struct ParticleDesc
{
	Vector2 Position;
	Vector2 Velocity, VelocityVariation;
	Color ColorBegin, ColorEnd;
	float SizeBegin, SizeEnd, SizeVariation;
	float LifeTime = 0.5f;
};


class ParticlesGenerator
{
private:
	struct Particle;

public:
	ParticlesGenerator(uint32_t maxParticles);

	void OnUpdate(Time frameTime);
	void Emit(const ParticleDesc& desc);

private:
	void RenderParticle(const Particle& particle);

private:
	struct Particle
	{
		Vector2 Position;
		Vector2 Velocity;
		Color ColorBegin, ColorEnd;
		float Rotation;
		float SizeBegin, SizeEnd;

		float LifeTime, LifeRemaning;

		bool Active = false;
	};

	std::vector<Particle> m_ParticlePool;
	uint32_t m_PoolIndex;
};
