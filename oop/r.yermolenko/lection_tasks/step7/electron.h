#pragma once
#include "ParticleDefinition.h"
template <typename T>
class Electron : public ParticleDefinition<T>
{
private:
	T m_electric_charge;
	T m_spin;
	std::string m_family;
public:
	void setFamily(std::string const& family) { m_family = "lepton"; }
	Electron() :
		m_electric_charge(-1.), m_spin (0.5), m_family("lepton") 
	    {
       	 this->m_name = "electron";
		}
	~Electron() {
		m_spin = 0;
	}
	T getSpin() { return m_spin; }
	T getElectricCharge() { return m_electric_charge; }
	std::string getFamily() { return m_family; }
};