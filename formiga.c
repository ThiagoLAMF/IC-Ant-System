#define ALFA 2
#define BETA 1.5
#define Q 1
#define RO 0.5
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/**
    Colonia armazena caminho percorrido pela formiga
**/
int** CriaColonia(int tamanho)
{
    int i;
    int **colonia = (int**)malloc(sizeof(int*)*tamanho);

    for(i=0;i<tamanho;i++)
    {
        colonia[i] = (int*) malloc(sizeof(int)*tamanho);
    }
    return colonia;
}

/**
    Armazena feromonio em cada aresta
**/
float** CriaTrilhaFeromonio(int tamanho)
{
    int i,j;
    float **colonia = (float**)malloc(sizeof(float*)*tamanho);

    for(i=0;i<tamanho;i++)
    {
        colonia[i] = (float*) malloc(sizeof(float)*tamanho);
    }

    for(i=0;i<tamanho;i++)
    {
        for(j=0;j<tamanho;j++)
        {
           colonia[i][j] =1;
        }
    }

    return colonia;
}

float** CriaCaminhoDistancia(int tamanho)
{
    int i;
    float **colonia = (float**)malloc(sizeof(float*)*tamanho);

    for(i=0;i<tamanho;i++)
    {
        colonia[i] = (float*) malloc(sizeof(float)*(tamanho+1));
    }
    return colonia;
}

float NovoFeromonio(int v1, int v2,float feromonioAtual,float **matrizCaminhoDistancia,int tam)
{
    int i,j;
    float somatorioArestas = 0;
    for(i=0;i<tam;i++)
    {
        if(matrizCaminhoDistancia[i][0] == v1 && matrizCaminhoDistancia[i][tam] == v2)
        {
            somatorioArestas += Q/matrizCaminhoDistancia[i][tam]; // Q / Somatorio Distancia
            continue;
        }
        for(j=0;j<tam;j++)
        {
            if(matrizCaminhoDistancia[i][j] == v1 && matrizCaminhoDistancia[i][j+1] == v2)
            {
                somatorioArestas += Q/matrizCaminhoDistancia[i][tam]; // Q / Somatorio Distancia
                break;
            }
        }
    }

    return (((1 - RO) * feromonioAtual) + somatorioArestas);
}

float IteraFormiga(float **colonia,float **trilhaFeromonio,int tam)
{
    int visitados[tam][tam]; //vetor de visitados de cada formiga
    float **matrizCaminhoDistancia = CriaCaminhoDistancia(tam); //[tam][tam+1]; //Matriz que armazena o camiho percorrido pela formiga e o tamanho da solução.
    int i,j,k,v;
    float probabilidade[tam];
    int candidatos[tam];

    //Inicializa matriz visitados e menorcaminho
    for(i=0;i<tam;i++)
    {
        for(j=0;j<tam+1;j++)
        {
            if(j<tam) visitados[i][j]= 0;
            matrizCaminhoDistancia[i][j] = 0;
        }
        probabilidade[i] = 0;
    }

    for(i=0;i<tam;i++)
    {
        visitados[i][i] = 1; //formiga i começa no vertice i
        matrizCaminhoDistancia[i][0] = i;

        for(v=1;v<tam;v++)
        {


            float somatorioDistancias = 0;
            int tamCandidatos = 0;
            for(k=0;k<tam;k++)
            {
                if(visitados[i][k] == 0)
                {
                    somatorioDistancias += pow(trilhaFeromonio[i][k],ALFA) * pow(1/colonia[i][k],BETA);
                    candidatos[tamCandidatos] = k;
                    tamCandidatos++;
                }
            }

            for(j = 0;j<tamCandidatos;j++)//calcula probabilidade:(p cada nao visitado uma probabilidade)
            {
                probabilidade[j] = (pow(trilhaFeromonio[i][candidatos[j]],ALFA) * pow((1/colonia[i][candidatos[j]]),BETA) ) / somatorioDistancias;
            }

            //Seleciona um vertice pela roleta
            int escolhido = Roleta(probabilidade,tamCandidatos,candidatos);
            visitados[i][escolhido] = 1;
            matrizCaminhoDistancia[i][v] = escolhido;
            matrizCaminhoDistancia[i][tam] += colonia[ (int)matrizCaminhoDistancia[i][v-1] ] [escolhido]; //atualiza PESO
            //printf("FORMIGA %d P/ %d\n",i,escolhido);
            //getchar();
        }
        matrizCaminhoDistancia[i][tam] += colonia[i] [(int)matrizCaminhoDistancia[i][tam-1] ]; //atualiza PESO(circulo)

    }

    /*printf("\n-----------Caminhos:-------------\n");
    for(i=0;i<tam;i++)
    {
        for(j=0;j<tam+1;j++)
        {
            printf("%.2f ",matrizCaminhoDistancia[i][j]);
        }
        printf("\n");
    }*/

    //getchar();

    //Atualiza Feromonio:
    //printf("\n-----------Feromonio:-------------\n");
    for(i=0;i<tam;i++)
    {
        for(j=0;j<tam;j++)
        {
            trilhaFeromonio[i][j] = NovoFeromonio(i,j,trilhaFeromonio[i][j],matrizCaminhoDistancia,tam);
            //printf("%.5f ",trilhaFeromonio[i][j]);
        }
        //printf("\n");
    }

    //retorna melhor resultado:
    float menorDistancia = 99999999;
    for(i=0;i<tam;i++)
    {
        if(matrizCaminhoDistancia[i][tam] < menorDistancia)
            menorDistancia = matrizCaminhoDistancia[i][tam];
    }

    //printf("\n--MENOR %f",menorDistancia);
    //getchar();
    return menorDistancia;
}



int Roleta(int *probabilidade,int tam,int *candidatos)
{
    int roleta[tam];
    int j;
    roleta[0] = probabilidade[0];

    for(j = 1; j < tam; j++) {
        roleta[j] = roleta[j-1] + probabilidade[j];
    }

    float x = rand()/(float)RAND_MAX;
    for(j = 0; j < tam; j++) {
        if(x <= roleta[j]){
            return candidatos[j];
        }
    }
    return candidatos[j-1];
}
