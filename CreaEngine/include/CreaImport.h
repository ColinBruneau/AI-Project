#ifndef _CREAIMPORT_H
#define _CREAIMPORT_H

namespace crea
{

#   ifdef CREAENGINE_EXPORTS
#       define CREAENGINE_API __declspec(dllexport)
#   else
#       define CREAENGINE_API __declspec(dllimport)
#   endif

} // namespace LibMath


#include "Core\GameManager.h"
#include "Core\SceneManager.h"
#include "Core\DataManager.h"
#include "Core\EntityManager.h"
#include "Graphics\SpriteRenderer.h"
#include "Graphics\TextRenderer.h"
#include "Graphics\MapRenderer.h"
#include "Graphics\AnimatedSpriteRenderer.h"
#include "Data\Entity.h"
#include "Data\AnimatedSprite.h"
#include "Data\Animation.h"
#include "Data\Map.h"
#include "AI\ActionTable.h"

#   endif // _CREAIMPORT_H