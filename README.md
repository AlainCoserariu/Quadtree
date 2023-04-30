# Projet Quadtree 2023
### Coserariu Alain

## Introduction

Le projet consiste à creer une application permettant de visualiser un quadtree divisant un nuage de point.  
L'application possède deux mode de distribution des points :  
* Distribution par clique de souris
* Distribution aléatoire

## Compilation

La commande suivante permet de générer le fichier executable. 
```
make
```

Il est possible de supprimer uniquement les fichiers objets non désirables via la commande 
```
make clean
```

Enfin il est possible de supprimer tous les fichiers objets ainsi que l'executable via la commande :
```
make mrproper
```


## Execution et utilisation

Une fois compilé, un executable du nom de quadtree sera généré. La section ci dessous est dédié au lancement et à l'utilisation du programme.

### Paramètres de lancement du programme
```
./quadtree [nombre de point] [distribution] [nombre de points maximal d'une feuille]
```

* Le nombre de point représente le nombre de points total qui sera généré.
* La distribution indique si les points son généré aléatoirement ou par clique de souris. (0 : génération aléatoire. 1 : génération par clique de souris).
* Le nombre de points maximal d'une feuille est assez expicite.

En cas de mauvaise saisie de paramètre le programme affichera une aide récapitulant les différentes contraintes.

### Manuel utilisateur

#### Génération aléatoire

Si l'utilisateur indique une génération aléatoire, le programme affiche directement une fenêtre comportant le découpage de la zone sous forme de carrés verts. Les points sont affiché en rouge.  
L'utilisateur peut alors quitter le programme en appuyant sur une touche du clavier ou une touche de la souris.

#### Distribution par clique de souris

Si l'utilisateur indique une distibution par clique de souris, le programme affiche une fenêtre vide. L'utilisateur peut alors utiliser le clique gauche de la souris pour placer un point à l'endroit pointé par la souris sur la fenêtre. Si l'utilisateur clique sur un point déjà placé, l'entré n'est pas prise en compte et il peut retenter de placer le point. Une fois le nombre de points indiqué en paramètre atteint, l'utilisateur peut quitter l'application en appuyant sur un bouton du clavier (la souris devient inutile, cela permet de ne pas quitter l'application par inadvertance).  
L'utilisateur peut quitter à tout moment l'application en appuyant sur une touche du clavier.

## Problèmes rencontrées
* La manière de générer des points aléatoire n'est pas du tout optimal. Pour un grand nombre de points l'application peut mettre un certain temps avant d'afficher la fenêtre. Cela est dû à la regénération aléatoire d'un point si il est situé sur un autre. Donc pour une grille presque entièrement remplis, trouver le prochain pixel libre peut être très long en plus de parcourir le tableau de point. Pour corriger le souci on aurai pu utiliser un dictionnaire qui associe à chaque pixel un nombre, et a chaque génération de nombre supprimer le pixel correspondant du dictionnaire et l'ajouter au tableau de points. Cependant ce problème n'est obvserbable que dans le cas d'une génération aléatoire,or dans un cas pratique on sait que les points ne seront pas confondu. Plus encore demander un trop grand nombre de points n'a pas de réel interêts ici vu que nous cherchons seulement à visualiser un quadtree. De plus ce problème ne vient pas de la structure de quadtree en elle même, donc on a décider qu'il était acceptable de laisser cette génération.  
Le temps d'attente devient perceptible à partir de 50 000 points. À partir de 100000 points (environ 40% de la fenêtre) le temps de chargement tourne autour des 10 secondes.

* Selon l'utilitaire valgrind 18 octets sont perdu. Cependant cette perte semble venir de l'initialisation de la bibliothèque SDL. L'utilitaire ne donnant pas plus d'information, nous n'avons pas pu corriger cette perte.
```
==12326== 18 bytes in 2 blocks are definitely lost in loss record 117 of 414
==12326==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==12326==    by 0x4CE060E: strdup (strdup.c:42)
==12326==    by 0x5426D9A: ??? (in /usr/lib/x86_64-linux-gnu/libX11.so.6.4.0)
==12326==    by 0x542C260: _XimEncodeICATTRIBUTE (in /usr/lib/x86_64-linux-gnu/libX11.so.6.4.0)
==12326==    by 0x541B099: _XimProtoCreateIC (in /usr/lib/x86_64-linux-gnu/libX11.so.6.4.0)
==12326==    by 0x540930A: XCreateIC (in /usr/lib/x86_64-linux-gnu/libX11.so.6.4.0)
==12326==    by 0x48B0B31: ??? (in /usr/lib/x86_64-linux-gnu/libSDL-1.2.so.0.11.4)
==12326==    by 0x48B18F4: ??? (in /usr/lib/x86_64-linux-gnu/libSDL-1.2.so.0.11.4)
==12326==    by 0x48A2BE8: SDL_VideoInit (in /usr/lib/x86_64-linux-gnu/libSDL-1.2.so.0.11.4)
==12326==    by 0x487AABB: SDL_InitSubSystem (in /usr/lib/x86_64-linux-gnu/libSDL-1.2.so.0.11.4)
==12326==    by 0x487AB88: SDL_Init (in /usr/lib/x86_64-linux-gnu/libSDL-1.2.so.0.11.4)
==12326==    by 0x4A2799D: initialise_sdl (in /usr/lib/libMLV.so.0.2.0)
```