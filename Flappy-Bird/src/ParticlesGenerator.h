#pragma once

#include <Athena.h>


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
	ParticlesGenerator(uint32_t maxParticles = 1000);

	void OnUpdate(Time frameTime);
	void OnRender();

	void Emit(const ParticleDesc& desc);

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
