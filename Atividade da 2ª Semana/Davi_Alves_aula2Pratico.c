#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 10

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
    int num_livro[5], i=0, j=0, k=0, l=0, m=0, n=0, livro[5][MAX], aux;
    char charaux;
    
    for(i=0; i < 5; i++){ // Zerar todos os valores
        for(j=0; j < MAX; j++){
            livro[i][j]=0; 
        }
    }
    
    for(i=0; i<5; i++){
        j=0;
        while(scanf("%d%c", &livro[i][j++], &charaux) == 2){ //Scanf retorna a quantidade de valores inseridos
            if(charaux == '\n') 
                break;
        }
        
        num_livro[i] = livro[i][0];
        
        livro[i][0]=0;
        aux=livro[i][0]; // Troca de lugar para o numero de livros não ser ultrapassado
        livro[i][0]=livro[i][num_livro[i]]; //Utilizando sempre o num_livro como parâmetro
        livro[i][num_livro[i]]=aux;
        
        insercao(livro[i], num_livro[i]); //Ordenação do vetor de livros por insertion sort (Complexidade: O(n^2))
    }
    
    //A idéia é gerar um primeiro vetor de respostas (com o livro 1 e com livro 2) 
    //E um segundo vetor de respostas (com o livro 3, 4 e 5)
    //E após isso, somar as duas respostas
    
    int respostas1[100]; //Criar um vetor com o pior caso de livros
    
    for(i=0; i<100;i++){ //Inicializar zerando ele (Complexidade (O(n))
        respostas1[i]=0;
    }
    
    for(i=0; i<num_livro[0]; i++){ //Complexidade O(n^2)
        for(j=0; j<num_livro[1];j++){
            respostas1[n] = livro[0][i] + livro[1][j];
            n++;
        }
    }

    insercao(respostas1, n); //Ordenação do vetor de respostas1 pelo insertion sort (Complexidade: O(n^2))
    int save_game1 = n;
    
    int respostas2[1000];
    
    for(i=0; i<1000;i++){ //Inicializar zerando o respostas2 (Complexidade (O(n))
        respostas2[i]=0;
    }
    
    n=0;
    for(k=0;k<num_livro[2];k++){ //Complexidade O(n^3)
        for(l=0;l<num_livro[3];l++){
			for(m = 0 ; m < num_livro[4]; m++){	
                respostas2[n]= livro[2][k]+livro[3][l]+livro[4][m];
                n++;
			}
		}
    }

    insercao(respostas2, n);
    int save_game2 = n;
    int respostas3[100000];
    
    for(i=0; i<10000;i++){ //Inicializar zerando o respostas3 (Complexidade (O(n))
        respostas3[i]=0;
    }
    
    n=0;
    for(i=0; i<save_game1; i++){ //Complexidade O(n^2)
        for(j=0; j<save_game2;j++){
            respostas3[n] = respostas1[i] + respostas2[j];
            n++;
        }
    }
    
    insercao(respostas3, n);
    int save_game3 = n;
    
    int num_somas;
    int resposta = 0;
    scanf("%d", &num_somas);
    
    j=n-1; //Ordenação é crescente, portanto faremos a busca de tras pra frente
    i=0;
    while(i < num_somas){ //Começa de trás pra frente (Devido à ordenação do insertion sort)
        resposta = resposta + respostas3[j]; 
        j--;
        i++;
    }
    
    printf("%d\n", resposta);
    
    return 0;
}