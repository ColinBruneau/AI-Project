/***************************************************/
/* Nom:	Cells
/* Description: Cells est une application de test
/* du module d'IA d�velopp� � Creajeux
/* Il est bas� sur le moteur CreaEngine qui utilise
/* le framework SFML.
/* Auteur: BRUNEAU Colin
/***************************************************/
#include "stdafx.h"
#include "Core\GameManager.h"
#include "Core\SceneManager.h"
#include "Game\StateGame.h"

using namespace crea;

int _tmain(int argc, _TCHAR* argv[])
{
	GameManager* pGM = GameManager::getSingleton();

	pGM->init();

	pGM->setState(new StateGame());

	pGM->update();

	pGM->quit();

	return 0;
}
