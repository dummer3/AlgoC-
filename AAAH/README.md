# Classes

- La Classe `Map` est un simple tableau 2D d'entier, elle permet juste de plus rapidement afficher, ou modifier certains éléments
- La Classe `f_stack` et `p_stack` sont respectivement une pile et une file de priorité, cependant elles possèdent
  toutes les deux une fonction `find` pour rechercher, et rechercher/supprimer si existe mieux
- `Content` est une structure qui regroupe toutes les données nécessaires pour faire fonctionner l'algorithme A, mais
  aussi retracer le chemin.


# Comment exécuter

Créer une carte (cf *test.txt*, 0 = case vide, 1 = case mur)
ET OUI NOIR = LIBRE ET BLANC = MUR

Modifier dans AAAH.cpp, le main:

- nom du fichier
- coordonnée start et end
  
ATTENTION, ne pas oublier qu'il y a des murs pour rendre la carte plus lisible, bien les prendre en compte (décalage de 1 horizontalement et verticalement ) 

*Si j'ai pas la flemme, on pourra les passer en arguments de la commande*

Il existe aussi tout en haut du fichier un define DEBUG.

1 pour avoir la trace de l'algo, 0 pour avoir seulement le résultat.

Puis:
g++ -Wall -Wextra  -o exec Map.cpp AAAH.cpp

./exec

La magie opère !!!



