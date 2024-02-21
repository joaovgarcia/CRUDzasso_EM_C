#include <stdio.h>
#include <string.h>

#define TAMANHO_NOME 50
#define TAMANHO_LISTA 50

typedef struct objeto OBJETO;

struct objeto {
  char nome[TAMANHO_NOME];
  int id;
};

OBJETO criaObjeto(char* nome);

void adicionaObjeto(OBJETO* objeto, OBJETO lista[], int* tamanho);

void listarObjetos(OBJETO lista[], int* tamanho);

int buscaObjeto(OBJETO* objeto, OBJETO lista[], int* tamanho); 

void deletaObjeto(int indice, OBJETO lista[], int* tamanho);

void modificaObjeto(char* novoNome, int indice, OBJETO lista[]);

void pulalinha(){
    printf("\n\n");
  }

int main(){
  

  char* nomes[5] = {"Clara", "Rafael", "Jose", "Clarice", "Joao"};

  OBJETO objeto = {0};
  OBJETO objetos[TAMANHO_LISTA] = {0};
  int tamanholista = 0;

  for(int i = 0; i < 5; i++){
    objeto = criaObjeto(nomes[i]);
    adicionaObjeto(&objeto, objetos, &tamanholista);
  }

  listarObjetos(objetos, &tamanholista);

  pulalinha();

  modificaObjeto("Margarida", buscaObjeto(&objetos[3], objetos, &tamanholista), objetos); 

  pulalinha();

  listarObjetos(objetos, &tamanholista);

  pulalinha();

  deletaObjeto(buscaObjeto(&objetos[3], objetos, &tamanholista), objetos, &tamanholista);

  pulalinha();

  listarObjetos(objetos, &tamanholista);

  return 0;
}

void modificaObjeto(char* novoNome, int i, OBJETO lista[]){

  size_t tamanhoNome = strlen(novoNome) +1;

  if(i){
    printf("Alterando objeto: %s\n", lista[i].nome);
    for(int j = 0; j < tamanhoNome; j++){
      lista[i].nome[j] = novoNome[j];
    }
  }
}

void deletaObjeto(int i, OBJETO lista[], int *tamanho){
 
  if(i){
    printf("Deletando objeto: %s\n", lista[i].nome);
    for(int j = i; j < *tamanho; j++){
      lista[j] = lista[j+1];
      (*tamanho)--;
    }
  }else{
    printf("Nenhum objeto foi deletado");
  } 
}

int buscaObjeto(OBJETO* objeto, OBJETO lista[], int* tamanho){
  
  for(int i = 0; i < *tamanho; i++){
    if(objeto->id == lista[i].id){
      printf("Objeto %s encontrado!\n", lista[i].nome);
      return i;
      break;
    }
  printf("Buscando...\n");
  }
    printf("O objeto não existe!");
    return -1;
}



void listarObjetos(OBJETO lista[], int* tamanho){
  
  printf("Usuário \tID\n-------------------\n");
    for(int i = 0; i < *tamanho; i++){
      printf("%-16s", lista[i].nome);
      printf("%d\n",lista[i].id);
    }
}

void adicionaObjeto(OBJETO* objeto, OBJETO lista[], int* tamanho){
  lista[objeto->id - 1] = *objeto; 
  (*tamanho)++;

}

OBJETO criaObjeto(char *nome){
  
  static int id = 1;

  OBJETO obj;
  
  obj.id = id++;

  size_t tamanhoChar = strnlen(nome, TAMANHO_NOME) +1;
  
  strlcpy(obj.nome, nome, tamanhoChar);
  obj.nome[tamanhoChar] = '\0';
  
  return obj;
}


