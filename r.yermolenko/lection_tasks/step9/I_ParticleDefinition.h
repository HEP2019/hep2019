#pragma once
#include <string>
#include <vector>

template <typename T>
class IParticleDefinition
{
protected:
	std::string m_name;
	T m_mass;
	T m_P;
	T m_E;

public:
	virtual std::string getName() { return m_name; }
	virtual ~IParticleDefinition(){};
	
	virtual T getE() = 0;
};