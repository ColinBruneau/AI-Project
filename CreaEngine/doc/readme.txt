/***************************************************/
/* Nom:	CreaEngine
/* Description: CreaEngine est un moteur d�velopp� � Creajeux
/* dans le cadre des cours "Engine" (C++, Graphique, Physique, IA)
/* Il est bas� sur SFML mais en plugin de sorte de pouvoir 
/* plus tard remplacer SFML par n'importe quel autre renderer
/* (DirectX9, Vulkan, etc.)
/* 
/* Auteur: BRUNEAU Colin
/***************************************************/

01/2016:	D�velopement du framework sur base SFML (TD Design Pattern, Visual Studio 2013).
09/2016:	Portage sur Visual Studio 2015
		Int�gration des plugins CreaSFML et CreaDirectX
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
		S�lection
03/2017 BehaviorTree
09/2017 VS2017
10/2017 OpenGL3
11/2017 Script integration (UserController and CharacterController as scripts)
04/2018 integration of modifications from 2017-2018 (Shape)
04/2019 integration of modifications from 2018-2019 (DXShape)

Doing:
- OpenGL3 integration (following https://learnopengl.com/)
*** 07/2020 Ajout de GL3Shader et GL3Material
mais il faut d�commenter les fonctions dans Material::use qui n�cessite une adaptation de Transform pour utiliser des Mat4 (LibMath?)
J'ai int�gr� LibMath mais �a oblige � l'int�grer dans chaque solution et vu que le moteur est 2D only pour le moment,
il vaut mieux simplement int�grer la position et l'orientation du transform dans un glm::mat4 sans passer par la LibMath
*** 11/2020 
Ajout de la fonction clone pour h�ritage Material. Il faudrait faire h�riter aussi les autres assets.
Le SpriteRenderer poss�de un Material non utilis�. Pourtant c'est lui qui devrait le poss�der mais comme en SFML il n'y en a pas, impossible de le mettre dans SpriteRenderer.

To do: 
- MEMORY MANAGER!!!
- regrouper les interfaces dans IGraphics.h et Math.h?
- syst�me de prefab
- ajouter offset (ou hotspot) sur un objet
- dans le CharacterController, ajouter une r�ponse aux collisions autre que bloquer le perso
- bug: la souris ne retourne pas 1280*800 au coin en bas � droite 
- Selection: pour le moment la s�lection se fait sur tous les sprites dans SceneGame. Il faudrait faire un syst�me g�n�rique de s�lection (component?)
  qui pourrait �tre configur� dans le Gamecode (ex: texture, entit� s�lectionnable).
- Steering: faire la classe Vehicle
- SelectEntities: should not be able to select root!
- .anm: change -W to Flip parameter
- table d'action: v�rifier chargement de la table, bug si ordre des anims diff�rent que ordre de l'EnumAction...

Removed:
- DataManager: regrouper les diff�rentes map dans 1 map de maps? ex: au lieu de GetTexture() GetData("Texture", ...)
- EntityManager: comme pour DataManager...
Implique que tous les assets d�rivent d'un m�me type (Asset?) or ce n'est pas le cas. (A REVERIFIER parceque �a fonctionne ds les TDs)