#include "ParticlesGenerator.h"


ParticlesGenerator::ParticlesGenerator(uint32_t maxParticles)
	: m_PoolIndex(maxParticles - 1)
{
	m_ParticlePool.resize(maxParticles);
}

void ParticlesGenerator::OnUpdate(Time frameTime)
{
	float seconds = frameTime.AsSeconds();

	for (auto& particle : m_ParticlePool)
	{
		if (!particle.Active)
			continue;
		
		if (particle.LifeRemaning <= 0.f)
		{
			particle.Active = false;
			continue;
		}

		particle.LifeRemaning -= seconds;

		particle.Position += particle.Velocity * seconds;
		particle.Rotation += 0.01f * seconds;

		RenderParticle(particle);
	}
}

void ParticlesGenerator::RenderParticle(const Particle& particle)
{
	float life = particle.LifeRemaning / particle.LifeTime;

	Color color = Lerp(particle.ColorEnd, particle.ColorBegin, life);
	float size = Lerp(particle.SizeEnd, particle.SizeBegin, life);

	Renderer2D::DrawRotatedQuad(particle.Position, { size, size }, particle.Rotation, color);
}

void ParticlesGenerator::Emit(const ParticleDesc& desc)
{
	Particle& particle = m_ParticlePool[m_PoolIndex];
	particle.Active = true;

	particle.ColorBegin = desc.ColorBegin;
	particle.ColorEnd = desc.ColorEnd;

	particle.SizeBegin = desc.SizeBegin + desc.SizeVariation * (Random::Float() - 0.5f);
	particle.SizeEnd = desc.SizeEnd;	

	particle.Position = desc.Position;
	particle.Rotation = Random::Float() * 2 * M_PIf;

	particle.Velocity = desc.Velocity;
	particle.Velocity.x += desc.VelocityVariation.x * (Random::Float() - 0.5f);
	particle.Velocity.y += desc.VelocityVariation.y * (Random::Float() - 0.5f);

	particle.LifeTime = desc.LifeTime;
	particle.LifeRemaning = desc.LifeTime;

	m_PoolIndex = --m_PoolIndex % m_ParticlePool.size();
}
