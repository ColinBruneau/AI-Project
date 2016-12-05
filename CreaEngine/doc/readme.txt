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

To do: 
- regrouper les interfaces dans IGraphics.h et ICore.h?
- DataManager: regrouper les diff�rentes map dans 1 map de maps? ex: au lieu de GetTexture() GetData("Texture", ...)
- EntityManager: comme pour DataManager...
- lien tiled - animation
- Collider g�r� dans DataManager? (.col)
- loadFromFileJSON pour Peon.cc, Peon.uc

