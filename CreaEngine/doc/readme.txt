/***************************************************/
/* Nom:	CreaEngine
/* Description: CreaEngine est un moteur développé à Creajeux
/* dans le cadre des cours "Engine" (C++, Graphique, Physique, IA)
/* Il est basé sur SFML mais en plugin de sorte de pouvoir 
/* plus tard remplacer SFML par n'importe quel autre renderer
/* (DirectX9, Vulkan, etc.)
/* 
/* Auteur: BRUNEAU Colin
/***************************************************/

01/2016:	Dévelopement du framework sur base SFML (TD Design Pattern, Visual Studio 2013).
09/2016:	Portage sur Visual Studio 2015
		Intégration des plugins CreaSFML et CreaDirectX
10/2016:	Refactoring de l'architecture
		Module Animation
		Chargement map (JSON)
11/2017 Chargement des animations (Action Table)
		Physics module (collision, friction)
		Movement module (CharacterControl et User Control)
		Agent module (Attributes)
12/2017 FSM
		Msg
01/2017 Steering and swarming
02/2017 Formation
		Sélection
03/2017 BehaviorTree
09/2017 VS2017
10/2017 OpenGL3
11/2017 Script integration (UserController and CharacterController as scripts)
04/2018 integration of modifications from 2017-2018 (Shape)
04/2019 integration of modifications from 2018-2019 (DXShape)

Doing:
- OpenGL3 integration (following https://learnopengl.com/)
*** 07/2020 Ajout de GL3Shader et GL3Material
mais il faut décommenter les fonctions dans Material::use qui nécessite une adaptation de Transform pour utiliser des Mat4 (LibMath?)
J'ai intégré LibMath mais ça oblige à l'intégrer dans chaque solution et vu que le moteur est 2D only pour le moment,
il vaut mieux simplement intégrer la position et l'orientation du transform dans un glm::mat4 sans passer par la LibMath
*** 11/2020 
Ajout de la fonction clone pour héritage Material. Il faudrait faire hériter aussi les autres assets.
Le SpriteRenderer possède un Material non utilisé. Pourtant c'est lui qui devrait le posséder mais comme en SFML il n'y en a pas, impossible de le mettre dans SpriteRenderer.

To do: 
- MEMORY MANAGER!!!
- regrouper les interfaces dans IGraphics.h et Math.h?
- système de prefab
- ajouter offset (ou hotspot) sur un objet
- dans le CharacterController, ajouter une réponse aux collisions autre que bloquer le perso
- bug: la souris ne retourne pas 1280*800 au coin en bas à droite 
- Selection: pour le moment la sélection se fait sur tous les sprites dans SceneGame. Il faudrait faire un système générique de sélection (component?)
  qui pourrait être configuré dans le Gamecode (ex: texture, entité sélectionnable).
- Steering: faire la classe Vehicle
- SelectEntities: should not be able to select root!
- .anm: change -W to Flip parameter
- table d'action: vérifier chargement de la table, bug si ordre des anims différent que ordre de l'EnumAction...

Removed:
- DataManager: regrouper les différentes map dans 1 map de maps? ex: au lieu de GetTexture() GetData("Texture", ...)
- EntityManager: comme pour DataManager...
Implique que tous les assets dérivent d'un même type (Asset?) or ce n'est pas le cas. (A REVERIFIER parceque ça fonctionne ds les TDs)