#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include <string.h>

#include "ecosys.h"
float p_ch_dir=0.3;
float p_reproduce_proie=0.25;
float p_reproduce_predateur=0.3;
int temps_repousse_herbe=-15;


/* PARTIE 1*/
/* Fourni: Part 1, exercice 4, question 2 */
Animal *creer_animal(int x, int y, float energie) {
  Animal *na = (Animal *)malloc(sizeof(Animal));
  assert(na);
  na->x = x;
  na->y = y;
  na->energie = energie;
  na->dir[0] = rand() % 3 - 1;
  na->dir[1] = rand() % 3 - 1;
  na->suivant = NULL;
  return na;
}


/* Fourni: Part 1, exercice 4, question 3 */
Animal *ajouter_en_tete_animal(Animal *liste, Animal *animal) {
  assert(animal);
  assert(!animal->suivant);
  animal->suivant = liste;
  return animal;
}

/* A faire. Part 1, exercice 6, question 2 */
void ajouter_animal(int x, int y,  float energie, Animal **liste_animal) {
  /*A Completer*/
  assert(x >= 0 && x < SIZE_X);
	assert(y >= 0 && y < SIZE_Y);
  Animal *nouvanimal = creer_animal(x,y,energie);
	*liste_animal = ajouter_en_tete_animal(*liste_animal, nouvanimal);
}

/* A Faire. Part 1, exercice 5, question 5 */
void enlever_animal(Animal **liste, Animal *animal) {
  /*A Completer*/
  // Vérifier si la liste est vide
    if (*liste == NULL) {
        return;
    }
    // l'animal est en tête de liste
    if (*liste == animal) {
        *liste = animal->suivant;
        free(animal);
        return;
    }
  // Parcourir la liste pour trouver l'élément précédant celui à retirer
    Animal *precedent = *liste;
    while (precedent->suivant != NULL && precedent->suivant != animal) {
        precedent = precedent->suivant;
    }

    // Vérifier si l'élément à retirer a été trouvé
    if (precedent->suivant != NULL) {
        precedent->suivant = animal->suivant;
        free(animal);
    }

}

/* A Faire. Part 1, exercice 6, question 7 */
Animal* liberer_liste_animaux(Animal *liste) {
   /*A Completer*/
  Animal *tmp ;
  while(liste){
    tmp=liste->suivant;
    free(liste);
    liste=tmp;
  }
  return NULL;
}

/* Fourni: part 1, exercice 4, question 4 */
unsigned int compte_animal_rec(Animal *la) {
  if (!la) return 0;
  return 1 + compte_animal_rec(la->suivant);
}

/* Fourni: part 1, exercice 4, question 4 */
unsigned int compte_animal_it(Animal *la) { 
  int cpt=0;
  while (la) {
    ++cpt;
    la=la->suivant;
  }
  return cpt;
}



/* Part 1. Exercice 5, question 1, ATTENTION, ce code est susceptible de contenir des erreurs... */
void afficher_ecosys(Animal *liste_proie, Animal *liste_predateur) {
  unsigned int i, j;
  char ecosys[SIZE_X][SIZE_Y];
  Animal *pa=NULL;

  /* on initialise le tableau */
  for (i = 0; i < SIZE_X; ++i) {
    for (j = 0; j <SIZE_Y ; ++j) {
      ecosys[i][j]=' ';
    }
  }

  /* on ajoute les proies */
  pa = liste_proie;
  while (pa) {
    ecosys[pa->x][pa->y] = '*';
    pa=pa->suivant;
  }

  /* on ajoute les predateurs */
  pa = liste_predateur;
  while (pa) {
      if ((ecosys[pa->x][pa->y] == '@') || (ecosys[pa->x][pa->y] == '*')) { /* proies aussi present */
        ecosys[pa->x][pa->y] = '@';
      } else {
        ecosys[pa->x][pa->y] = 'O';
      }
    pa = pa->suivant;
  }

  /* on affiche le tableau */
  printf("+");
  for (j = 0; j < SIZE_Y; ++j) {
    printf("-");
  }  
  printf("+\n");
  for (i = 0; i < SIZE_X; ++i) {
    printf("|");
    for (j = 0; j < SIZE_Y; ++j) {
      putchar(ecosys[i][j]);
    }
    printf("|\n");
  }
  printf("+");
  for (j = 0; j<SIZE_Y; ++j) {
    printf("-");
  }
  printf("+\n");
  int nbproie=compte_animal_it(liste_proie);
  int nbpred=compte_animal_it(liste_predateur);
  
  printf("Nb proies : %5d\tNb predateurs : %5d\n", nbproie, nbpred);

}


void clear_screen() {
  printf("\x1b[2J\x1b[1;1H");  /* code ANSI X3.4 pour effacer l'ecran */
}

/* PARTIE 2*/

/* Part 2. Exercice 4, question 1 */
void bouger_animaux(Animal *la) {
    /*A Completer*/
    Animal *a = la;
  
	  while(a){
      if (rand()/(float)RAND_MAX < p_ch_dir){ //changement de direction avec une probabilité p_ch_dir
        a->dir[0] = rand()%3 - 1; //-1 ,0 ,1 
        a->dir[1] = rand()%3 - 1;
      }
      // déplacer l'animal selon sa direction
      // les coordonnées de l'animal sont bien dans les limites de taille du tableau
      a->x = (a->x + a->dir[0] + SIZE_X) % SIZE_X;  //% SIZE_X assure toricité
      a->y = (a->y + a->dir[1] + SIZE_Y) % SIZE_Y;
      a = a->suivant;
	}
}



