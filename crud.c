#include <stdio.h>
#include <string.h>
#include <error.h>

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

void adicionaObjeto(OBJETO objeto, OBJETOS* objetos);

char* listarObjetos(OBJETOS objetos);

int buscaObjeto(OBJETO* objeto, OBJETOS objetos); 

void deletaObjeto(int indice, OBJETOS* objetos);

void modificaObjeto(char* novoNome, int indice, OBJETOS* objetos);

void criaArquivo(OBJETOS lista, ARQUIVO* arquivo);

void mostraArquivo(ARQUIVO arquivo);

void pulalinha(){
    printf("\n\n");
}

int main(){
  
  char* nomes[7] = {"Clara", "Rafael", "Jose", "Clarice", "Joao", "Valdsnei", "maria"};

  OBJETO objeto = {0};
  OBJETOS objetos = {.lista = {{{0}}}, .tamanholista = 0};
  ARQUIVO arquivo = {.nome = "objetos.txt"};


  for(int i = 0; i < 7; i++){
    objeto = criaObjeto(nomes[i]);
    adicionaObjeto(objeto, &objetos);
  }

  listarObjetos(objetos);

  pulalinha();

  modificaObjeto("Margarida", buscaObjeto(&objetos.lista[3], objetos), &objetos); 

  pulalinha();

  listarObjetos(objetos);

  pulalinha();

  deletaObjeto(buscaObjeto(&objetos.lista[3], objetos), &objetos);

  pulalinha();

  listarObjetos(objetos);

  criaArquivo(objetos, &arquivo);

  mostraArquivo(arquivo);
  return 0;
}

void mostraArquivo(ARQUIVO arquivo){

  char linha[100];

  arquivo.Objetos = fopen(arquivo.nome, "r");

  if(arquivo.Objetos == NULL){
    printf("Parece que o arquivo não existe!");
  }else{
    printf("Mostrando arquivo...\n");
    while(fgets(linha, sizeof(linha), arquivo.Objetos))
      printf("%s\n", linha); 
  }
}

void criaArquivo(OBJETOS lista, ARQUIVO* arquivo){

  char* cabecalho = "Usuário \tID\n-------------------\n";
  int numerolinhas = lista.tamanholista;

  arquivo->Objetos = fopen(arquivo->nome, "r");

  if(arquivo->Objetos == NULL){
    printf("Criando um novo arquivo...\n\n");
    arquivo->Objetos = fopen(arquivo->nome, "w");
    fprintf(arquivo->Objetos, "%d\n", numerolinhas);
    fputs(cabecalho, arquivo->Objetos);
    fprintf(arquivo->Objetos, "%s", listarObjetos(lista));
    printf("Arquivo criado com sucesso!\n");
  }else{
    printf("O arquivo ja foi criado, substituindo...\n");
    arquivo->Objetos = fopen(arquivo->nome, "w");
    fprintf(arquivo->Objetos, "%d\n", numerolinhas);
    fputs(cabecalho, arquivo->Objetos);
    fprintf(arquivo->Objetos, "%s", listarObjetos(lista));
    printf("O arquivo foi substituido pela nova lista.\n");
  }
   
  fclose(arquivo->Objetos);

}

void modificaObjeto(char* novoNome, int i, OBJETOS* objetos){

  size_t tamanhoNome = strlen(novoNome) +1;

  if(i != -1){
    printf("Alterando objeto: %s\n", objetos->lista[i].nome);
    for(int j = 0; j < tamanhoNome; j++){
      objetos->lista[i].nome[j] = novoNome[j];
    }
  }
}

void deletaObjeto(int i, OBJETOS* objetos){
 
  if(i != -1){
    printf("Deletando objeto: %s\n", objetos->lista[i].nome);
    for(int j = i; j < objetos->tamanholista; j++){
      objetos->lista[j] = objetos->lista[j+1];
    }
  }else{
    printf("Nenhum objeto foi deletado\n\n");
  } 
  objetos->tamanholista--;
}

int buscaObjeto(OBJETO* objeto, OBJETOS objetos){
  
  for(int i = 0; i < objetos.tamanholista; i++){
    if(objeto->id == objetos.lista[i].id){
      printf("Objeto %s encontrado!\n", objetos.lista[i].nome);
      return i;
      break;
    }
  printf("Buscando...\n");
  }
    printf("O objeto não foi encontrado!\n\n");
    return -1;
}



char* listarObjetos(OBJETOS objetos){
  
  char tempStr[1024] = {0};
  char* temp = tempStr;
  
  printf("Usuário \tID\n-------------------\n");
    for(int i = 0; i < objetos.tamanholista; i++){
      char tmp[100];
      snprintf(tmp, sizeof(tmp), "%-16s%d\n", objetos.lista[i].nome, objetos.lista[i].id);
      strcat(temp, tmp);
      printf("%s", tmp);
    }
 return temp;
}

void adicionaObjeto(OBJETO objeto, OBJETOS* objetos){
    objetos->lista[objetos->tamanholista] = objeto; 
    objetos->tamanholista++;
  
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


