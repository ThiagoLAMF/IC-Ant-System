

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
float** CriaTrilhaFeromonio()
{
    int i;
    float **colonia = (float**)malloc(sizeof(float*)*tamanho);

    for(i=0;i<tamanho;i++)
    {
        colonia[i] = (float*) malloc(sizeof(float)*tamanho);
    }
    return colonia;
}

void IteraFormiga(int **colonia,float **trilhaFeromonio,int tamanho)
{
    int visitados[tam];

}
