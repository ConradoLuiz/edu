#include <stdio.h>

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

int main(){
    FILE *f;
    Endereco e;
    f = fopen("cep.dat", "r");
    int c;
    char buffer[200];

    int possibilidades[256];

    for(int i=0; i < 256; i++){
        possibilidades[i] = 0;
    }


    while(!feof(f)){
        c = fgetc(f);   
        if(c == -1) break;
        possibilidades[c]++;
    }
    
    //------------------------------
    FILE *saida;
    saida = fopen("coco", "w");

    for(int i=0; i< 256; i++){
        printf("%c,%d\n", i, possibilidades[i]);
        // sprintf(buffer, "%c,%d\n", i, possibilidades[i]);
        // fwrite(buffer, 1, sizeof(buffer), saida);    
    }

    

    return 0;
}