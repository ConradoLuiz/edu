#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Endereco Endereco;

struct _Endereco {
    char logradouro[72];
    char bairro[72];
    char cidade[72];
    char uf[72];
    char sigla[2];
    char cep[8];
    char lixo[2];
};

int comparaEndereco(const void *e1, const void *e2) {
    return strncmp(((Endereco *)e1)->cep, ((Endereco *)e2)->cep, 8);
}

int main(){

    FILE *f, *saida;
    Endereco *e;

    char nome_arq[50];

    long tam_arq, n_registros, tam_particao, n_particao = 8;
    f = fopen("cep.dat", "r");
    fseek(f,0,SEEK_END);
    tam_arq = ftell(f);
    n_registros = tam_arq / sizeof(Endereco);

    tam_particao = (n_registros/n_particao) + 1;

    int i = 0;
    fseek(f, 0, SEEK_SET);

    while(i < n_particao ){
        printf("Dividindo...\t");
        e = (Endereco*)malloc(sizeof(Endereco) * tam_particao);

        if(!fread(e, sizeof(Endereco), tam_particao, f) == tam_particao){
            printf("Erro na hora de particionar");
        }

        qsort(e, tam_particao, sizeof(Endereco), comparaEndereco);

        
        sprintf(nome_arq, "cep_%d.dat", i);
        saida = fopen(nome_arq, "w");

        fwrite(e, sizeof(Endereco), tam_particao, saida);

        fclose(saida);

        free(e);
        i++;

    }
    
    printf("Vou abrir e ler os arquivos!");

    fclose(f);

    

    int total_arqs = (n_particao * 2) - 1;
    int total_intercalar = n_particao - 1;

    FILE *arq_a, *arq_b;

    Endereco *ea, *eb;

    int index_a = 0;
    int index_b = 1;


    for(int j = 0; j < total_intercalar; j++){
        printf("Vou abrir e ler os arquivos!");

        sprintf(nome_arq, "cep_%d.dat", index_a);
        arq_a = fopen(nome_arq, "r");
        sprintf(nome_arq, "cep_%d.dat", index_b);
        arq_b = fopen(nome_arq, "r");
        sprintf(nome_arq, "cep_%d.dat", i);
        saida = fopen(nome_arq, "w");

        

        fread(ea, sizeof(Endereco), 1, arq_a);
        fread(eb, sizeof(Endereco), 1, arq_b);

        

        while (!feof(arq_a) && !feof(arq_b)) {
            if (comparaEndereco(&ea, &eb) < 0) {
                fwrite(&ea, sizeof(Endereco), 1, saida);
                fread(&ea, sizeof(Endereco), 1, arq_a);
            } else {
                fwrite(&eb, sizeof(Endereco), 1, saida);
                fread(&eb, sizeof(Endereco), 1, arq_b);
            }
        }

        printf("Um dos arquivos acabou!");

        while (!feof(arq_a)) {
            fwrite(&ea, sizeof(Endereco), 1, saida);
            fread(&ea, sizeof(Endereco), 1, arq_a);
        }
        while (!feof(arq_b)) {
            fwrite(&eb, sizeof(Endereco), 1, saida);
            fread(&eb, sizeof(Endereco), 1, arq_b);
        }

        fclose(arq_a);
        fclose(arq_b);
        fclose(saida);

        index_a += 2;
        index_b += 2;
        i++;
    }
    
    return 0;
}