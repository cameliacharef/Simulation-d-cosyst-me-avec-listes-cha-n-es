# Simulation d'écosystème avec listes chaînées

Ce projet consiste à écrire des fonctions de manipulation de listes chaînées et à les utiliser pour programmer une simulation simple d'écosystème.

### Description
Le modèle d'écosystème que vous allez programmer n'a pas l'intention d'être réaliste, mais il permet de se familiariser avec le concept d'équilibre, primordial dans un écosystème. Cet écosystème contiendra deux types d'entités virtuelles : des proies et des prédateurs, susceptibles de manger les proies. Notre écosystème est un monde discret (un tore, que nous afficherons comme un rectangle) contenant un certain nombre de cases, identifiées par leurs coordonnées (entières) x et y. Chaque proie (et chaque prédateur) est dans une case donnée et peut se déplacer. À un instant donné, une case peut contenir plusieurs proies et plusieurs prédateurs. Chaque case peut aussi contenir de l'herbe, la nourriture des proies.

La simulation de notre écosystème repose sur plusieurs structures de données et sur des fonctions que vous allez écrire dans la suite de cette séance. Les données utilisées pour la simulation sont une liste chaînée contenant les proies et une autre liste chaînée contenant les prédateurs, ainsi qu'un tableau statique à deux dimensions représentant le monde.

### Fonctionnalités
- **Manipulation de listes chaînées** : Implémentation de fonctions pour ajouter, supprimer et parcourir des éléments dans des listes chaînées.
- **Simulation d'écosystème** : Création d'un écosystème avec des proies, des prédateurs et de l'herbe.
- **Déplacement et interaction** : Les proies et les prédateurs peuvent se déplacer et interagir selon certaines règles.
