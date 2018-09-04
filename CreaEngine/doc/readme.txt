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
04/2018 integration of modifications from classes (Shapes,

Doing:
- OpenGL3 integration (following http://www.opengl-tutorial.org)
- Shape et RectangleShape dans SFML (� faire aussi dans DirectX)
- Destructeurs des objets de SFML (� faire aussi dans DirectX)

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
- DXShape not implemented
- merge sfmlLine with SFMLLineShape

Removed:
- DataManager: regrouper les diff�rentes map dans 1 map de maps? ex: au lieu de GetTexture() GetData("Texture", ...)
- EntityManager: comme pour DataManager...
Implique que tous les assets d�rivent d'un m�me type (Asset?) or ce n'est pas le cas.