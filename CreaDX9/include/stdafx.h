// stdafx.h : fichier Include pour les fichiers Include système standard,
// ou les fichiers Include spécifiques aux projets qui sont utilisés fréquemment,
// et sont rarement modifiés
//

#pragma once

#include <stdio.h>
#include <tchar.h>

#include <cassert>
#include <iostream>
using namespace std;

#pragma warning( disable: 4251 )

// Windows
#include <Windows.h>

#include "CreaImport.h"

// TODO: faites référence ici aux en-têtes supplémentaires nécessaires au programme

#include <d3d9.h>
#include <d3dx9.h>

#define SafeRelease(pInterface) if(pInterface != NULL) {pInterface->Release(); pInterface=NULL;}
#define SafeDelete(pObject) if(pObject != NULL) {delete pObject; pObject=NULL;}

#include "Graphics\DX9Facade.h"
#include "Graphics\DX9Font.h"
#include "Graphics\DX9Texture.h"
#include "Graphics\DX9Color.h"
#include "Graphics\DX9Text.h"
#include "Graphics\DX9Sprite.h"