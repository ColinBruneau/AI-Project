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
#include <Windowsx.h>

#include "CreaImport.h"

// TODO: faites r�f�rence ici aux en-t�tes suppl�mentaires n�cessaires au programme

// Include GLEW. Always include it before gl.h and glfw.h, since it's a bit magic.
#include <GL/glew.h>
// Include GLFW
#include <GLFW/glfw3.h>
// Include GLM
#include <glm/glm.hpp>
using namespace glm;

#define SafeDelete(pObject) if(pObject != NULL) {delete pObject; pObject=NULL;}

#include "Graphics\GL3Facade.h"
#include "Graphics\GL3Font.h"
#include "Graphics\GL3Texture.h"
#include "Graphics\GL3Color.h"
#include "Graphics\GL3Text.h"
#include "Graphics\GL3Sprite.h"
