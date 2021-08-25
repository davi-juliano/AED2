#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define MAX 100000

int particiona(int *V, int inicio, int fim){
    int esq, dir, pivo, aux;
    esq = inicio;
    dir = fim;
    pivo = V[inicio];
    while(esq<dir){
        while(esq <= fim && V[esq] <= pivo){
            esq++;
        }
        while(dir >= 0 && V[dir] > pivo){
            dir--;   
        }
        if(esq<dir){
            aux=V[esq];
            V[esq]=V[dir];
            V[dir]=aux;
        }
    }
    V[inicio]=V[dir];
    V[dir]=pivo;
    return dir;
}

void QuickSort(int *V, int inicio, int fim){ //Função do Prof. André Backes (prof da Ufu) com ordenação por QuickSort
    int pivo;                               //Link da aula: https://www.youtube.com/watch?v=spywQ2ix_Co&list=PL8iN9FQ7_jt6H5m4Gm0H89sybzR9yaaka&index=52
    if(fim> inicio){
        pivo=particiona(V, inicio, fim); //Particiona também é uma função do código do professor André
        QuickSort(V, inicio, pivo-1);
        QuickSort(V, pivo+1, fim);
    }
}

void Merge(int *V, int inicio, int meio, int fim){
    int *temp, p1, p2, tamanho, i, j, k;
    int fim1=0, fim2=0;
    tamanho = fim-inicio+1;
    p1=inicio;
    p2=meio+1;
    temp=(int*)malloc(tamanho*sizeof(int));
    if(temp!=NULL){
        for(i=0; i<tamanho; i++){
            if(!fim1 && !fim2){
                if(V[p1] < V[p2])
                    temp[i]=V[p1++];
                
                else
                    temp[i]=V[p2++];
                    
                if(p1>meio) fim1=1;
                if(p2>fim) fim2=1;
            }else{
                if(!fim1)
                    temp[i]=V[p1++];
                else
                    temp[i]=V[p2++];
            }
        }
    for(j=0, k=inicio; j<tamanho; j++, k++)
        V[k]=temp[j];
        
    }
    free(temp);
}

void MergeSort(int *V, int inicio, int fim){  //Função do Prof. André Backes (prof da Ufu) com ordenação por MergeSort
    int meio;                           //Link da aula: https://www.youtube.com/watch?v=RZbg5oT5Fgw&list=PL8iN9FQ7_jt6H5m4Gm0H89sybzR9yaaka&index=51
    if(inicio<fim){
        meio=floor((inicio+fim)/2);
        MergeSort(V, inicio, meio);
        MergeSort(V, meio+1, fim);
        Merge(V, inicio, meio, fim); //Merge também é uma função do código do professor André
    }
}

int main(){
    int vetor[MAX], i;
    srand(time(NULL));
    
    for(i=0; i<MAX; i++){ //Gera os valores randômicos dentro de um range de 0 a 100000 (Não gerei para 1000000, pois não há necessidade)
        vetor[i]= rand()%100000;
    }
    
    clock_t comeco1 = clock(); //Começa a contar o algoritmo do MergeSort

    MergeSort(vetor, 0, 100000);
    
    clock_t fim1 = clock(); //Finalização da contagem do algoritmo de MergeSort
    double tempo1 = ((double)(fim1 - comeco1))/ CLOCKS_PER_SEC;//Tempo calculado pelo delta tempo
    printf("O algoritmo do MergeSort demorou %f segundos para executar\n", tempo1);

    clock_t comeco2 = clock(); //Começa a contar o algoritmo do QuickSort

    QuickSort(vetor, 0, 100000);

    clock_t fim2 = clock(); //Finalização da contagem do algoritmo do QuickSort
    double tempo2 = ((double)(fim2 - comeco2))/ CLOCKS_PER_SEC; //Tempo calculado pelo delta tempo
    printf("O algoritmo do QuickSort demorou %f segundos para executar\n", tempo2); // ajustado de acordo com o pacote Time
    
    return 0;
}
 