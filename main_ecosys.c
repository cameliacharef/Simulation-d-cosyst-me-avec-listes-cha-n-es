//CHAREF CAMELIA 21202057
//BEN MIMOUN SARAH 28713241
#include <assert.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <strings.h>
#include "ecosys.h"

#define NB_PROIES 50 
#define NB_PREDATEURS 20
#define T_WAIT 40000
#define MAX_ITER 500
#define ENERGIEproie 20
#define ENERGIEpredateur 120


/* Parametres globaux de l'ecosysteme (externes dans le ecosys.h)*/
//jouer avec les parametres

int main(void) {
 
  /* A completer. Part 2:
   * exercice 4, questions 2 et 4
    
   * exercice 6, question 2
   * exercice 7, question 3
   * exercice 8, question 1
   */

    //Exercice 4 Q1
  srand(time(NULL));
  Animal *a = creer_animal(19, 49, 10.); //variable de test
  a->dir[0] = 1;
  a->dir[1] = 1;
  a->suivant = NULL;
  printf("Test deplacement\n");
  //On affiche du deplacement
  for(int i = 0; i<10; i++){
    bouger_animaux(&*a);
    printf("direction : (%d,%d)\n", a->dir[0], a->dir[1]);
    printf("X : %d, Y : %d\n", a->x, a->y);
  }

  //Exercice 4 Q2
  Animal *b = creer_animal(0, 0, 10.);
  printf("Test reproduce\n");
  for(int j = 0; j<4; j++){
    reproduce(&b, 1.);
    printf("Nb d'animaux : %d\n", compte_animal_it(b));
  }

  a = liberer_liste_animaux(a);
  b = liberer_liste_animaux(b);

  printf("Exercice 5 Question 2 - Test rafraichir\n");
  Animal *liste_proie = NULL;
  Animal *liste_predateur = NULL;

  FILE *fichier = fopen("Evol_Pop.txt", "w"); // Ouvrir le fichier pour écriture

    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }
  fprintf(fichier, "gen proies predateurs \n");


  int i,j;
  for(i = 0; i<NB_PROIES; i++){
    ajouter_animal(rand()%SIZE_X,rand()%SIZE_Y,(float)(rand()*1.0)/(RAND_MAX*1.0) * ENERGIEproie,&liste_proie);//energie 1+rand()%99
  }

  for(i = 0; i<NB_PREDATEURS; i++){
    ajouter_animal(rand()%SIZE_X,rand()%SIZE_Y,(float)(rand()*1.0)/(RAND_MAX*1.0) * ENERGIEpredateur,&liste_predateur);
  }
  afficher_ecosys(liste_proie,liste_predateur);

  
  int monde[SIZE_X][SIZE_Y];// Initialisation du monde (herbe)
   for(i = 0; i<SIZE_X; i++){
    for(j = 0; j<SIZE_Y; j++){
      monde[i][j] = 0;
    }
  }

  int nb = 0;
  int cptproie = compte_animal_it(liste_proie);
  int cptpredateur = compte_animal_it(liste_predateur);
//&&((liste_proie)&&(liste_predateur))
  while((nb<MAX_ITER) && cptproie>0 && cptpredateur>0){
    // Écrire les données dans le fichier
    fprintf(fichier, "%d %u %u", nb, compte_animal_it(liste_proie), compte_animal_it(liste_predateur));
    fprintf(fichier, "\n");
    afficher_ecosys(liste_proie,liste_predateur);
    usleep(T_WAIT);

   
    clear_screen();	
    rafraichir_proies(&liste_proie, monde);
    rafraichir_predateurs(&liste_predateur, &liste_proie);    
    rafraichir_monde(monde);//si on fait pas rafraichir_monde, les proies vont mourir car ils ont pas de l'herber
    
    cptproie = compte_animal_it(liste_proie);
    cptpredateur = compte_animal_it(liste_predateur);
    nb++;
  }
  printf("Nombre de proies à la fin: %d \n",cptproie);
  printf("Nombre de predateurs à la fin: %d \n",cptpredateur);
  printf("Nombre d'iterations : %d \n",nb);
  fclose(fichier); // Fermer le fichier

  if(liste_predateur){
    liste_predateur = liberer_liste_animaux(liste_predateur);
  }
  if(liste_proie){
    liste_proie = liberer_liste_animaux(liste_proie);
  }
  assert(liste_predateur == NULL);
  assert(liste_proie == NULL);
  printf("La simulation est terminée !\n");
  
  
  return 0;
}

//exercice 8

  /*
utiliser gnuplot , il faut taper ces commandes:
  gnuplot
  plot "Evol_Pop.txt" using 1:2 with lines title "proies"
  replot "Evol_Pop.txt" using 1:3 with lines title "predateurs"
  set terminal png
  set output 'graph4.png'
  replot

Les paramètres que l'on peut modifier sont :
  Le nombre de proies/prédateurs au début.
  Leur énergie de base pour faire plus de génération.
  Ou les probabilités dans le fichier ecosys.c
*/