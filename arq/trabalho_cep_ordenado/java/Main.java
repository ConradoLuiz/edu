import java.io.RandomAccessFile;

public class Main{

    public static void main(String[] args) throws Exception{

        if (args.length != 1){
            System.out.println("Chamar o programa passando apenas o CEP como parametro!!");
            System.exit(1);
        }

        RandomAccessFile f = new RandomAccessFile("cep_ordenado.dat", "r");
        Endereco e = new Endereco();

        String cepPes = args[0];

        boolean achou = false;

        long inicio, meio, fim;
        long tamArq;
        int tamReg = 300;

        inicio = 0;
        tamArq = f.length();
        fim = tamArq/tamReg;

        int i = 0;
        f.seek(0);

        while(inicio <= fim && !achou){
            i++;

            meio = (inicio + fim)/2;

            f.seek(meio * 300);
            e.leEndereco(f);

            if (e.getCep().equals(cepPes)){
                System.out.println(e);
                achou = true;
            }
            else{
                if(Integer.parseInt(cepPes) > Integer.parseInt(e.getCep())){
                    inicio = meio + 1;
                }
                else{
                    fim = meio - 1;
                }
            }
        }

        if (!achou){
            System.out.println("CEP nao encontrado!");
        }
        System.out.println("Numero de comparações: " + i);
    }
}