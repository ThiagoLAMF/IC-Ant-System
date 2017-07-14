int** CriaColonia(int tamanho);
float** CriaTrilhaFeromonio(int tamanho);
float IteraFormiga(int **colonia,float **trilhaFeromonio,int tam);
int Roleta(int *probabilidade,int tam,int *candidatos);
float NovoFeromonio(int v1, int v2,float feromonioAtual,float **matrizCaminhoDistancia,int tam);
float** CriaCaminhoDistancia(int tamanho);
