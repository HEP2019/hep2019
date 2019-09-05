#pragma once
#include <string>
class ParticleDefinition
{
private:
	std::string m_name;
	float m_mass;
	float m_Px;
	float m_Py;
	float m_Pz;
	float m_E;
public:
	float const& getEnergy();
	std::string const& getName(){ return m_name; }
	float const& getMass() { return m_mass; }
	void setMass(float const& mass);
	void setName(std::string const& name);
};