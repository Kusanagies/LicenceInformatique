#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#define TAILLE_MATRICE	10 //On va prendre une matrice de taille 10 pour que ce soit plus "Simple"



//Exemple de glider : 
//matrice[1][2] = 1
//matrice[2][3] = 1
//matrice[3][1] = 1
//matrice[3][2] = 1
//matrice[3][3] = 1
//soit :
//0000
//0010
//0001
//0111

//Voici les fonctions qu'on aura besoin:

//La fonction qui initialise la matrice (Malloc)
int** Initialisation_Matrice(int taille);
//La fonction qui va iniatiliser la matrice avec des cellules vivantes ou mortes
void Initialisation_Matrice_Avec_Des_Cellules_Vivantes(int** TableauMatrice,int taille);
//La fonction qui va compter le nombre de cellule vivante autour d'une cellule vivante ou morte
int nombre_de_voisins(int** matrice,int x,int y);
//La fonction qui permet de mettre a jour la matrice avec les regles du jeu de la vie (a besoin de la fonction nbvoisins
void update(int** matrice);

//fonction principale 
int main(){

	int i,j,k;
	int** tabGameOfLife;
	
	
	
	//Bloc à enlever si on utilise pas la SDL
	////////////////////////////
	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;
	if(0 != SDL_Init(SDL_INIT_VIDEO)){
		fprintf(stderr,"Erreur SDL_INIT_VIDEO : %s",SDL_GetError());
		goto QUIT;
	}
	window = SDL_CreateWindow("SDL2",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,TAILLE_MATRICE,TAILLE_MATRICE,SDL_WINDOW_SHOWN);
	if(NULL == window){
		fprintf(stderr,"Erreur SDL_CreateWindow : %s",SDL_GetError());
		goto QUIT;
	}
	renderer = SDL_CreateRenderer(window, -1,SDL_RENDERER_ACCELERATED);
	if(NULL == renderer){
		fprintf(stderr,"Erruer SDL_CreateRenderer : %s",SDL_GetError());
		goto QUIT;
	}
	
	//SDL_Color Blanc = {0,0,0,255};
	//SDL_Color Noir = {255,255,255,255};
	
	//SDL_SetRenderDrawColor(renderer,Blanc);			Set la couleur à dessiner
	//SDL_RenderDrawPoint(renderer,x,y); Permet de dessiner un point au point x et y
	
	
	////////////////////////////
	
	
	
	
	bool Jeu = true;
	int generation = 1;
	tabGameOfLife = Initialisation_Matrice(TAILLE_MATRICE);
	Initialisation_Matrice_Avec_Des_Cellules_Vivantes(tabGameOfLife,TAILLE_MATRICE);
	
	//test gliders
	/*
	for(i = 0;i < TAILLE_MATRICE;i++){
		for(j = 0;j < TAILLE_MATRICE;j++){
			tabGameOfLife[i][j] = 0;
		}
	}
	tabGameOfLife[1][2] = 1;
	tabGameOfLife[2][3] = 1;
	tabGameOfLife[3][1] = 1;
	tabGameOfLife[3][2] = 1;
	tabGameOfLife[3][3] = 1;
	*/
	
	/*
	printf("Matrice Initial : \n");
	*/
	
	
	while(Jeu){
		
		//Enlever si on fait la SDL
		/*
		printf("Generation %d :\n",generation);
		for(i = 0;i < TAILLE_MATRICE;i++){
			for(j = 0;j < TAILLE_MATRICE;j++){
				printf("%d",tabGameOfLife[i][j]);
			}
			printf("\n");
		}
		*/
		
		//Enlever si on fait pas la SDL
		/////////////
		for(i = 0;i < TAILLE_MATRICE;i++){
			for(j = 0;j < TAILLE_MATRICE;j++){
				if(tabGameOfLife[i][j] == 0){
					SDL_SetRenderDrawColor(renderer,255,255,255,255);
					SDL_RenderDrawPoint(renderer,i,j);
				} else {
					SDL_SetRenderDrawColor(renderer,0,0,0,255);
					SDL_RenderDrawPoint(renderer,i,j);
				}
			}
		}
		SDL_Event event;
		SDL_WaitEvent(&event);
		if(event.type == SDL_QUIT){
			goto QUIT;
		} else if(event.type == SDL_KEYDOWN){
			if(event.key.keysym.sym == SDLK_SPACE){
				update(tabGameOfLife);
			}
		}
		/////////////
		
		
		//Enlevr si on fait PAS la SDL
		/*
		printf("Entrer 1 pour continuer 0 sinon : ");
		IN:
		int Input;
		scanf("%d",&Input);
		
		if(Input == 1){
			update(tabGameOfLife);
			generation++;
		} else if(Input == 0){
			Jeu = false;
		} else {
			printf("Erreur Input veuillez entrer 1 ou 0 :");
			goto IN;
		}
		*/
	}
	
				
	
	for(i = 0;i < TAILLE_MATRICE;i++){
		free(tabGameOfLife[i]);
	}
	free(tabGameOfLife);
	
	//Bloc à enlever si on utilise pas la SDL
	////////////////////////////////
	
	//SDL_Delay(3000); //En ms
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	QUIT:
	SDL_Quit();
	////////////////////////////////
	return 0;
}


