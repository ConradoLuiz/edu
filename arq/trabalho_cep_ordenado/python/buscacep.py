import sys
import struct

def main():

    registro = struct.Struct("72s72s72s72s2s8s2s")
    cep_column = 5
    cepPesq = int(sys.argv[1])

    print ("Tamanho da Estrutura: %d" % registro.size)

    with open("cep_ordenado.dat", "rb") as f:

        inicio = 0

        f.seek(0, 2) # Chamando com (*, 2) pq 2 significa SEEK_END
        f_size = f.tell()
        fim = int(f_size/registro.size)

        i = 0
        f.seek(0, 0)
        achou = False

        while inicio <= fim and not achou:
            i += 1

            meio = int((inicio+fim)/2)

            f.seek(meio * 300, 0) # Chamando com (*, 0) pq 0 significa SEEK_SET
            linha = f.read(registro.size)

            endereco = registro.unpack(linha)

            cep = int(endereco[cep_column])

            if cep == cepPesq:
                achou = True
                print("\nCEP encontrado!\n")
                for att in endereco:
                    print(str(att, 'latin1'))

            elif cep > cepPesq:
                fim = meio - 1
            else:
                inicio = meio + 1
        
        if not achou:
            print ("O CEP nao foi encontrado!")
        
        print ("Numero de comparacoes:", i)



        

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print ("Passar apenas o CEP como argumento!")
        quit()
    main()