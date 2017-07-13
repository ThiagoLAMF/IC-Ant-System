typedef struct cidade
{
    float x;
    float y;
}Cidade;

float **AlocaCidades(int n_cidades);
float **IniciaCoordenadas(char *arquivo);
float **IniciaMatriz(char *nomeArquivo);
float DistanciaEuclidiana(Cidade c1, Cidade c2);
void PrintCidades(float **cidades,int n_cidades);
