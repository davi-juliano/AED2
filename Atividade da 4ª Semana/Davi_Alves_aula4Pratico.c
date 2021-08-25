#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int fatorial(int num){ //Outra função que tirei do baú de LP (Bem clássica)
    int j, fat;
    if(num == 0){
        return 1; 
    }  
    else{
        fat = 1;
        j = num;
        while(num > 0){
            fat = fat * num;
            num--;
        }
        return fat;
    }   
}      

void faz_permutacao(char string[], int aux, int j, char strings[][10]){
    int tamanho, i;
    char auxchar; //Eu utilizei uma função antiga que fiz em LP para fazer essa permutação sem repetições
    
    tamanho = strlen(string);
    
    if(aux == tamanho){
        strcpy(strings[j], string); //Tentei colocar uns argumentos a mais para armazenar em um vetor que eu supostamente ordenaria
        printf("%s\n", strings[j]); //Mas não deu certo :'(
    }
    else{
        for(i=aux; i<tamanho;i++){
            auxchar = string[i]; 
            string[i] = string[aux]; 
            string[aux] = auxchar;
            
            faz_permutacao(string, aux+1, j+1, strings);
            
            auxchar = string[aux]; 
            string[aux] = string[i]; 
            string[i] = auxchar;
        }
    }
}

void bubble_string(char strings[][10], int num_fat){ //Tentativa de utilizar o bubble sort em strings, mas como não funcionou o vetor na 
    int i, j;                                        //Função acima, eu decidi deixar, mas sem executá-lo 
    char vetaux[100];
    for(i=0; i < num_fat; i++){
        for(j = i+1; j < num_fat; j++){
            if(strcmp(strings[i], strings[j]) > 0){
                strcpy(vetaux, strings[i]);
                strcpy(strings[i], strings[j]);
                strcpy(strings[j], vetaux);
            }
        }
    }
}

int main(){
    int num, i, tamanho, j, fat;
    char string[10], strings[100][10];
    srand(time(NULL));

    scanf("%d", &num);
   
    for(i=0; i<num; i++){ //Execução dos n valores de strings que serão dadas
        scanf("%s", string);
        getchar();
        
        clock_t comeco1 = clock(); //Começa a contar o algoritmo da permutação
        
        faz_permutacao(string, 0, 0, strings);
        tamanho = strlen(string);
        fat = fatorial(tamanho);
        /* bubble_string(strings[i], fat);
        for(j=0; j < fat; j++){
            printf("%s\n", strings[j]);
        }*/
        
        clock_t fim1 = clock(); //Finalização da contagem do algoritmo da permutação 
        double tempo1 = ((double)(fim1 - comeco1))/ CLOCKS_PER_SEC;//Tempo calculado pelo delta tempo
        printf("O algoritmo da permutação demorou %f segundos para executar\n", tempo1);
    }
    
    
    
    return 0;
}