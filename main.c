#include "cidades.h"

int main()
{
    //float ** cidades = IniciaCoordenadas("2.txt");
    float ** cidades = IniciaMatriz("1.txt");

    PrintCidades(cidades,6);

    return 0;
}
