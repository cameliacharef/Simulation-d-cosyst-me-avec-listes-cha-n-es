//CHAREF CAMELIA 21202057
//BEN MIMOUN SARAH 28713241
#include <assert.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ecosys.h"
#include <string.h>

#define NB_PREDATEURS 20
#define NB_PROIES 20

int main(void){
    int energie=10;

    //TESTS TME 2
    printf("PARTIE 1 des tests\n");
    Animal *liste_proie = NULL;
    Animal *liste_predateur = NULL;
    
    srand(time(NULL));// initialiser le générateur de nombres aléatoires avec une graine 
    int i ;
    for(i = 0; i<NB_PROIES; i++){//*
        ajouter_animal(rand()%SIZE_X,rand()%SIZE_Y,energie,&liste_proie);// Tirer une positions aléatoire entre 0 et SIZE_XetY
    }

    for(i = 0; i<NB_PREDATEURS; i++){//O
        ajouter_animal(rand()%SIZE_X,rand()%SIZE_Y,energie,&liste_predateur);
    }
    
    assert(compte_animal_it(liste_predateur)==NB_PREDATEURS);
    assert(compte_animal_it(liste_proie)==NB_PROIES);

    afficher_ecosys(liste_proie, liste_predateur);


    printf("\nPARTIE 2 des tests (entrees-sorties)\n");

    Animal *liste_proie_test_lire = NULL;
	Animal *liste_predateur_test_lire = NULL;
    
    ecrire_ecosys("liste_ecosys.txt", liste_proie, liste_predateur);
	lire_ecosys("liste_ecosys.txt", &liste_proie_test_lire, &liste_predateur_test_lire);
    afficher_ecosys(liste_proie_test_lire, liste_predateur_test_lire); printf("\n");
    
    //coordonnées premier test ecosysteme
    Animal *tempProie = liste_proie;
	printf("coordonnées premier test ecosysteme\nProies :\n");
    while (tempProie) {
  		printf("%d, %d, %f\n", tempProie->x, tempProie->y, tempProie->energie);
  		tempProie = tempProie->suivant;
    }
  
	Animal *tempPredateur = liste_predateur;
  	printf("\nPrédateurs :\n");
  	while (tempPredateur) {
  		printf("%d, %d, %f\n", tempPredateur->x, tempPredateur->y, tempPredateur->energie);
  		tempPredateur = tempPredateur->suivant;
    }
    


    printf("QUESTION 7 TME2 pour enlever_animal()\n");
    int nbproieSup = 5;
    int nbpredateurSup = 5;

    for (i = 0; i < nbproieSup; i++) {
        enlever_animal(&liste_proie, liste_proie);
    }

    for (i = 0; i < nbpredateurSup; i++) {
        enlever_animal(&liste_predateur, liste_predateur);
    }
    printf("Nb predateurs : %5d\tNb proies : %5d\n", compte_animal_it(liste_predateur), compte_animal_it(liste_proie));
    //15 predateurs et 15 proies
    afficher_ecosys(liste_proie, liste_predateur);
    assert(compte_animal_it(liste_predateur)==(NB_PREDATEURS-nbpredateurSup));
    assert(compte_animal_it(liste_proie)==(NB_PROIES-nbproieSup));

    
    
    
    
    //liberer memoire
    liste_proie = liberer_liste_animaux(liste_proie);
    liste_predateur =liberer_liste_animaux(liste_predateur);
    //All heap blocks were freed -- no leaks are possible
    //pas de fuite memoire apres suppression
    assert(liste_predateur == NULL);
    assert(liste_proie == NULL);
    
    liste_proie_test_lire = liberer_liste_animaux(liste_proie_test_lire);
	liste_predateur_test_lire = liberer_liste_animaux(liste_predateur_test_lire);

    assert(liste_proie_test_lire == NULL);
    assert(liste_predateur_test_lire == NULL);

    
    
}