int** Initialisation_Matrice(int taille){
	
	int** TabMatrice;
	//Initialise la matrice dans la memoire avec une taille taille
	TabMatrice = malloc(sizeof(int*) * taille);
	if(TabMatrice == NULL){
		printf("Erreur Allocation fonction Init"); 
		return 0;
	}
	int i;
	//Meme chose mais pour chaque lignes
	for(i = 0; i < taille;i++){
		TabMatrice[i] = malloc(sizeof(int*) * taille);
	} 
	return TabMatrice;
}

void Initialisation_Matrice_Avec_Des_Cellules_Vivantes(int** TableauMatrice,int taille){
	int i,j;
	for(i = 0; i < taille;i++){
		for(j = 0;j < taille;j++){
			TableauMatrice[i][j] = rand() % 2; //Choisit un nombre random si pair elle sera egal à 0 si impair à 1
		}
	}
}

int nombre_de_voisins(int** matrice,int x,int y){
	int count = 0;
	int i,j;
	for(i = x - 1;i <= x + 1;i++){ //Va prendre la position x - 1 jusqu'à x + 1 soit trois blocs
		for(j = y - 1;j <= y + 1;j++){ //La meme chose mais pour y
			if(i >= 0 && i < TAILLE_MATRICE && j >= 0 && j < TAILLE_MATRICE && !(i == x && j == y)){ //i et j doivent etre superieur à 0 (sinon en dehors de la matrice)
																									 //i et j doivent aussi etre strictement inferieurs à la taille de la matrice (donc ne pas sortir de la matrice)
																									 // i et j ne doivent pas aussi etre egal au centre de la matrice qu'on etudie (3x3)
				count += matrice[i][j];		// vue que chaque emplacement sont egaux à 1 ou 0 on peut juste l'ajouter à la matrice elle meme										
			}
		}
	}
	return count;
}

void update(int** matrice){
	int i,j;
	int** Matrice2 = Initialisation_Matrice(TAILLE_MATRICE); //On aura besoin d'une matrice qui prendra les valeurs qui seront modifié
	
	for(i = 0;i < TAILLE_MATRICE;i++){
		for(j = 0;j < TAILLE_MATRICE;j++){
			int voisins = nombre_de_voisins(matrice,i,j);
			
			if(matrice[i][j] == 1){ //Si la cellule est vivante qui est aux coordonnées i et j
				if(voisins < 2 || voisins > 3){//Si inféerieur à 2 ou supérieur à 3 alors mort sinon vivant
					Matrice2[i][j] = 0;
				} else {
					Matrice2[i][j] = 1;
				}
			} else {				// si cellule morte
				if(voisins == 3){
					Matrice2[i][j] = 1;
				} else {
					Matrice2[i][j] = 0;
				}
			}
		}
	}
	//La matrice copie la matrice2
	for(i = 0;i < TAILLE_MATRICE;i++){
		for(j = 0;j < TAILLE_MATRICE;j++){
			matrice[i][j] = Matrice2[i][j];
		}
	}
	
	//Libère la mémoire
	for(i = 0;i < TAILLE_MATRICE;i++){
		free(Matrice2[i]);
	}
	free(Matrice2);
}






	
