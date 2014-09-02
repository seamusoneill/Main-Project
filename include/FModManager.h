/*! Header for Sound Manager*/
#pragma once
#pragma comment(lib,"fmodex_vc.lib")
#include "fmod.hpp"
#include <iostream>
class FModManager
{
public:
	static FMOD::System* System();
private:
	static FMOD::System *system;
};