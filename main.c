#include "cidades.h"
#include "formiga.h"
#include <stdio.h>
#define TAM_CIDADES  38
#define ITERACOES 10000

int main()
{
    //float ** cidades = IniciaCoordenadas("2.txt");
    //float ** cidades = IniciaMatriz("1.txt");
    //float ** cidades = IniciaCoordenadas("3.txt"); //29
    float ** cidades = IniciaCoordenadas("4.txt"); //38


    PrintCidades(cidades,TAM_CIDADES);
    int ** colonia = CriaColonia(TAM_CIDADES);
    int ** trilhaFeromonio = CriaTrilhaFeromonio(TAM_CIDADES);


    int i;
    float menorDistancia = 999999;
    float d;

    for(i=0;i<ITERACOES;i++)
    {
        d = IteraFormiga(cidades,trilhaFeromonio,TAM_CIDADES);
        if(d < menorDistancia)
            menorDistancia = d;
    }

    printf("\n\nMENOR DISTANCIA: %f",menorDistancia );

    return 0;
}
