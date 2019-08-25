#include <stdio.h>
#include <string.h>
#include <iostream>

typedef struct _Endereco Endereco;
 
struct _Endereco
{
    char logradouro[72];
    char bairro[72];
    char cidade[72];
    char uf[72];
    char sigla[2];
    char cep[8];
    char lixo[2];
};

long linhaByte(long nlinha){
    return nlinha * 300;
}
 
int main(int argc, char**argv){

    FILE *f;
    Endereco e;
    long tam_arq;
    int qt;
    int cmp;
    long registro = 300;
    long inicio, fim, meio;
    char* cepPesq;
    bool achou = false;
 
    if(argc != 2)
    {
        fprintf(stderr, "Chamar o programa passando o CEP!\n");
        return 1;
    }

    cepPesq = argv[1];

    f = fopen("cep_ordenado.dat", "r");

    inicio = 0;
    fseek(f, 0, SEEK_END);
    tam_arq = ftell(f);
    fim = (tam_arq/registro);

    int i = 0;
    fseek(f, 0, SEEK_SET);

    while(inicio <= fim && !achou){
        i++;

        meio = (inicio+fim)/2;

        fseek(f, linhaByte(meio), SEEK_SET);
        qt = fread(&e, sizeof(Endereco), 1, f);

        cmp = strncmp(cepPesq, e.cep, 8);
        if(cmp == 0){
            printf("%.72s\n%.72s\n%.72s\n%.72s\n%.2s\n%.8s\n",e.logradouro,e.bairro,e.cidade,e.uf,e.sigla,e.cep);
            achou = true;
            break;
        }
        else if(cmp > 0){
            inicio = meio + 1;
        }
        else{
            fim = meio -1;
        }
    }

    if(!achou){
        std::cout<<"CEP nao encontrado.\n";
    }
    std::cout<<"Numero de comparacoes: "<< i<<std::endl;
    
    return 0;
}