

#include <stdio.h>
#include <stdlib.h>

typedef struct no {
  int chave;
  int contador;
  struct no* esq;         
  struct no* dir;        
} NO, *PONT;


void inicializar(PONT* raiz);
PONT criarNo(int valor);
PONT inserir(PONT raiz, int valor);
PONT removerUmaOcorrencia(PONT raiz, int valor);
PONT lowestCommonAncestor(PONT raiz, int val1, int val2);
PONT removerTodasOcorrencias(PONT raiz, int valor);
PONT buscar(PONT raiz, int valor);
void exibirInOrder(PONT raiz);
int contarNos(PONT raiz);
int contarTotalElementos(PONT raiz);
int kEsimoMenor(PONT raiz, int k);
void imprimirIntervalo(PONT raiz, int min, int max);



void inicializar(PONT* raiz) {
  *raiz = NULL;
}


PONT criarNo(int valor) {
  PONT novo = (PONT) malloc(sizeof(NO));
  if(novo) {
      novo->chave = valor;
      novo->contador = 1;
      novo->esq = NULL;
      novo->dir = NULL;
  }
  return novo;
}


PONT buscar(PONT raiz, int valor) {
    if (raiz==  NULL || raiz-> chave == valor){
        return raiz;
    }
    if (valor < raiz -> chave){
        return buscar(raiz->esq, valor);
    }else{
        return buscar(raiz->dir, valor);
    }
  return NULL; 
}

PONT inserir(PONT raiz, int valor) {
  if(raiz == NULL) {
    return criarNo(valor);
  }
  if (valor< raiz->chave) {
    raiz->esq = inserir(raiz->esq, valor);
    }else if (valor > raiz->chave) {
      raiz->dir = inserir(raiz->dir, valor);
    }else {
      raiz->contador++;
    }
  return raiz;
}

PONT removerUmaOcorrencia(PONT raiz, int valor) {
    if (raiz == NULL) {
        return raiz;
    }
    if (valor < raiz->chave) {
        raiz->esq = removerUmaOcorrencia(raiz->esq, valor);
    } else if (valor > raiz->chave) {
        raiz->dir = removerUmaOcorrencia(raiz->dir, valor); 
    } else {
        if (raiz->contador > 1) {
            raiz->contador--; 
        } else {
            if (raiz->esq == NULL) {
                PONT temp = raiz->dir;
                free(raiz);
                return temp;
            } else if (raiz->dir == NULL) {
                PONT temp = raiz->esq;
                free(raiz);
                return temp;
            }
            
            PONT temp = raiz->dir;
            while (temp->esq != NULL) {
                temp = temp->esq;
            }
            raiz->chave = temp->chave;
            raiz->contador = temp->contador;
            raiz->dir = removerUmaOcorrencia(raiz->dir, temp->chave); // Remove o sucessor
        }
    }
    return raiz; 
}

PONT removerTodasOcorrencias(PONT raiz, int valor) {
  if (raiz == NULL) {
        return raiz;
    }
    if (valor < raiz->chave) {
        raiz->esq = removerTodasOcorrencias(raiz->esq, valor);
    } else if (valor > raiz->chave) {
        raiz->dir = removerTodasOcorrencias(raiz->dir, valor);
    } else {
        if (raiz->esq == NULL) {
            PONT temp = raiz->dir;
            free(raiz);
            return temp;
        } else if (raiz->dir == NULL) {
            PONT temp = raiz->esq;
            free(raiz);
            return temp;
        }
        PONT temp = raiz->dir;
        while (temp->esq != NULL) {
            temp = temp->esq;
        }
        raiz->chave = temp->chave;
        raiz->contador = temp->contador;
        raiz->dir = removerTodasOcorrencias(raiz->dir, temp->chave);
    }
    return raiz;
}





void exibirInOrder(PONT raiz) {
  if(raiz != NULL) {
    exibirInOrder(raiz->esq);
    for(int i = 0; i< raiz->contador; i++) {
      printf("%d ", raiz->chave);
    }
    exibirInOrder(raiz->dir);
  }
  
}


int contarNos(PONT raiz) {
  if(raiz == NULL) {
    return 0; 
  }
  return 1 + contarNos(raiz->esq) + contarNos(raiz->dir);
}


int contarTotalElementos(PONT raiz) {
  if (raiz == NULL){
    return 0;
  }else{
    return raiz->contador + contarTotalElementos(raiz->esq) + contarTotalElementos(raiz->dir);
  }  
}


int kEsimoMenor(PONT raiz, int k) {
  if(raiz==NULL){
    return -1;
  }
  int countEsq = contarTotalElementos(raiz->esq);
  if(k <= countEsq){
    return kEsimoMenor(raiz->esq, k);
  } else if (k<= countEsq+raiz->contador){
    return raiz->chave;
  } else{
    return kEsimoMenor(raiz->dir, k-countEsq-raiz->contador);
  }
}


