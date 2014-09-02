/*! Class for FMOD*/
#include "FModManager.h"

FMOD::System *FModManager::system=0;

FMOD::System* FModManager::System(){
	if(!system){
		FMOD_RESULT result;

		result = FMOD::System_Create(&system);
		if (result != FMOD_OK)
		{
			std::cout << "FMOD error! (%d) %s \n" <<result;
			exit(-1);
		}

		result = system->init(100, FMOD_INIT_NORMAL, 0);
		if(result != FMOD_OK)
		{
			std::cout << "FMOD error! (%d) %s\n" <<result;
			exit(-1);
		}
	}
	return system;
}