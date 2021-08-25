#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX 10000

/////////////////////////////////////////Funções da AVL/////////////////////////////////////////////////
//Funções do Prof. André Backes (prof da Ufu) que apresentam diversas funções da árvore auto-balanceada AVL 
//Link da aula: https://www.youtube.com/watch?v=lQsVUxa3Auk&list=PL8iN9FQ7_jt6H5m4Gm0H89sybzR9yaaka&index=83
//Link do site do Prof. André: https://programacaodescomplicada.wordpress.com/complementar/

struct NO{ //Estrutura de dados da Árvore AVL
    int info;
    int altura;
    struct NO *esq;
    struct NO *dir;
};
typedef struct NO* ArvAVL;

ArvAVL* cria_ArvAVL(){
    ArvAVL* raiz = (ArvAVL*) malloc(sizeof(ArvAVL));
    if(raiz != NULL)
        *raiz = NULL;
    return raiz;
}

void libera_NO(struct NO* no){
    if(no == NULL)
        return;
    libera_NO(no->esq);
    libera_NO(no->dir);
    free(no);
    no = NULL;
}

void libera_ArvAVL(ArvAVL* raiz){
    if(raiz == NULL)
        return;
    libera_NO(*raiz);//libera cada nó
    free(raiz);//libera a raiz
}

int altura_NO(struct NO* no){
    if(no == NULL)
        return -1;
    else
    return no->altura;
}

int fatorBalanceamento_NO(struct NO* no){
    return labs(altura_NO(no->esq) - altura_NO(no->dir));
}

int maior(int x, int y){
    if(x > y)
        return x;
    else
        return y;
}

int consulta_ArvAVL(ArvAVL *raiz, int valor){ //Função que consulta se um valor está dentro da AVL
    if(raiz == NULL)
        return 0;
    struct NO* atual = *raiz;
    while(atual != NULL){
        if(valor == atual->info){
            return 1;
        }
        if(valor > atual->info)
            atual = atual->dir;
        else
            atual = atual->esq;
    }
    return 0;
}

void RotacaoRR(ArvAVL *A){ //Rotação simples à esquerda
    struct NO *B;
    B = (*A)->dir;
    (*A)->dir = B->esq;
    B->esq = (*A);
    (*A)->altura = maior(altura_NO((*A)->esq),altura_NO((*A)->dir)) + 1;
    B->altura = maior(altura_NO(B->dir),(*A)->altura) + 1;
    (*A) = B;
}

void RotacaoLL(ArvAVL *A){ // Rotação simples à direita
    struct NO *B;
    B = (*A)->esq;
    (*A)->esq = B->dir;
    B->dir = *A;
    (*A)->altura = maior(altura_NO((*A)->esq),altura_NO((*A)->dir)) + 1;
    B->altura = maior(altura_NO(B->esq),(*A)->altura) + 1;
    *A = B;
}

void RotacaoLR(ArvAVL *A){ //Rotação Direita-Esquerda
    RotacaoRR(&(*A)->esq);
    RotacaoLL(A);
}

void RotacaoRL(ArvAVL *A){ //Rotação Esquerda-Direita
    RotacaoLL(&(*A)->dir);
    RotacaoRR(A);
}

