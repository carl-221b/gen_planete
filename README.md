# **Génération procédurale de planètes sphériques - Groupe 2**

## Build 
Commandes à faire :
```
mkdir build
cd build
cmake ../src
make
```

## Lancer le générateur
Commandes à faire dans le dossier build :
```
./gen_planet [options] [config_file_path]
```
Mettez pour *config_file_path* le chemin vers le fichier de configuration contenant les paramètres de génération.

Une fenêtre openGL s'ouvre alors avec la planète générée à partir d'un bruit aléatoire.

Exemple :
```
./gen_planet ../src/data/generators/simple.xml
```

Pour plus d'informations, utilisez la commande *-h* pour voire l'aide complète.

## Modifier les paramètres
la construction et les différentes options pour le fichier de configuration du générateur est de la forme :

```
<params>
    <!-- Basic shape -->
    <shape name=.../>
    <shape_params>
        <option1 value=.../>
        <option2 value=.../>
        ...
    </shape_params>
 
    <!-- Editor -->
    <editor name=... />
    <editor_params>
        <option1 value=.../>
        <option2 value=.../>
    </editor_params>
</params>
```

Un exemple minimaliste est le suivant :
```
<?xml version="1.0" encoding="UTF-8"?>
<params>

   <!-- Basic shape -->
   <basic_shape name="icosphere"/>

   <shape_params>
       <nb_subdivision value="8"/>
   </shape_params>

   <!-- Editor -->
   <editor name="noisy_height" />

   <editor_params>
       <maximum_displacement_ratio value="0.1"/>
       <frequence value="5"/>
   </editor_params>

</params>
```

Pour un exemple complet des paramètres disponibles pour un éditeur, regardez le dossier src/data/generators qui contient un fichier de configuration complet par éditeur avec des explications par paramêtre.

## Interaction fenêtre openGL 
 - Clic and drag : Rotation de la planète
 - Molette de la souris : zoom et de-zoom
 - Touche ' Z ' : Mode " fil de fer " pour afficher le maillage

 //TO COMPLETE
 
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
