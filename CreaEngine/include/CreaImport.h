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
#include "Core\TimeManager.h"
#include "Graphics\SpriteRenderer.h"
#include "Graphics\TextRenderer.h"
#include "Graphics\MapRenderer.h"
#include "Graphics\Animator.h"
#include "Data\Entity.h"
#include "Data\Animation.h"
#include "Data\Map.h"
#include "AI\ActionTable.h"
#include "AI\Pathfinding\MapSearchManager.h"

#   endif // _CREAIMPORT_H