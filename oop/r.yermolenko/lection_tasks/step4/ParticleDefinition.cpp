#include "ParticleDefinition.h"

inline float const& ParticleDefinition::getEnergy()
{
	return m_E;
}

void ParticleDefinition::setMass(float const& mass)
{
	m_mass = mass;
}
void ParticleDefinition::setName(std::string const& name)
{
	m_name = name;
}