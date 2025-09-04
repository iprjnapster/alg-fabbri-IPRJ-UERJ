/* R. Fabbri, 2024 */
#include "linked_list_string.h"
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <string>
#include <iostream>

#define MAX_NUMERO_DE_CARACTERES 64
struct No {
	// char *name;
	
	 char name[MAX_NUMERO_DE_CARACTERES];
	// opcional: convencao de '\0' no final
	 
	No *next;
};

typedef No *Lista;
//----------------------------------
struct No2 {
	char *name;

	No2 *next;
};

typedef No2 *Lista2;

void 
playground_lista2(){
	Lista2 l;

	l = (No2 *) malloc(sizeof(No2));
	l -> name = 0;
    
    // usando \0 (necessario alocar memoria para o caractere)
    l->name = (char *) malloc(sizeof(1));
	l->name[0] = '\0';
    printf("%s", l->name);
    printf("print vazio realizado\n");

    // ou
    // l->name = "";
	// printf("%s", l->name);
    // printf("print vazio realizado\n");

	l -> name = "joao\n";
	printf("%s", l->name);	
}

void
playground_lista()
{
	Lista l;

	// cria um novo no
	
	l = (No *) malloc(sizeof(No));
	
	//no cado da implementacao estatica
	l->name[0] = '\0';

	//ou no caso do char* :
	// l->name = "";
	// l->name = 0;


	std::cout << std::string(l->name) <<std::endl;
	// ou
	printf("%s", l->name); //assume que nome contem '\0'
	strncpy(l->name, "joao\n", MAX_NUMERO_DE_CARACTERES);
	printf("%s", l->name); //assume que nome contem '\0'

}
