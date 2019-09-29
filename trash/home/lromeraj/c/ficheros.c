#include <stdio.h>
#include <stdlib.h>

#define LEN 50

typedef struct{
	int num;
	//char letra;
} Elemento;

void introducir( char* );
void fusionar(Elemento *, Elemento*, char*, char*, char*);

int main() {

	Elemento p, u;
	char 	nombre1[LEN],
				nombre2[LEN],
				nombre3[LEN];

	// file 1
	printf("Introduzca el nombre de f1: \n");
	fgets(nombre1, LEN-2, stdin);
	introducir( nombre1 );

	// file 2
	printf("Introduzca el nombre de f2: \n");
	fgets(nombre2, LEN-2, stdin);
	introducir( nombre2 );

	// file 3
	printf("Introduzca el nombre de ff: \n");
	fgets(nombre3, LEN-2, stdin);

	fusionar( &p, &u, nombre1, nombre2, nombre3 );

	return 0;
}

void introducir(char *nombre){

	int i, j, k;
	// char t;

	FILE *f1 = fopen(nombre,"w");

	printf("Introduzca la cantidad de elementos que va a introducir: \n");
	scanf("%i",&i);

	for (j=1; j<=i; j++){
		printf("Introduzca el numero %i:\n",j);
		scanf("%i",&k);
		// printf("Introduzca la letra asociado a dicho numero: \n");
		// scanf("%c",&t);
		fprintf(f1,"%i ",k);
	}

}

void fusionar( Elemento *p, Elemento *u, char *nombre1, char *nombre2, char *nombre3){

	FILE *f1, *f2, *ff;

	f1 = fopen(nombre1,"r");
	f2 = fopen(nombre2,"r");
	ff = fopen(nombre3,"w");

	if (f1!=NULL && f2!=NULL && ff!=NULL){
		if(!feof(f1)&&!feof(f2)){
		fscanf(f1,"%i",&p->num);
		fscanf(f2,"%i",&u->num);
	}
		while (!feof(f1)&&!feof(f2)){
			while(p->num<u->num){
				fprintf(ff,"%i ",p->num);
				if(!feof(f1))   fscanf(f1,"%i",&p->num);
				else break;
			}
			while(u->num<p->num){
				fprintf(ff,"%i ",u->num);
				if(!feof(f2))   fscanf(f2,"%i",&u->num);
				else break;
			}
		}
		if(feof(f1)){
			while(!feof(f2)){
				fscanf(f2,"%i",&u->num);
				fprintf(ff,"%i ",u->num);
			}
		}
		else {
			while(!feof(f1)){
				fscanf(f1,"%i",&p->num);
				fprintf(ff,"%i ",p->num);
			}
		}
	}

	else printf("Error al abrir alguno de los ficheros.\n");
	fclose(f1);
	fclose(f2);
	fclose(ff);
}
