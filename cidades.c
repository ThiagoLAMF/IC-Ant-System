#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "cidades.h"

/**
    Aloca a matriz que representa a distancia entre as cidades.
**/
float **AlocaCidades(int n_cidades)
{
    int i;
    float **cidades = (float**) malloc(sizeof(float*)*n_cidades);
    if(cidades == NULL) return NULL;

    for(i=0;i<n_cidades;i++)
    {
        cidades[i] = (float*)malloc(n_cidades * sizeof(float));
        if(cidades[i]==NULL) return NULL;
    }
    return cidades;
}

/**
    Inicia a matriz de distancias a partir de um arquivo que contem coordenadas(x,y) das cidades.
**/
float **IniciaCoordenadas(char *nomeArquivo)
{
    FILE *arquivo;
    int n_cidades;
    int i,j;

    arquivo = fopen(nomeArquivo,"r");

    if(arquivo == NULL) return NULL;

    fscanf(arquivo,"%d",&n_cidades);

    Cidade cidadesAux[n_cidades];
    for(i=0;i<n_cidades;i++)
    {
        fscanf(arquivo,"%f",&cidadesAux[i].x);
        fscanf(arquivo,"%f",&cidadesAux[i].y);
    }

    float **cidades = AlocaCidades(n_cidades);

    for(i=0;i<n_cidades;i++)
        for(j=0;j<n_cidades;j++)
            cidades[i][j] = DistanciaEuclidiana(cidadesAux[i],cidadesAux[j]);

    free(arquivo);
    return cidades;
}

/**
    Inicia a matriz de distancias a partir de um arquivo com a matriz de distâncias.
**/
float **IniciaMatriz(char *nomeArquivo)
{
    FILE *arquivo;
    int n_cidades;
    int i,j;

    arquivo = fopen(nomeArquivo,"r");

    if(arquivo == NULL) return NULL;

    fscanf(arquivo,"%d",&n_cidades);

    float **cidades = AlocaCidades(n_cidades);

    for(i=0;i<n_cidades;i++)
        for(j=0;j<n_cidades;j++)
            fscanf(arquivo,"%f",&cidades[i][j]);

    free(arquivo);
    return cidades;
}

/**
    Calcula a distância euclidiana entre 2 coordenadas.
**/
float DistanciaEuclidiana(Cidade c1, Cidade c2)
{
    float dif_x = c2.x - c1.x;
    float dif_y = c2.y - c1.y;

    return sqrt((dif_x*dif_x) + (dif_y*dif_y));
}

/**
    Imprime a matriz.
**/
void PrintCidades(float **cidades,int n_cidades)
{
    int i,j;
    printf("--------Cidades---------");
    for(i=0;i<n_cidades;i++)
    {
        printf("\n");
        for(j=0;j<n_cidades;j++)
            printf("%.2f\t",cidades[i][j]);
    }
}
