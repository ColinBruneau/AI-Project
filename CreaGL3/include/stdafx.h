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

// Constants
#define ONEOVER255 0.00392156862745f
#include <algorithm>

// Windows
//#include <Windows.h>
//#include <Windowsx.h> 


#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

// GLAD / GLFW
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// JSON
#include "json.h"

// stb_image
#include <stb_image.h>

// assimp
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

// glm
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// FreeType
#include "ft2build.h"
#include "freetype/freetype.h"

#include "CreaImport.h"

#define SafeDelete(pObject) if(pObject != NULL) {delete pObject; pObject=NULL;}

#include "Graphics\GL3Facade.h"
#include "Graphics\GL3Font.h"
#include "Graphics\GL3Texture.h"
#include "Graphics\GL3Color.h"
#include "Graphics\GL3Text.h"
#include "Graphics\GL3Sprite.h"
#include "Graphics\GL3Shape.h"
#include "Graphics\GL3Shader.h"
#include "Graphics\GL3Material.h"