/* Part 2. Exercice 4, question 3 */
void reproduce(Animal **liste_animal, float p_reproduce) {
   /*A Completer*/
   Animal *a = liste_animal ? *liste_animal :NULL;
   while(a){
    if((float)rand()/RAND_MAX < p_reproduce){
      ajouter_animal(a->x, a->y, a->energie/2, liste_animal);
      a->energie /=2;
    }
    a = a->suivant;
   }
}


/* Part 2. Exercice 6, question 1 */
void rafraichir_proies(Animal **liste_proie, int monde[SIZE_X][SIZE_Y]) {
    /*A Completer*/
    bouger_animaux(*liste_proie);
    Animal *temp = liste_proie ? *liste_proie : NULL;

  while(temp){
    temp->energie--;//baisser leur energie de 1,
    if (temp->energie < 0){//supprimer les proies dont l’energie est inf ´ erieure ´ a 0;
      enlever_animal(liste_proie, temp);
    }

    else if (monde[temp->x][temp->y] > 0){ //position avec valeure positive : il ya de lenergie
      temp->energie += monde[temp->x][temp->y];//quantité d'herbe sur la case où se trouve l'animal.
      monde[temp->x][temp->y] = temps_repousse_herbe;//gagne en énergie en fonction de la quantité d'herbe présente sur cette case
    }

    temp = temp->suivant;
  }

  reproduce(liste_proie, p_reproduce_proie);
}




/* Part 2. Exercice 7, question 1 */
Animal *animal_en_XY(Animal *l, int x, int y) {
    /*A Completer*/
  while(l){
    if((l->x == x)&&(l->y == y)){ return l;}
    l = l->suivant;
  }
  return NULL;
} 


/* Part 2. Exercice 7, question 2 */
void rafraichir_predateurs(Animal **liste_predateur, Animal **liste_proie) {
   /*A Completer*/
  bouger_animaux(*liste_predateur);
  Animal *temp = liste_predateur ? *liste_predateur : NULL;

  while(temp){
    temp->energie--;

    if (temp->energie < 0){
      enlever_animal(liste_predateur, temp);
    }
    else {
      Animal *proieVictime = animal_en_XY(*liste_proie, temp->x, temp->y);
      if (proieVictime != NULL){
        temp->energie += proieVictime->energie;
        enlever_animal(liste_proie, proieVictime);
      }
    }

    temp = temp->suivant;
  }

  reproduce(liste_predateur, p_reproduce_predateur);
}


/* Part 2. Exercice 5, question 2 */
void rafraichir_monde(int monde[SIZE_X][SIZE_Y]){
   /*A Completer*/
  int i,j;
  for(i = 0; i<SIZE_X; i++){
    for(j = 0; j<SIZE_Y; j++){
      monde[i][j] ++;
    }
  }

}


void ecrire_ecosys(const char *nom_fichier, Animal *liste_proie, Animal *liste_predateur){
	FILE *f = fopen(nom_fichier, "w");
	if (f == NULL){
		printf("Erreur lors de l'ouverture.");
		exit(1);
	}
	fprintf(f, "<proie>\n");
	Animal *tmp = liste_proie;
	while(tmp){
		fprintf(f, "x=%d y=%d dir=[%d,%d] e=%f\n", tmp->x, tmp ->y, tmp->dir[0], tmp->dir[1], tmp->energie);
		tmp = tmp->suivant;
	}
	fprintf(f,"</proie>\n");

	fprintf(f,"<predateur>\n");
	tmp = liste_predateur;
	while(tmp){
		fprintf(f, "x=%d y=%d dir=[%d,%d] e=%f\n", tmp->x, tmp ->y, tmp->dir[0], tmp->dir[1], tmp->energie);
		tmp = tmp->suivant;
	}
	fprintf(f, "</predateur>\n");
	
	fclose(f);
}

void lire_ecosys(const char *nom_fichier, Animal **liste_proie, Animal **liste_predateur){
	FILE *f = fopen(nom_fichier, "r");
	if (f == NULL){
		printf("Erreur lors de l'ouverture.");
		exit(1);
	}

	char buffer[256]; //max 256 caractères par ligne, on vise plus haut.
	fgets(buffer, 256, f);
	assert(strncmp(buffer, "<proie>", 7) == 0);

	int x_lu, y_lu, dir0, dir1; float e_lu;
	fgets(buffer, 256, f);
	while(strncmp(buffer, "</proie>", 8) != 0){
		sscanf(buffer, "x=%d y=%d dir=[%d,%d] e=%f\n", &x_lu, &y_lu, &dir0, &dir1, &e_lu);
		Animal *a = creer_animal(x_lu, y_lu, e_lu);
		a->dir[0] = dir0; 
		a->dir[1] = dir1;
		a->suivant = *liste_proie;
		*liste_proie = a;
		fgets(buffer, 256, f);
	}

	fgets(buffer, 256, f);
	assert(strncmp(buffer, "<predateur>", 11) == 0);

	fgets(buffer, 256, f);
	while(strncmp(buffer, "</predateur>", 12) != 0){
		sscanf(buffer, "x=%d y=%d dir=[%d,%d] e=%f\n", &x_lu, &y_lu, &dir0, &dir1, &e_lu);
		Animal *a = creer_animal(x_lu, y_lu, e_lu);
		a->dir[0] = dir0; 
		a->dir[1] = dir1;
		a->suivant = *liste_predateur;
		*liste_predateur = a;
		fgets(buffer, 256, f);
	}

	fclose(f);
}
