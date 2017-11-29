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
#include <Windowsx.h>

#include "CreaImport.h"

// TODO: faites référence ici aux en-têtes supplémentaires nécessaires au programme

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
