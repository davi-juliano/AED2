#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX 1000

int primos_iterados(int x){
    int j=2; //Começa em 2, pois 1 é o valor que todo valor é divisível

    while(j!=x){
        if(x%j!=0){ //Analisa para todos os valores se o x é divisível por algum outro, começando em 2 e terminando em x
            j++;
        }
        else{ 
            return 0; //Retorna 0 caso não for primo
        }
    }
    return 1; //Retorna 1 se é primo
}

int primos_recursivo(int x, int j){
    if(x%j==0){ //Caso base para sair da recursão
        if(x==j){
            return 1; //O j vai iterar até ser igual a x, e se iterar sendo igual, ele é primo
        }
        else{
            return 0; //Caso contrário
        }
    }
    if(x%j!=0){
        return primos_recursivo(x, (j+1)); //Recursão
    }
}

int main(){
    int vetor[1000], i, maior_valor=0;
    srand(time(NULL));
    
    for(i=0; i<MAX; i++){ //Gera os valores randômicos dentro de um range de 0 a 10000
        vetor[i]= rand()%10000;
    }
    
    clock_t comeco1 = clock(); //Começa a contar o algoritmo iterativo
    for(i=0; i<MAX; i++){ //Execução
        if((primos_iterados(vetor[i])==1) && (maior_valor <= vetor[i])){
            maior_valor = vetor[i];
        }
    }
    printf("O maior valor(Iterativo) é %d\n", maior_valor);
    clock_t fim1 = clock(); //Finalização da contagem do algoritmo iterativo 
    double tempo1 = ((double)(fim1 - comeco1))/ CLOCKS_PER_SEC;//Tempo calculado pelo delta tempo
    printf("O algoritmo iterativo demorou %f segundos para executar\n", tempo1);

    clock_t comeco2 = clock(); //Começa a contar o algoritmo recursivo
    for(i=0; i<MAX; i++){
        if((primos_recursivo(vetor[i], 2)==1) && (maior_valor <= vetor[i])){
            maior_valor = vetor[i];
        }
    }
    printf("O maior valor(Recursivo) é %d\n", maior_valor);
    clock_t fim2 = clock(); //Finalização da contagem do algoritmo recursivo
    double tempo2 = ((double)(fim2 - comeco2))/ CLOCKS_PER_SEC; //Tempo calculado pelo delta tempo
    printf("O algoritmo recursivo demorou %f segundos para executar\n", tempo2); // ajustado de acordo com o pacote Time
    
    return 0;
}
 