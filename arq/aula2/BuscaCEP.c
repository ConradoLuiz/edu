#include <stdio.h>
#include <string.h>
#include <ctype.h>

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

int main(int argc, char**argv)
{
	FILE *f;
	Endereco e;
	int qt;
	int c;

	if(argc != 2)
	{
		fprintf(stderr, "USO: %s [RUA]", argv[0]);
		return 1;
	}

	//saber o tamanho da string que é passada no argumento
	int tam_rua = strlen(argv[1]);

	//colocar todos os caracteres em maiusculo para comparar
	for(int i = 0; i < tam_rua; i++){
		argv[1][i] = toupper(argv[1][i]);
	}

	c = 0;
	printf("Tamanho da Estrutura: %ld\n\n", sizeof(Endereco));
	f = fopen("cep.dat","r");
	qt = fread(&e,sizeof(Endereco),1,f);
	while(qt > 0)
	{
		c++;
		
		if(strncmp(argv[1],e.logradouro,tam_rua)==0)//só é preciso comparar até o tamanho da string passada
		{
			printf("%.72s\n%.72s\n%.72s\n%.72s\n%.2s\n%.8s\n",e.logradouro,e.bairro,e.cidade,e.uf,e.sigla,e.cep);
			break;
		}
		qt = fread(&e,sizeof(Endereco),1,f);		
	}
	printf("Total Lido: %d\n", c);
	fclose(f);
}