void imprimirIntervalo(PONT raiz, int min, int max) {
  if (raiz== NULL){
    return;
  }
  if(raiz -> chave> min){
    imprimirIntervalo(raiz->esq, min, max);
  }
  if(raiz->chave >=min && raiz->chave <= max){
    for(int i=0; i<raiz->contador; i++){
      printf("%d ", raiz->chave);
    }
  }
  if(raiz-> chave <max){
    imprimirIntervalo(raiz-> dir, min, max);
  }
}



PONT lowestCommonAncestor(PONT raiz, int val1, int val2) {
  if(raiz == NULL){
    return NULL;
  }
  if(raiz->chave >val1 && raiz->chave > val2){
    return lowestCommonAncestor(raiz->esq, val1, val2);
  }
  if(raiz->chave < val1 && raiz->chave <val2){
    return lowestCommonAncestor(raiz->dir, val1, val2);
  }
  return raiz;
}



int main() {
  PONT raiz;
  inicializar(&raiz);

 
  raiz = inserir(raiz, 10); 
  raiz = inserir(raiz, 5);
  raiz = inserir(raiz, 15);
  raiz = inserir(raiz, 10);
  raiz = inserir(raiz, 5);  
  raiz = inserir(raiz, 5);  
  raiz = inserir(raiz, 18);

  printf("\n--- APÓS INSERIR (10,5,15,10,5,5,18) ---\n");
  printf("InOrder esperado: 5 5 5 10 10 15 18\n");
  printf("InOrder obtido:   ");
  exibirInOrder(raiz); 
  printf("\n");


  PONT node5 = buscar(raiz, 5);
  if (node5) {
      printf("\nBuscar(5): encontrado com contador=%d (esperado=3)\n", node5->contador);
  } else {
      printf("\nBuscar(5): não encontrado (inesperado)\n");
  }

  PONT nodeX = buscar(raiz, 999); // valor não existente
  if (!nodeX) {
      printf("Buscar(999): não encontrado (esperado)\n");
  } else {
      printf("Buscar(999): encontrado??? (inesperado)\n");
  }


  raiz = removerUmaOcorrencia(raiz, 5);

  printf("\n--- APÓS removerUmaOcorrencia(5) ---\n");
  printf("Esperado InOrder: 5 5 10 10 15 18\n");
  printf("InOrder obtido:   ");
  exibirInOrder(raiz);
  printf("\n");

  node5 = buscar(raiz, 5);
  if (node5) {
      printf("Agora contador(5)=%d (esperado=2)\n", node5->contador);
  }


  raiz = removerTodasOcorrencias(raiz, 10);

  printf("\n--- APÓS removerTodasOcorrencias(10) ---\n");
  printf("Esperado InOrder: 5 5 15 18\n");
  printf("InOrder obtido:   ");
  exibirInOrder(raiz);
  printf("\n");


  int qtdNos = contarNos(raiz);
  int totalElem = contarTotalElementos(raiz);
  printf("\ncontarNos => %d (esperado=3)\n", qtdNos);
  printf("contarTotalElementos => %d (esperado=4)\n", totalElem);


  printf("\n--- Teste k-ésimo menor ---\n");
  printf("k=1 => %d (esperado=5)\n", kEsimoMenor(raiz, 1));
  printf("k=2 => %d (esperado=5)\n", kEsimoMenor(raiz, 2));
  printf("k=3 => %d (esperado=15)\n", kEsimoMenor(raiz, 3));
  printf("k=4 => %d (esperado=18)\n", kEsimoMenor(raiz, 4));
  printf("k=5 => %d (esperado=-1)\n", kEsimoMenor(raiz, 5));


  printf("\n--- Teste imprimirIntervalo [6..18] ---\n");
  printf("Esperado: 15 18\nObtido:   ");
  imprimirIntervalo(raiz, 6, 18);
  printf("\n");


  raiz = inserir(raiz, 12);
  raiz = inserir(raiz, 16);
  raiz = inserir(raiz, 3);

  printf("\n--- Árvore após inserir(12,16,3) ---\n");
  printf("InOrder esperado: 3 5 5 12 15 16 18\n");
  printf("Obtido:          ");
  exibirInOrder(raiz);
  printf("\n");


  PONT nLCA;

  nLCA = lowestCommonAncestor(raiz, 3, 5);
  if (nLCA) {
      printf("\nLCA(3,5) => chave=%d (esperado=5)\n", nLCA->chave);
  }

  nLCA = lowestCommonAncestor(raiz, 3, 12);
  if (nLCA) {
      printf("LCA(3,12) => chave=%d (esperado=5)\n", nLCA->chave);
  }

  nLCA = lowestCommonAncestor(raiz, 16, 18);
  if (nLCA) {
      printf("LCA(16,18) => chave=%d (esperado=15)\n", nLCA->chave);
  }

  nLCA = lowestCommonAncestor(raiz, 5, 18);
  if (nLCA) {
      printf("LCA(5,18) => chave=%d (esperado=5)\n", nLCA->chave);
  }

  // Por fim, buscar um LCA com valor inexistente
  nLCA = lowestCommonAncestor(raiz, 100, 3);
  if (!nLCA) {
      printf("LCA(100,3) => NULL (esperado=chave nao existe)\n");
  }

  printf("\n--- FIM DOS TESTES ---\n");

  return 0;
}