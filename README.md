# **Génération procédurale de planètes sphériques - Groupe 2**

## Build 
Commandes à faire dans le dossier src :
```
$ mkdir build
$ cd build
$ cmake ../
$ make -j6 
```

## Lancer le générateur
Commandes à faire dans le dossier build :
```
$ ./gen_planet [options] [config_file_path]
```
Mettez pour *config_file_path* le chemin vers le fichier de configuration contenant les paramètres de génération.

Une fenêtre openGL s'ouvre alors avec la planète générée à partir d'un bruit aléatoire.

Exemple :
```
$ ./gen_planet ../src/data/generators/simple.xml
```

Pour plus d'informations, utilisez la commande *-h* pour voire l'aide complète.

## Modifier les paramètres
la construction et les différentes options pour le fichier de configuration du générateur est de la forme :

```
<params>
    <shape name=... option1=... option2=... />
    <editor name=... option1=... option2=... />
</params>
```

Un exemple minimaliste est le suivant :
```
<?xml version="1.0" encoding="UTF-8"?>
<params>
    <basic_shape name="icosphere" nb_subdivision="5"/>
    <editor name="noisy_height" />
</params>
```

On a du coup les différentes options de la forme basique ainsi que pour l'éditeur à la suite des uns des autres.

Actuellement on a comme option, pour les formes de base :
	* icosphere
	Un type sphère géodésique à partir d'un icosahèdre.
		-nb_subdivision le nombre de subdivision de l'icosahèdre de départ.

Pour les éditeurs :
	*noisy_height
	Utilise le bruit de perlin pour faire des altitudes et où on attribue une couleur en rapport.

## Interaction fenêtre openGL 
 - Clic and drag : Rotation de la planète
 - Molette de la souris : zoom et de-zoom
 - Touche ' Z ' : Mode " fil de fer " pour afficher le maillage
 
## Bibliothèques utilisés
### Mozilla Public License 2
 - Eigen :  
	 Facilite les calculs matriciels pour la géométrie. 
 - glbinding :  
	 Permet le lien entre les données en mémoire et opengl.
 - glfw : 
	 API utilisé pour la gestion de fenêtre.
 - ObjFormat :
 Utilisé pour le chargement de fichier obj pour les transformer en données.
 Copyright (C) 2007 Gael Guennebaud 

### GNU Library General Public License, Version 2
- surface_mesh :
Facilite la gestion de connectivité et connexité des vertices pour la subdivision
Copyright (C) 2013 by Graphics & Geometry Group, Bielefeld University
- libnoise :
Utilisé pour l'application des bruits sur la sphère afin de créer les reliefs.