//A função de inserir na AVL do professor André Backes não aceita a repetição de valores dentro da estrutura,
//Pois compromete o auto-balanceamento da estrutura
int insere_ArvAVL(ArvAVL *raiz, int valor){ //Função de inserir na AVL
    int res;
    if(*raiz == NULL){ //Quando a árvore está vazia ou está em um nó folha
        struct NO *novo;
        novo = (struct NO*)malloc(sizeof(struct NO));
        if(novo == NULL)
            return 0;

        novo->info = valor;
        novo->altura = 0;
        novo->esq = NULL;
        novo->dir = NULL;
        *raiz = novo;
        return 1;
    }

    struct NO *atual = *raiz;
    if(valor < atual->info){ //Caso o nó raíz da rotação ser maior que o filho, ele saberá que é o filho da esquerda
        if((res = insere_ArvAVL(&(atual->esq), valor)) == 1){
            if(fatorBalanceamento_NO(atual) >= 2){
                if(valor < (*raiz)->esq->info ){ //Se o balanceamento for na direita, segue rotação simples na direita
                    RotacaoLL(raiz);
                }else{ //Se o balanceamento for na esquerda, será feito o procedimento da rotação dupla Direita-Esquerda
                    RotacaoLR(raiz);
                }
            }
        }
    }else{
        if(valor > atual->info){ //Caso o nó raíz da rotação ser menor que o filho, ele saberá que é o filho da direita
            if((res = insere_ArvAVL(&(atual->dir), valor)) == 1){
                if(fatorBalanceamento_NO(atual) >= 2){
                    if((*raiz)->dir->info < valor){ //Se o balanceamento for na esquerda, segue rotação simples na esquerda
                        RotacaoRR(raiz);
                    }else{ //Se o balanceamento for na direita, será feito o procedimento da rotação dupla Esquerda-Direita
                        RotacaoRL(raiz);
                    }
                }
            }
        }else{ //Valor duplicado é excluído
            //printf("Valor duplicado!!\n");
            return 0;
        }
    }

    atual->altura = maior(altura_NO(atual->esq),altura_NO(atual->dir)) + 1;

    return res;
}

int altura_avl(ArvAVL *a){ //Código da Professora Lilian Berton da Aula 6 de Algoritmos e Estruturas de Dados 2
    if (a == NULL)
        return 0;
    if (*a == NULL)
        return 0;
    int he = altura_avl(&((*a)->esq));
    int hd = altura_avl(&((*a)->dir));
        if(he < hd) 
            return (hd+1);
        else 
            return (he+1);
}

/////////////////////////////////////////Funções da ABB/////////////////////////////////////////////////

typedef struct arv{ //Estrutura de dados da ABB
    int info;
    struct arv*esq;
    struct arv*dir;
}TArv;
typedef TArv *PArv;

void inicializa_arvore(PArv arvore){ //Função que inicializa a árvore
    arvore=NULL;
}

PArv libera (PArv a){  //Função que libera a árvore 
    if (a!=NULL) {
        libera(a->esq);
        libera(a->dir);
        free(a); 
    }
    return NULL;
}

PArv insereABB (PArv a, int c){     //Função que insere um valor na ABB
    if (a == NULL) {  //Função utilizada na última atividade de AED 1 com a Prof Daniela Musa
        PArv novo=(PArv)malloc(sizeof(TArv));
        novo->esq = NULL;
        novo->dir = NULL;
        novo->info = c;
        a = novo;
    }

    else if (c < a->info)
        a->esq = insereABB(a->esq,c);
    else if (c > a->info)  //Eis a diferença, pois não queremos valores repetidos na ABB
        a->dir = insereABB(a->dir,c);
    else{
        return(a);
    }
}

PArv buscaABB(PArv a, int c){ //Função recursiva que busca um nó de acordo com o dado dele na ABB
    if (a==NULL)            //Função utilizada na última atividade de AED 1 com a Prof Daniela Musa
        return NULL;        
    
    else if(c < a->info)
        return(buscaABB(a->esq,c));
    
    else if (c > a->info)
        return(buscaABB(a->dir,c));
    
    else
        return a;
    
}

int altura_ABB(PArv a){ //Código da Professora Lilian Berton da Aula 6 de Algoritmos e Estruturas de Dados 2
    if (a == NULL){
        return -1;
    }
    else {
        int he = altura_ABB(a->esq);
        int hd = altura_ABB(a->dir);
        if(he < hd) 
            return (hd+1);
        else 
            return (he+1);
    }
}

/////////////////////////////////////////Funções do Vetor/////////////////////////////////////////////////

void busca_vetor(int vetor[], int n, int tam){ //Função feita pelo autor do trabalho
    int i;
    for(i=0; i<tam; i++){
        if(vetor[i]==n){
            //printf("Achou o %d!!", n);
            return;
        }
    }
    //printf("Não achou o %d!!", n);
}

void insercao(int vetor[], int n){ //Função do Prof. André Backes (prof da Ufu) com ordenação por inserção 
    int i, j, aux;      //Link da aula: https://www.youtube.com/watch?v=79buQYoWszA&ab_channel=LinguagemCPrograma%C3%A7%C3%A3oDescomplicada
    
    for(i=1; i < n; i++){
        aux = vetor[i];
        for(j=i; (j>0) && (aux < vetor[j-1]); j--)
            vetor[j]=vetor[j-1];
        vetor[j]=aux;
    }
    return;
}

