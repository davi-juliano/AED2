#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX 10000

//Funções utilizadas pelo professor André Backes em suas aulas 89-98 sobre Tabelas Hash
//Alterações feitas pelo autor do trabalho na substituição de uma struct dentro da Tabela Hash, mas sempre
//Mantendo a lógica utilizada pelo professor André.
//Link: https://www.youtube.com/watch?v=njkANXEMHTY&amp

typedef struct hash{ //Definição do tipo Hash
    int qtd, TABLE_SIZE;
    int **num;
}Hash;

Hash* criaHash(int TABLE_SIZE){ //Função de criação de uma Hash 
    Hash* ha = (Hash*) malloc(sizeof(Hash)); //Criação muito semelhante a de um vetor alocado dinamicamente
    if(ha != NULL){
        int i;
        ha->TABLE_SIZE = TABLE_SIZE;
        ha->num = (int**) malloc(TABLE_SIZE * sizeof(int*));
        if(ha->num == NULL){
            free(ha);
            return NULL;
        }
        ha->qtd = 0;
        for(i=0; i < ha->TABLE_SIZE; i++)
            ha->num[i] = NULL;
    }
    return ha;
}

void liberaHash(Hash* ha){ //Função que libera uma Tabela Hash
    if(ha != NULL){
        int i;
        for(i=0; i < ha->TABLE_SIZE; i++){
            if(ha->num[i] != NULL)
                free(ha->num[i]); //Ela libera numero por numero
        }
        free(ha->num); //Para posteriormente liberar toda lista e a tabela
        free(ha);
    }
}

//Função de divisão
int chaveDivisao(int chave, int TABLE_SIZE){
    return (chave & 0x7FFFFFFF) % TABLE_SIZE; //De acordo com o professor, a operação de E Bit a Bit elimina 
                                              //o sinal do valor da chave
}

int insereHash_SemColisao(Hash* ha, int num){ //Função de inserção e busca dos hash's sem colisão
    if(ha == NULL || ha->qtd == ha->TABLE_SIZE) //Novamente, inserção semelhante a um vetor alocado
        return 0;

    int pos = chaveDivisao(num,ha->TABLE_SIZE); //Entretanto, há a chave de inserção que é dada pela função de divisão
    int* novo;
    novo = (int*) malloc(sizeof(int));
    if(novo == NULL)
        return 0;
    *novo = num;
    ha->num[pos] = novo; //Inserção na posição da chave dada
    ha->qtd++;
    return 1;
}

int buscaHash_SemColisao(Hash* ha, int busca ,int* num){ //Busca utilizando a chave dada pela função de divisão
    if(ha == NULL)
        return 0;

    int pos = chaveDivisao(busca, ha->TABLE_SIZE);
    if(ha->num[pos] == NULL)
        return 0;
    *num = *(ha->num[pos]); //Retorna o numero encontrado no ponteiro num
    return 1;
}

//Função da sondagem linear para endereçamento aberto
int sondagemLinear(int pos, int i, int TABLE_SIZE){
    return ((pos + i) & 0x7FFFFFFF) % TABLE_SIZE;
}

int insereHash_EnderAberto(Hash* ha, int num){ //Mantém a lógica da inserção sem colisão, entretando, ele utiliza 
    if(ha == NULL || ha->qtd == ha->TABLE_SIZE) //a sondagem linear para colisões
        return 0;
    int i, pos, newPos;
    pos = chaveDivisao(num,ha->TABLE_SIZE);
    
    for(i=0; i < ha->TABLE_SIZE; i++){
        newPos = sondagemLinear(pos,i,ha->TABLE_SIZE); //Utilização do método da sondagem linear
        if(ha->num[newPos] == NULL){
            int* novo;
            novo = (int*) malloc(sizeof(int));
            if(novo == NULL)
                return 0;
            *novo = num;
            ha->num[newPos] = novo;
            ha->qtd++;
            return 1;
        }
    }
    return 0;
}

int buscaHash_EnderAberto(Hash* ha, int inserir, int* num){ //Novamente é a mesma lógica, mas com a chave de sondagem linear
    if(ha == NULL)
        return 0;

    int i, pos, newPos;
    pos = chaveDivisao(inserir,ha->TABLE_SIZE);
    
    for(i=0; i < ha->TABLE_SIZE; i++){
        newPos = sondagemLinear(pos,i,ha->TABLE_SIZE);
        if(ha->num[newPos] == NULL)
            return 0;

        if((*ha->num[newPos]) == inserir){
            *num = *(ha->num[newPos]); //Retorna o num com o valor dado pela tabela hash
            return 1;
        }
    }
    return 0;
}

int main(){
    int tamanho = MAX, i, num;
    Hash *tabela1 = criaHash(tamanho); //Criação da tabela para o método sem colisões
    int vetaux[MAX];
    srand(time(NULL));
    
    clock_t comeco1 = clock(); //Começa a contar a inserção na Tabela Hash
    for(i=0; i<tamanho; i++){
        vetaux[i]=rand()%10000;
        if(insereHash_SemColisao(tabela1, vetaux[i])==1){
            //printf("Inserido com sucesso!\n");
        }
        else{
            //printf("Houve erro na insercao!\n");
        }
    }
    clock_t fim1 = clock(); //Finalização da contagem da inserção na Tabela Hash

    double tempo1 = ((double)(fim1 - comeco1))/ CLOCKS_PER_SEC; //Tempo calculado pelo delta tempo
    printf("O algoritmo de insercao na Tabela Hash demorou %f segundos\n", tempo1);

    clock_t comeco2 = clock();
    if(buscaHash_SemColisao(tabela1, 999, &num)==1){
        printf("O numero %d foi encontrado!!\n", num);
    }
    else{
        printf("O numero não foi encontrado!\n");
    }
    clock_t fim2 = clock();

    double tempo2 = ((double)(fim2 - comeco2))/ CLOCKS_PER_SEC; //Tempo calculado pelo delta tempo
    printf("O algoritmo de busca na Tabela Hash demorou %f segundos\n", tempo2);

    Hash *tabela2 = criaHash(tamanho); //Criação da tabela com o Endereçamento Aberto

    comeco1 = clock(); //Começa a contar a inserção na Tabela Hash com Endereçamento Aberto
    for(i=0; i<tamanho; i++){
        if(insereHash_EnderAberto(tabela2, vetaux[i])==1){
            //printf("Inserido com sucesso!\n");
        }
        else{
            //printf("Houve erro na insercao!\n");
        }
    }
    fim1 = clock(); //Finalização da contagem da inserção na Tabela Hash com Endereçamento Aberto

    tempo1 = ((double)(fim1 - comeco1))/ CLOCKS_PER_SEC; //Tempo calculado pelo delta tempo
    printf("O algoritmo de insercao na Tabela Hash de Endereçamento Aberto demorou %f segundos\n", tempo1);

    comeco2 = clock();
    if(buscaHash_EnderAberto(tabela2, 999, &num)==1){
        printf("O numero %d foi encontrado!!\n", num);
    }
    else{
        printf("O numero não foi encontrado!\n");
    }
    fim2 = clock();

    tempo2 = ((double)(fim2 - comeco2))/ CLOCKS_PER_SEC; //Tempo calculado pelo delta tempo
    printf("O algoritmo de busca na Tabela Hash de Endereçamento Aberto demorou %f segundos\n", tempo2);
    
    liberaHash(tabela1);
    liberaHash(tabela2);

    return 0;
}