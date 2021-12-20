#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <limits.h>

void afficher_tableau (int *tb, int taille_tb, int inverse){
	// fonction pour afficher a l'ecran un tableau de valeur (soit depuis le debut, soit depuis la fin)
	int i;
	if (inverse){
		for (i=taille_tb-1;i>=0;i--)
			printf("%d \n", tb[i]);
	}
	else{
		for (i=0;i<taille_tb;i++)
			printf("%d \n", tb[i]);
	}
	printf("\n");
}

void copie_tableau(int *tba, int *tbb, int taille_tb){
	//fonction pour copier le contenu de tba dans tbb
	int i;
	for (i=0;i<taille_tb;i++)
		tbb[i] = tba[i];
}

unsigned long tri_selection(int *tb, int taille_tb){
	int i, j, max, max_pos, tb_tmp[taille_tb];
	unsigned long tps;
	// Copie tableau dans tableau temporaire
	copie_tableau(tb, tb_tmp, taille_tb);
	//Debut prise temps d'execution
	clock_t begin = clock();
	//debut tri
	for (j=taille_tb-1; j>=0;j--){
		max=INT_MIN;
		max_pos=0;
		//iteration dans le tableau pour trouver la valeur max et la position dans le tableau de la valeur max
		for (i=0;i<taille_tb;i++){
			if (tb_tmp[i]> max){
				max_pos = i;
				max = tb_tmp[i];
			}
		}
		tb[j]= tb_tmp[max_pos];
		tb_tmp[max_pos]=INT_MIN;
	}
	clock_t end = clock();
	tps=((end-begin)*1000)/CLOCKS_PER_SEC;
	return tps;
}


unsigned long tri_bulles(int *tb, int taille_tb){
	int i = taille_tb, temp, j;
	bool echange = 1;
	unsigned long tps;
	clock_t begin = clock();
	while(i>0 && echange ){
		echange = 0;
		for (j=0; j<i-1; j++){
			if(tb[j]>tb[j+1]){
				temp = tb[j];
				tb[j] = tb[j+1];
				tb[j+1] = temp;
				echange = 1;
			}
		}
		i--;
	}
	clock_t end = clock();
	tps=((end - begin)*1000)/CLOCKS_PER_SEC;
	return tps;
}

void fusion(int *tb, int *tb_tmp, int debut, int mil, int fin){
	int k, i=debut, j= mil+1;
	for(k=debut; k<=fin;k++){
		if(j>fin||i<= mil&&tb[i]<tb[j]){
			tb_tmp[k] = tb[i];
			i++;
		}
		else{
			tb_tmp[k] = tb[j];
			j++;
		}
	}
	for(k=debut;k<=fin;k++){
		tb[k]=tb_tmp[k];
	}
}

unsigned long tri_fusion(int *tb, int taille_tb){
	int tb_tmp[taille_tb],i=1,debut, fin;
	unsigned long tps;
	clock_t begin = clock();
	while (i<=taille_tb-1){
		debut =0;
		while((debut+i-1)<taille_tb){
			fin = debut+(i*2)-1;
			if (fin >taille_tb-1)
				fin = taille_tb-1;
			fusion(tb, tb_tmp, debut, debut+i-1, fin);
			debut = debut+(i*2);
		}
		i=i+i;
	}
	clock_t end = clock();
	tps=((end - begin)*1000)/ CLOCKS_PER_SEC;
	return tps;
}

void comparaison_tri(int *tb, int taille_tb){
	int tb_tmp[taille_tb], i;
	unsigned long tps_b, tps_s, tps_f, tb_res[3];
	//tb_res = (unsigned long(*))malloc(3*sizeof(unsigned long));
	copie_tableau(tb, tb_tmp, taille_tb);
	//appel des trois fonctions et stockent le resultat dans un tableau de resultats
	for (i=0; i<3;i++){
		copie_tableau(tb_tmp, tb, taille_tb);
		if (i==0){
			tps_b = tri_bulles(tb, taille_tb);
			tb_res[i] = tps_b;
		}
		else if (i==1){
			tps_f = tri_fusion(tb, taille_tb);
			tb_res[i] = tps_f;
		}
		else if (i==2){
			tps_s = tri_selection(tb, taille_tb);
			tb_res[i] = tps_s;
		}
	}
	printf("comparaison des tris: \n");
	for (i=0; i<3;i++){
		if(tb_res[i]==tps_b){
			printf("position %d : tri a bulles avec une duree d'execution de %lu ms \n", i+1, tps_b);
			tps_b=-1;
		}
		else if(tb_res[i]==tps_s){
			printf("position %d : tri selection avec une duree d'execution de %lu ms \n", i+1, tps_s);
			tps_s=-1;
		}
		else if(tb_res[i]==tps_f){
			printf("position %d : tri selection avec une duree d'execution de %lu ms \n", i+1, tps_f);
			tps_f=-1;
		}
	}
}

void main(){
	int taille_tb = 0, choix_tri = 0, choix_mode= 0, *tb_in, *tb_out, i, temp;
	//tableau des noms de types de tri
	char types[][20]={
		"tri a bulles",
		"tri selection",
		"tri fusion"
	};
	unsigned long tps;
	// demande utilisateur taille du tableau
	do{
		printf("Veuiller indiquer la taille du tableau(superieur a 0): \n");
		scanf("%d",&taille_tb);
		if (taille_tb<1)
			printf("le nombre indique n'est pas bon \n");
	}while(taille_tb<1);
	//création tableau entrée, temporaire et sortie
	tb_in = (int(*))malloc(taille_tb*sizeof(int));
	tb_out = (int(*))malloc(taille_tb*sizeof(int));
	//Remplissage tableau entrée
	srand(time(NULL));
	for (i=0;i<taille_tb;i++){
		temp = rand()%20001-10000;
		tb_in[i] = temp;
		tb_out[i] = temp;
	}
	//Selection mode de tri
	do{
		printf("Veuillez selectionner le type de tri (1:tri a bulle, 2:tri selection, 3: tri fusion, 4: comparaison tri): \n");
		scanf("%d",&choix_tri);
		if (choix_tri<1 || choix_tri>4)
			printf("Le choix n'est pas bon \n");
	}while(choix_tri<1 || choix_tri>4);
	//Selection tri croissant ou décroissant
	do{
		printf("Veuillez selectionner le mode de tri (0: ordre croissant, 1: ordre decroissant): \n");
		scanf("%d",&choix_mode);
		if (choix_mode<0 || choix_mode>1)
			printf("Le choix n'est pas bon \n");
	}while(choix_mode<0 || choix_mode>1);
	//selection fonction de tri
	switch(choix_tri){
		case 1: tps = tri_bulles(tb_out, taille_tb);
			break;
		case 2: tps = tri_selection(tb_out, taille_tb);
			break;
		case 3: tri_fusion(tb_out, taille_tb);
			break;
		case 4: comparaison_tri(tb_out, taille_tb);
			break;
	}
	//Affichage tableau de départ et tableau de sortie
	printf("tableau de depart: \n");
	afficher_tableau(tb_in, taille_tb, 0);
	printf("tableau trie: \n");
	afficher_tableau(tb_out, taille_tb, choix_mode);
	if (choix_tri>=1 && choix_tri<=3){
		printf("type de tri: %s \n", types[choix_tri-1]);
		printf("temps d'execution %lu ms", tps);
	}
}