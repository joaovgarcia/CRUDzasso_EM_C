#include <stdio.h>
#include <string.h>

#define TAMANHO_NOME 50
#define TAMANHO_LISTA 50

struct arquivo{
  
  FILE* Objetos;
  char nome[TAMANHO_NOME];
  int linhas;

};
typedef struct arquivo ARQUIVO;

struct objeto {
  char nome[TAMANHO_NOME];
  int id;
};
typedef struct objeto OBJETO;

struct objetos{

  OBJETO lista[TAMANHO_LISTA];
  int tamanholista;

  
};
typedef struct objetos OBJETOS;

OBJETO criaObjeto(char* nome);

void adicionaObjeto(OBJETO* objeto, OBJETO lista[], int* tamanho);

void listarObjetos(OBJETO lista[], int* tamanho);

int buscaObjeto(OBJETO* objeto, OBJETO lista[], int* tamanho); 

void deletaObjeto(int indice, OBJETO lista[], int* tamanho);

void modificaObjeto(char* novoNome, int indice, OBJETO lista[]);

void criaArquivo(OBJETOS lista, ARQUIVO arquivo);

void mostraArquivo(FILE* f);

void pulalinha(){
    printf("\n\n");
}

int main(){
  
  char* nomes[5] = {"Clara", "Rafael", "Jose", "Clarice", "Joao"};

  OBJETO objeto = {0};
  OBJETOS objetos = {0};


  for(int i = 0; i < 5; i++){
    objeto = criaObjeto(nomes[i]);
    adicionaObjeto(&objeto, objetos.lista, &objetos.tamanholista);
  }

  listarObjetos(objetos.lista, &objetos.tamanholista);

  pulalinha();

  modificaObjeto("Margarida", buscaObjeto(&objetos.lista[3], objetos.lista, &objetos.tamanholista), objetos.lista); 

  pulalinha();

  listarObjetos(objetos.lista, &objetos.tamanholista);

  pulalinha();

  deletaObjeto(buscaObjeto(&objetos.lista[3], objetos.lista, &objetos.tamanholista), objetos.lista, &objetos.tamanholista);

  pulalinha();

  listarObjetos(objetos.lista, &objetos.tamanholista);

  criaArquivo(objetos, ar);

  return 0;
}

/*void mostraArquivo(FILE* f){

  f = fopen("objetos.txt", "r");

  if(f != NULL){

  }
  
}*/

void criaArquivo(OBJETOS lista, ARQUIVO arquivo){

  strcpy(arquivo.nome, "objetos.txt");

  if(arquivo.Objetos != NULL){
    printf("Você está prestes a substituir todo o conteúdo do arquivo pela ultima lista criada\n"
           "Deseja continuar?\n"); 
  }else{
    printf("Criando um novo arquivo...\n\n");
    arquivo.Objetos = fopen(arquivo.nome, "w+");
        printf("Arquivo criado com sucesso!\n");
        puts("Usuário \tID\n-------------------\n");

  }

  fclose(arquivo.Objetos);

}

void modificaObjeto(char* novoNome, int i, OBJETO lista[]){

  size_t tamanhoNome = strlen(novoNome) +1;

  if(i != -1){
    printf("Alterando objeto: %s\n", lista[i].nome);
    for(int j = 0; j < tamanhoNome; j++){
      lista[i].nome[j] = novoNome[j];
    }
  }
}

void deletaObjeto(int i, OBJETO lista[], int *tamanho){
 
  if(i != -1){
    printf("Deletando objeto: %s\n", lista[i].nome);
    for(int j = i; j < *tamanho; j++){
      lista[j] = lista[j+1];
      (*tamanho)--;
    }
  }else{
    printf("Nenhum objeto foi deletado\n\n");
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
    printf("O objeto não foi encontrado!\n\n");
    return -1;
}



void listarObjetos(OBJETO lista[], int* tamanho){
  
  char tempStr[1024];
  char* temp = tempStr;
  

  printf("Usuário \tID\n-------------------\n");
    for(int i = 0; i < *tamanho; i++){
      snprintf(temp, sizeof(tempStr), "%-15s%d\n", lista[i].nome, lista[i].id);
      printf("%s", temp);
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


