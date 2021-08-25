#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX 10000

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

void imprimeIn(PArv a){ //Função que imprime a ABB em ordem infixa
    if(a!=NULL) {       //Função utilizada na penúltima atividade de AED 1 com a Prof Daniela Musa
        imprimeIn(a->esq);
        printf("%d ", a->info);
        imprimeIn(a->dir);
    }
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

void imprime_folhas(PArv a){ //Função que imprime as folhas de ABB
    if(a->esq==NULL && a->dir==NULL){
        printf("%d ", a->info);
    }
    if(a->esq!=NULL && a->dir!=NULL){ //Função feita pelo autor do trabalho, utilizando a lógica do imprime infixo acima
        imprime_folhas(a->esq);
        imprime_folhas(a->dir);
    }
}

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
    int vet_ord[MAX], vet_rand[MAX], i;
    srand(time(NULL));
    
    inicializa_arvore(arvore_binaria1);
    inicializa_arvore(arvore_binaria2);
    
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
    
/////////////////////////////CALCULA ALTURA DAS SUB-ARVORES/////////////////////////////////////////
    
    int altura_dir=altura_ABB(arvore_binaria1->dir); //Altura da Sub-Árvore à direita
    printf("A Altura da Sub-ABB1 na direita é %d\n", altura_dir);
    
    int altura_esq=altura_ABB(arvore_binaria1->esq); //Altura da Sub-Árvore à esquerda
    printf("A Altura da Sub-ABB1 na esquerda é %d\n", altura_esq);
    
/////////////////////////////PRINTA AS FOLHAS DA ARVORE/////////////////////////////////////////
    imprime_folhas(arvore_binaria1); //Printa as folhas da Árvore Binária
    
    arvore_binaria1 = libera(arvore_binaria1); //Liberação da Estrutura alocada
    arvore_binaria2 = libera(arvore_binaria2);
    aux = libera(aux);
    
    return 0;
}