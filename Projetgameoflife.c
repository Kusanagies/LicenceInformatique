#include <stdio.h>
#include <stdlib.h>
//On va faire un programme avec le jeu de la vie en 100x100
#define TAILLE_MATRICE 10

//On initialise la matrice et initialise chaque case du tableau à 0
//On mettra ensuite des 1 (Cellules vivantes) avec la fonction rand() 

int **Initialisation_Matrice(int taille){
	int **TableauMatrice;
	TableauMatrice = malloc(sizeof(int*) * taille);
	if(TableauMatrice == NULL){
		printf("Erreur Allocation Memoire");
		return 0;
	}
	int i;
	for(i = 0;i < taille;i++){
		TableauMatrice[i] = malloc(sizeof(int*) * taille);
	}
	return TableauMatrice;
}

//Cette fonction va nous permettre d'initialiser la matrice de taille TAILLE avec des 1 ou des 0
void Initialisation_Matrice_Avec_Des_Cellules_Vivantes(int **TableauMatrice,int taille){
	int i,j;
	for(i = 0;i < taille;i++){
		for(j = 0;j < taille;j++){
			if(rand()%2 == 0){
				TableauMatrice[i][j] = 1;
			} else {
				TableauMatrice[i][j] = 0;
			}
		}
	}
}

int nombre_de_voisins(int **matrice ,int x,int y){ // x,y = L'emplacement du milieu du 3x3 et
	int count = 0;
	int i,j;
	for(i = x - 1;i <= x+1;i++){
		for(j = y - 1;j <= y+1;j++){
			count = count + matrice[i][j];
			count = count - matrice[x][y];
		}
	}
	return count;
}


void update(int **matrice){
	int i,j,k,l;
	int x,y; //Coordonné de la matrice à mettre à jour
	int nbVoisins;
	for(i = 0;i < TAILLE_MATRICE;i++){
		for(j = 0; j < TAILLE_MATRICE;j++){
			nbVoisins = 0;
			for(k = - 1;k <= 1;k++){
				for(l = -1;l <= 1;l++){
					x = (i + k + TAILLE_MATRICE)%TAILLE_MATRICE;
					y = (j + l + TAILLE_MATRICE)%TAILLE_MATRICE;
				}
			}
			nbVoisins = nbVoisins - matrice[i][j];
			if(matrice[i][j] == 1 && nbVoisins < 2){
				matrice[i][j] = 0;
			} else if (matrice[i][j] == 1 && nbVoisins > 3){
				matrice[i][j] = 0;
			} else if(matrice[i][j] == 0 && nbVoisins == 3){
				matrice[i][j] = 1;
			}
		}
	}
}

int main(){
	int i,j,k;
	int **tabGameOfLife;
	int Nb,Cycle;
	
	tabGameOfLife = Initialisation_Matrice(TAILLE_MATRICE);
	Initialisation_Matrice_Avec_Des_Cellules_Vivantes(tabGameOfLife,TAILLE_MATRICE);
	printf("Entrez le nombre de cycle :\n");
	scanf("%d\n",&Cycle);
	
	for(k = 0;k < Cycle;k++){
		update(tabGameOfLife);
		//Print de la matrice de taille TAILLE_MATRICE
		for(i = 0;i < TAILLE_MATRICE;i++){
			for(j = 0;j < TAILLE_MATRICE;j++){
				Nb = tabGameOfLife[i][j];
				printf("%d",Nb);
			}
			printf("\n");
		}
	}
	return 0;
}


