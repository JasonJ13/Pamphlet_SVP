# Pamphlet_SVP

Création d'un jeu en C++ utilisant la bibliothèque SMLF pour le rendu

## Description 

Le jeu est inspiré de Paper please ( [page steam] (https://store.steampowered.com/app/239030/Papers_Please/)),
ainsi que de la pièce de théâtre Cyrano de Bergerac ( [pdf de la pièce] (https://www.theatre-classique.fr/pages/pdf/ROSTAND_CYRANO.pdf).

Dans ce jeu, vous incarnez un missionaire entre des tranchées responsable de la correction de poème.
Différents auteurs et autrices se doivent de passer vous voir avant d'envoyer leurs poèmes pour que vous les corrigez.
De nombreuses fautes peuvent être présentes dans le poème, et il faut être attentif pour ne pas envoyer d'oeuvre malformée.

## Ambitions

Le projet peut être divisé en deux parties distinctes :
- La création du rendu du jeu et des mécaniques fondamentales.
- La gestion des poèmes et de leur erreur.

Cette dichotomie nous à permit de nous répartir les tâches sur le projet.

## Structure du projet

### Structures fondamentales
Bien que j'aimerai que ce ne soit pas le cas, il y a de grandes chances que cette partie évolue au cours du temps, en plus des ajouts en progression du projet

Le projet est divisé en plusieurs fichiers représentant plusieurs classes, chacun avec leurs rôles :
- Class Game : instance du jeu contenant toute les informations et de nombreuses instances listées si dessous.
- Class GameObject : Objet dans le jeu avec une manipulation du joueur limité.
- Class InteractibleObject - Class héritante de GameObject : Object du jeu avec une manipulation du joueur forte.
- Class TextureGestionner : Permet la gestion des Textures et des Sprites.
- Class Animation : Permet de créer des animations sur des propriétés de GameObject.
(Si j'ai le courage, je rajouterais deux schémas par la suite : un diagrame de classe et un diagram de cas d'utilisation)



## Progressions

### Ce que j'ai accompli (structure fondamental)
- Implémentation des classes listées dans la partie Structure du projet.
- Affichage des premiers objets.
- Projet fonctionnel et sans bug (pour le moment).
- Système de prise d'un objet (retirer pour cause de bug).
- Création d'animation sur des propriétés élémentaires de GameObject (float, Vector2f et Angle).
- Gestion des textures basiques avec TextureGestionner.

### Ce que je vise dans un future proche (aujourd'hui & demain)
- Spécification des objets de bases.
- Complession du système d'animation pour faciliter la création et le lancement.
- Ré-implémentation du système de prise d'un objet (sans bug)
- Finir la semaine sans bug

### Ce qu'il faut que j'implémente
- Système d'animation plus fuite (renseigner sur les signaux)
- Différentes classes dérivées de GameObject & InteractibleObject (l'idée étant de les rendre abstraites)
- Base graphique du jeu sur l'aquelle je peux m'appuyer pour le rendu final.

### Ce que j'aimerai bien ajouter
- Animation non linéaire (sinusoïdal et quadratique)
- du fun



## Log du README
Modifier le 17/06 à 12:20 par JasonJ13
