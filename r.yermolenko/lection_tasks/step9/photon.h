#pragma once
#include "I_ParticleDefinition.h"
#include "constants.h"
template <typename T>
class Photon : public IParticleDefinition<T>
{
private:
	T m_spin;
	std::string m_family;
public:
	Photon(double P) :
		 m_spin(1.0), m_family("bozon")
	{
		this->m_name = "photon";
		this->m_mass = 0.;
		this->m_P = P;
	}
	~Photon() {}
	T getE()
	{
		return this->m_P * CONST::с;
	}
};