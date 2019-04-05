#pragma once
#include <string>
#include <vector>

template <typename T>
class ParticleDefinition
{
protected:
	std::string m_name;
	T m_mass;
	std::vector<T> m_P;
	T m_E;

public:
	size_t const NUM_COMPONENT = 3;
	 ParticleDefinition():
		m_name(""), m_mass(static_cast<T>(0.f)), m_E(static_cast<T>(0.f))
	{
		m_P.resize(NUM_COMPONENT, static_cast<T>(0.f));
	}
	ParticleDefinition(std::string name, T mass, T E) :
		m_name(name), m_mass(mass), m_E(E)
	{
		m_P.resize(NUM_COMPONENT, static_cast<T>(0.f));
	}
	 ~ParticleDefinition()
	{
		m_P.clear();
		m_P.shrink_to_fit();
	}
	inline T const& getEnergy() { return m_E; }
	std::string const& getName(){ return m_name; }
	T const& getMass() { return m_mass; }
	void setMass(T const& mass) { m_mass = mass; }
	void setName(std::string const& name) { m_name = name; }
};