int main(){
    PArv arvore_binaria1, arvore_binaria2, aux;
    ArvAVL *arvore_avl;
    int vet_ord[MAX], vet_rand[MAX], i, j;
    srand(time(NULL));
    
    inicializa_arvore(arvore_binaria1);
    inicializa_arvore(arvore_binaria2);
    arvore_avl=cria_ArvAVL();
    
    for(i=0; i<MAX; i++){ //Gera os valores randômicos dentro de um range de 0 a 10000
        vet_rand[i]= rand()%6000;
        vet_ord[i]= vet_rand[i];
    }

    clock_t comeco1 = clock(); //Começa a contar o Insertion Sort
    insercao(vet_ord, MAX);
    clock_t fim1 = clock(); //Finalização da contagem do Insertion Sort 
    
    double tempo1 = ((double)(fim1 - comeco1))/ CLOCKS_PER_SEC; //Tempo calculado pelo delta tempo
    printf("O algoritmo do Insertion Sort demorou %f segundos para ordenar o vetor randômico\n", tempo1);

    /*for(i=0; i<MAX; i++)
        printf("%d ", vet_ord[i]);
    
    printf("\n");
    
    for(i=0; i<MAX; i++)
        printf("%d ", vet_rand[i]);
    */
    
    clock_t comeco2 = clock(); //Começa a contar a insercao na ABB
    for(i=0; i<MAX; i++){
        arvore_binaria1 = insereABB(arvore_binaria1, vet_rand[i]);
    }
    clock_t fim2 = clock(); //Finalização da contagem da insercao na ABB 
    
    double tempo2 = ((double)(fim2 - comeco2))/ CLOCKS_PER_SEC; //Tempo calculado pelo delta tempo
    printf("A inserção da ABB demorou %f segundos para inserir o vetor randômico\n", tempo2);
    
    //imprimeIn(arvore_binaria1);
    
    clock_t comeco3 = clock(); //Começa a contar a insercao na ABB
    for(i=0; i<MAX; i++){
        arvore_binaria2 = insereABB(arvore_binaria2, vet_ord[i]);
    }
    clock_t fim3 = clock(); //Finalização da contagem da insercao na ABB 
    
    double tempo3 = ((double)(fim3 - comeco3))/ CLOCKS_PER_SEC; //Tempo calculado pelo delta tempo
    printf("A inserção da ABB demorou %f segundos para inserir o vetor ordenado\n", tempo3);
    
    //imprimeIn(arvore_binaria2);
    
    clock_t comeco4 = clock(); //Começa a contar o algoritmo de inserção
    for(i=0; i<MAX; i++){
        insere_ArvAVL(arvore_avl, vet_rand[i]);
    }
    clock_t fim4 = clock(); //Finalização da contagem do algoritmo de inserção
    
    double tempo4 = ((double)(fim4 - comeco4))/ CLOCKS_PER_SEC; //Tempo calculado pelo delta tempo
    printf("O algoritmo de inserção demorou %f segundos para inserir na AVL\n", tempo4);

    //Após analisar os tempos para vetores ordenados e randômicos, utilzaremos apenas a árvore binária 1
    
    ///////////////////////////////////BUSCA POR 50/////////////////////////////////////////////////////
    
    comeco1 = clock(); //Começa a contar a busca por 50 no vetor ordenado
    busca_vetor(vet_ord, 50, MAX);
    fim1 = clock(); //Finalização da busca por 50 no vetor ordenado
    
    tempo1 = ((double)(fim1 - comeco1))/ CLOCKS_PER_SEC; //Tempo calculado pelo delta tempo
    printf("O Busca Vetor demorou %f segundos para buscar 50 no vetor ordenado\n", tempo1);

    comeco2 = clock(); //Começa a contar a busca por 50 no vetor randômico
    busca_vetor(vet_rand, 50, MAX);
    fim2 = clock(); //Finalização da busca por 50 no vetor randômico 
    
    tempo2 = ((double)(fim2 - comeco2))/ CLOCKS_PER_SEC; //Tempo calculado pelo delta tempo
    printf("O Busca Vetor demorou %f segundos para buscar 50 no vetor randômico\n", tempo2);
    
    comeco3 = clock(); //Começa a contar a busca por 50 na ABB
    aux = buscaABB(arvore_binaria1, 50);
    //printf("%d\n", aux->info);
    fim3 = clock(); //Finalização da busca por 50 na ABB
    
    tempo3 = ((double)(fim3 - comeco3))/ CLOCKS_PER_SEC; //Tempo calculado pelo delta tempo
    printf("O Busca ABB demorou %f segundos para buscar 50 na Árvore Binária\n", tempo3);

    comeco4 = clock(); //Começa a contar a busca pelo valor 50 na AVL
    if(consulta_ArvAVL(arvore_avl, 50)==1){
        printf("Foi encontrado o valor 50!\n");
    }
    else{
        printf("Não foi encontrado o valor 50!\n");
    }
    fim4 = clock(); //Finalização da contagem da busca pelo valor 50 na AVL
    
    tempo4 = ((double)(fim4 - comeco4))/ CLOCKS_PER_SEC; //Tempo calculado pelo delta tempo
    printf("O algoritmo de busca demorou %f segundos para buscar 50 na AVL\n", tempo4);

///////////////////////////////////BUSCA POR 5000/////////////////////////////////////////////////////
    
    comeco1 = clock(); //Começa a contar a busca por 5000 no vetor ordenado
    busca_vetor(vet_ord, 5000, MAX);
    fim1 = clock(); //Finalização da busca por 5000 no vetor ordenado
    
    tempo1 = ((double)(fim1 - comeco1))/ CLOCKS_PER_SEC; //Tempo calculado pelo delta tempo
    printf("O Busca Vetor demorou %f segundos para buscar 5000 no vetor ordenado\n", tempo1);

    comeco2 = clock(); //Começa a contar a busca por 5000 no vetor randômico
    busca_vetor(vet_rand, 5000, MAX);
    fim2 = clock(); //Finalização da busca por 5000 no vetor randômico 
    
    tempo2 = ((double)(fim2 - comeco2))/ CLOCKS_PER_SEC; //Tempo calculado pelo delta tempo
    printf("O Busca Vetor demorou %f segundos para buscar 5000 no vetor randômico\n", tempo2);
    
    comeco3 = clock(); //Começa a contar a busca por 5000 na ABB
    aux = buscaABB(arvore_binaria1, 5000);
    //printf("%d\n", aux->info);
    fim3 = clock(); //Finalização da busca por 5000 na ABB
    
    tempo3 = ((double)(fim3 - comeco3))/ CLOCKS_PER_SEC; //Tempo calculado pelo delta tempo
    printf("O Busca ABB demorou %f segundos para buscar 5000 na Árvore Binária\n", tempo3);
    
    comeco4 = clock(); //Começa a contar a busca pelo valor 5000 na AVL
    if(consulta_ArvAVL(arvore_avl, 5000)==1){
        printf("Foi encontrado o valor 5000!\n");
    }
    else{
        printf("Não foi encontrado o valor 5000!\n");
    }
    fim4 = clock(); //Finalização da contagem da busca pelo valor 5000 na AVL
    
    tempo4 = ((double)(fim4 - comeco4))/ CLOCKS_PER_SEC; //Tempo calculado pelo delta tempo
    printf("O algoritmo de busca demorou %f segundos para buscar 5000 na AVL\n", tempo4);
    
/////////////////////////////CALCULA ALTURA DAS SUB-ARVORES/////////////////////////////////////////
    
    int altura_dir=altura_avl(&((*arvore_avl)->dir)); //Altura da Sub-Árvore à direita
    printf("A Altura da Sub-ABB1 na direita é %d\n", altura_dir);
    
    int altura_esq=altura_avl(&((*arvore_avl)->esq)); //Altura da Sub-Árvore à esquerda
    printf("A Altura da Sub-ABB1 na esquerda é %d\n", altura_esq);

    arvore_binaria1 = libera(arvore_binaria1); //Liberação da Estrutura alocada
    arvore_binaria2 = libera(arvore_binaria2);
    aux = libera(aux);
    libera_ArvAVL(arvore_avl);
    
    return 0;
}