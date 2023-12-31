#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n){
  int numerosValidos[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

  for(int i = 0 ; i < 9 ; i++){
    for(int j = 0 ; j < 9 ; j++){
      int numeroActual = n -> sudo[i][j];

      if(numeroActual != 0){
        if(numerosValidos[numeroActual] == 0){
          numerosValidos[numeroActual] = 1;
        }
        else
          return 0;
      }
    }
  }

  for(int k = 0 ; k < 10 ; k++){
    numerosValidos[k] = 0;
  }

  for(int i = 0 ; i < 9 ; i++){
    for(int j = 0 ; j < 9 ; j++){
      int numeroActual = n -> sudo[j][i];

      if(numeroActual != 0){
        if(numerosValidos[numeroActual] == 0){
          numerosValidos[numeroActual] = 1;
        }
        else
          return 0;
      }
    }
  }

  for(int k = 0 ; k < 10 ; k++){
    numerosValidos[k] = 0;
  }

  for(int k = 0 ; k < 9 ; k++){
    for(int p = 0 ; p < 9 ; p++){
      int x = (k / 3) * 3 + (p / 3);
      int y = (k % 3) * 3 + (p % 3);

      int numeroActual = n -> sudo[x][y];

      if(numeroActual != 0){
        if(numerosValidos[numeroActual] == 0){
          numerosValidos[numeroActual] = 1;
        }
        else
          return 0;
      }
    }
    for(int k = 0 ; k < 10 ; k++){
    numerosValidos[k] = 0;
    }
  }
  
  return 1;
}


List* get_adj_nodes(Node* n){
  List* list = createList();

  for(int i = 0 ; i < 9 ; i++){
    for(int j = 0 ; j < 9 ; j++){
      if(n -> sudo[i][j] == 0){
        
        for(int k = 1 ; k <= 9; k++){
          n -> sudo[i][j] = k;
          
          if(is_valid(n)){
            Node* new_node = copy(n);
            pushBack(list, new_node);
          }
        }
        n->sudo[i][j] = 0;
        return list;
      }
    }
  }
  return list;
}


int is_final(Node* n){
  for(int i = 0 ; i < 9 ; i++){
    for(int j = 0; j < 9 ; j++){
      if(n -> sudo[i][j] == 0) return 0;
    }
  }
  
  return 1;
}

Node* DFS(Node* initial, int* cont){
  Stack* stack = createStack();
  push(stack, initial);

  (*cont) = 0;

  while(is_empty(stack) == 0){
    Node* primerNodo = top(stack);
    pop(stack);

    (*cont)--;

    if(is_final(primerNodo) == 1) return primerNodo;

    List* nodosAdyacentes = get_adj_nodes(primerNodo);

    Node* nodoActual = first(nodosAdyacentes);

    while(nodoActual != NULL){
      push(stack, nodoActual);
      nodoActual = next(nodosAdyacentes);
    }

    (*cont)++;
  }
  
  return NULL;
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/