/***************************************************/
/* Nom:	Cells
/* Description: Cells est une application de test
/* du module d'IA développé à Creajeux
/* Il est basé sur le moteur CreaEngine qui utilise
/* le framework SFML.
/* Auteur: BRUNEAU Colin
/***************************************************/
#include "stdafx.h"
#include "Core\GameManager.h"
#include "Core\SceneManager.h"
#include "Scene\SceneSteering.h"
#include "Scene\ScenePlanning.h"

using namespace crea;

int _tmain(int argc, _TCHAR* argv[])
{
	GameManager* pGM = GameManager::getSingleton();

	pGM->setRendererType(Renderer_DX9);
	//pGM->setRendererType(Renderer_SFML);

	pGM->setWindowRect(IntRect(0, 0, 1152, 896));

	pGM->setScene(new ScenePlanning());

	pGM->init();

	pGM->update();

	pGM->quit();

	return 0;
}

