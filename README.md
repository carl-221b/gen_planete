# **Génération procédurale de planètes sphériques**

![](https://github.com/carl-221b/gen_planete/blob/master/docs/report/img/notre_planete.png "Planète normale")

Rendu de planète avec un bruit aléatoire. Lien vers le [rapport](https://tsiory-rakotoarisoa.emi.u-bordeaux.fr/Projet_PDP_2020_Jupiter.pdf).

Algorithme de [subdivision](https://www.microsoft.com/en-us/research/wp-content/uploads/2016/02/tr-2001-24.pdf) 

## Auteurs
- Sofian Antri
- Benjamin Darmet
- Tsiory Rakotoarisoa
- Rémi Barbosa
- Marc Cerutti

## Autres Résultats 

![](https://github.com/carl-221b/gen_planete/blob/master/docs/report/img/notre_planete_mars.png "Planète rouge")

Rendu de planète avec un bruit aléatoire et couleur différente (biome non terrestre)

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
Mettez pour *config_file_path* le chemin vers le fichier de configuration contenant les paramètres de génération. Si aucun fichier de configuration n'est fournit, la génération se fera à partir d'une Shape et d'un Editor crée (et modifiable) dans le ```main```.

Une fenêtre openGL s'ouvre alors avec la planète générée à partir d'un bruit aléatoire, et ses différents paramètres affichés.

Exemple :
```
./gen_planet -o ../planet_save ../src/data/generators/simple.xml
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

Pour un exemple complet des paramètres disponibles avec un éditeur particulier, regardez le dossier src/data/generators qui contient un fichier de configuration complet par éditeur avec une explications courte par paramètre. 

Pour des paramètres particulier sur les bruits, je vous invite à regarder la doc de la bibliothèque [libnoise](http://libnoise.sourceforge.net/).

## Interaction fenêtre openGL 
 - Clic and drag : Rotation de la planète.
 - Molette de la souris : zoom et de-zoom.
 - Touche ' W ' : Activer/Desactiver Mode " fil de fer " pour afficher le maillage
 - Touche ' L ' : Activer/Desactiver la rotation de lumière autour de la planète.
 - Touche ' R ' : Chargement des modifications appliqués au shader s'il y en a eu.
 - Touche ' S ' : Sauvegarde en obj (sans les couleurs) et off (avec les couleurs) le relief de la planète (sans la mer).
 - Touche ' Q ' ou ' Escape ' : Sortir du logiciel.
 
## Bibliothèques utilisés
### Mozilla Public License 2
 - Eigen :  
     Facilite les calculs matriciels pour la géométrie. 
 - glbinding :  
     Permet le lien entre les données en mémoire et opengl.
 - glfw : 
     API utilisé pour la gestion de fenêtre.

### GNU Library General Public License, Version 2
- surface_mesh :
Facilite la gestion de connectivité et connexité des vertices pour la subdivision
Copyright (C) 2013 by Graphics & Geometry Group, Bielefeld University
- libnoise :
Utilisé pour créer les reliefs à partir de bruits cohérents.

### MIT License
- pugyxml:
Permet la prise en charge de fichiers de configurations xml.

### Copyright 2008, Google Inc.
- googletest :
Permet de faccilité la mise en place de tests unitaires automatisés. 

### Credits 
- Simon Boyé
- Gael Guennebaud
