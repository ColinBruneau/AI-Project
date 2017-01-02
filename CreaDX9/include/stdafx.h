// stdafx.h�: fichier Include pour les fichiers Include syst�me standard,
// ou les fichiers Include sp�cifiques aux projets qui sont utilis�s fr�quemment,
// et sont rarement modifi�s
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

// TODO: faites r�f�rence ici aux en-t�tes suppl�mentaires n�cessaires au programme

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