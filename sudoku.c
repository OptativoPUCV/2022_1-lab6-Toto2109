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

  for(int i = 0; i < 9;i++){
    int fila[10] = {0};
    for (int j = 0; j < 9;j++){
      if (fila[n->sudo[i][j]]) return 0;
      if (n->sudo[i][j] != 0){
        fila[n->sudo[i][j]] = 1;
      }
    }
  }


  for(int i = 0; i < 9;i++){
    int col[10] = {0};
    for (int j = 0; j < 9;j++){
      if (col[n->sudo[j][i]]) return 0;
      if (n->sudo[j][i] != 0){
        col[n->sudo[j][i]] = 1;
      }
    }
  }

  for (int i = 0; i < 9; i++){
    int cuadrante[10] = {0};
    for(int j = 0; j < 9; j++){
      int x=3*(i/3) + (j/3);
      int y=3*(i%3) + (j%3);
      if (cuadrante[n->sudo[x][y]]) return 0;
      if(n->sudo[i][j]){
        cuadrante[n->sudo[i][j]] = 1;
      }
    }
  }

    return 1;
}


List* get_adj_nodes(Node* n){
  List* list=createList();
  for(int i = 0; i < 9; i++){
    for(int j = 0; j < 9 ; j++){
      if(n -> sudo[i][j] == 0){
        for(int k = 1; k < 10; k++ ){
          n -> sudo [i][j] = k;
          if(is_valid(n)){
            Node *new = copy(n);
            push(list,new);
          }
        }
        return list;
      }
    }
  }
  return list;
}


int is_final(Node* n){
  for(int i = 0; i < 9; i++){
    for(int j = 0; j < 9; j++){
      if(n->sudo[i][j] == 0) return 0;
    }
  }
    return 1;
}

Node* DFS(Node* initial, int* cont){
  Stack *S = createStack();
  push(S,initial);
  while(get_size(S) != 0){
    Node* aux = top(S);
    pop(S);
    printf("probando");
    if(is_final(aux)) return aux;
    List* list = get_adj_nodes(aux);
    Node* node = first(list);
    while(node){
      push(S, node);
      node = next(list);
    }
    free(aux);
    cont++;
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