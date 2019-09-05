#pragma once
#include <string>

template <typename T>
class ParticleDefinition
{
private:
	std::string m_name;
	T m_mass;
	T m_Px;
	T m_Py;
	T m_Pz;
	T m_E;

public:
	inline T const& getEnergy() { return m_E; }
	std::string const& getName(){ return m_name; }
	T const& getMass() { return m_mass; }
	void setMass(T const& mass) { m_mass = mass; }
	void setName(std::string const& name) { m_name = name; }
};