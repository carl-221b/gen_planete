# **Génération procédurale de planètes sphériques - Groupe 2**

## Build 
Commandes à faire dans le dossier src :
```
$ mkdir build
$ cd build
$ cmake ../
$ make -j6 
$ ./gen_planet
```
Une fenêtre openGL s'ouvre alors avec la planète générée à partir d'un bruit aléatoire.

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
