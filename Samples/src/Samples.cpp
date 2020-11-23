/***************************************************/
/* Nom:	Samples
/* Description: Samples est une application de test
/* du CreaEngine
/* Il est basé sur le moteur CreaEngine qui utilise
/* le framework SFML.
/* Auteur: BRUNEAU Colin
/***************************************************/
#include "stdafx.h"
#include "Core\GameManager.h"
#include "Core\SceneManager.h"
#include "Scene\SceneMenu.h"

using namespace crea;

int _tmain(int argc, _TCHAR* argv[])
{
	GameManager* pGM = GameManager::getSingleton();


	//pGM->setRendererType(Renderer_DX9);
	pGM->setRendererType(Renderer_SFML);
	//pGM->setRendererType(Renderer_GL3);

	// todo: window do not have the size updated because the window is created first) but can't do it before because renderer not created...
	//pGM->setWindowRect(IntRect(0, 0, 1152, 896));

	pGM->setScene(new SceneMenu());

	pGM->init();

	pGM->update();

	pGM->quit();

	return 0;
}

