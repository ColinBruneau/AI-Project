#ifndef _CREAIMPORT_H
#define _CREAIMPORT_H

namespace crea
{

#   ifdef CREAENGINE_EXPORTS
#       define CREAENGINE_API __declspec(dllexport)
#   else
#       define CREAENGINE_API __declspec(dllimport)
#   endif

} // namespace crea

#define INVALID_OBJECT_ID 0
typedef unsigned int objectID;
namespace crea
{

#define g_time TimeManager::getSingleton()
#define g_entitymanager EntityManager::getSingleton()
#define g_msgmanager MsgManager::getSingleton()
#define g_debuglog DebugLog::getSingleton()

}

#include "Tools\json\json.h"
#include "Core\Singleton.h"
#include "Core\GameManager.h"
#include "Core\SceneManager.h"
#include "Core\EntityManager.h"
#include "Core\Entity.h"
#include "Core\Scene.h"
#include "Core\Math.h"
#include "Core\Script.h"
#include "Core\ScriptFactory.h"
#include "Core\PhysicsManager.h"
#include "Core\MsgManager.h"
#include "Core\Msg.h"
#include "Data\Asset.h"
#include "Data\DataManager.h"
#include "Data\Node.h"
#include "Data\Map.h"
#include "Data\Animation.h"
#include "Graphics\Shader.h"
#include "Graphics\Color.h"
#include "Graphics\Material.h"
#include "Graphics\Font.h"
#include "Graphics\Text.h"
#include "Graphics\Texture.h"
#include "Graphics\Sprite.h"
#include "Graphics\Shape.h"
#include "Graphics\SpriteRenderer.h"
#include "Graphics\TextRenderer.h"
#include "Graphics\MapRenderer.h"
#include "Graphics\Animator.h"
#include "AI\Agent.h"
#include "AI\ActionTable.h"
#include "AI\StateMachine.h"
#include "AI\Pathfinding\MapSearchNode.h"
#include "AI\Pathfinding\MapSearch.h"
#include "AI\Pathfinding\MapSearchManager.h"
#include "AI\Pathfinding\ClusterSearchNode.h"
#include "AI\Pathfinding\ClusterSearch.h"
#include "AI\Pathfinding\ClusterSearchManager.h"
#include "AI\Pathfinding\Cluster.h"
#include "AI\Steering\Steering.h"
#include "AI\Steering\Vehicle.h"
#include "AI\Planning\Action.h"
#include "AI\Planning\Planner.h"
#include "AI\Planning\WorldState.h"
#include "AI\BehaviorTree\Behavior.h"
#include "AI\BehaviorTree\BehaviorTree.h"
#include "AI\BehaviorTree\Blackboard.h"
#include "Physics\Collider.h"

#   endif // _CREAIMPORT_H