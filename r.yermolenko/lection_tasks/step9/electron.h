#pragma once
#include "I_ParticleDefinition.h"
#include "constants.h"
template <typename T>
class Electron : public IParticleDefinition<T>
{
private:
	T m_electric_charge;
	T m_spin;
	std::string m_family;
public:
	Electron(double P) :
		m_electric_charge(-1.), m_spin (0.5), m_family("lepton") 
	    {
       	 this->m_name = "electron";
		 this->m_mass = 0.511;
		 this->m_P = P;
		}
	~Electron() {}
	T getE()
	{
		return sqrt(this->m_P*this->m_P * CONST::с2 + this->m_mass * this->m_mass * CONST::с2);
	}
};