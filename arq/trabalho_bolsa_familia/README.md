# Trabalho operação de conjunto com bolsa familia
### por Conrado Luiz e Luíza Guedes

* Nós usamos uma biblioteca de árvore B+ que achamos no github e fizer algumas alterações no código para ela funcionar.

* Salvamos a ávore criada com os indexes na memória usando o _Pickle_, que é uma biblioteca do python parecida com o Marshal. Ela serve para salvar objetos na memória.

### -----------------------------------------------------------------------------------------------------------

* 1 - Para fazer o index, nó utilizamos o arquivo de bolsa que estava lá no dropbox. A linha dele era assim:
 BA	3389	BROTAS DE MACAUBAS	08	244	1335	8442	**_00016074176737_**	FLAVIANO SEBASTIAO DOS SANTOS	CAIXA - Programa Bolsa Família	131.00	08/2017
 
## O NIS tem 14 digitos, os 3 primeiros digitos são Zeros e ele está na *SÉTIMA* coluna(contando do zero).
### -----------------------------------------------------------------------------------------------------------

* 2 - Para fazer a operação de conjunto, nós baixamos um arquivo do bolsa familia do site do governo, porém a linha dele estava assim:

"201901";"201801";"AL";"2835";"PIACABUCU";**_"20312719439"_**;"JAQUELINE ALVES DOS SANTOS";"89,00"

## O NIS tem 11 digitos, os 3 primeiros digitos NÃO são Zeros, ele está na *QUINTA* coluna(contando do zero), e *entre aspas*.
### Além do csv estar dividido com ;(ponto e virgula) em vez de \t.

### -----------------------------------------------------------------------------------------------------------

## Por essas razões, na hora de abrir o segundo arquivo e buscar se o NIS estava na arvore, foi preciso fazer algumas modificações.

```python
for line in f_in:
		campos = line.split(";")
		campos = list(map(lambda x: x.strip('"'), campos))
		if tree.retrieve("000"+campos[5]):
			f_out.write(line)
```

* Primeiro foi necessário repartir a linha do csv pelo **;**(ponto e virgula)
* Depois foi preciso retirar as **"**(aspas) de todos os campos
* Na hora de buscar ele na árvore, foi necessário adicionar os 3 Zeros na frente

### Só assim foi possível fazer com que a operação de conjunto funcionasse corretamente.
