import pickle
from bptree import BPlusTree

# LEIA O README

with open("bpt_index.pickle", "rb") as f_pickle:
	print("Carregando index...")
	tree = pickle.load(f_pickle)
	print("Index carregado!")


with open("BolsaFamilia_Pagamentos.csv", "r")  as f_in, open("intersecao_bolsa.csv", "w") as f_out:
	header = f_in.readline()
	f_out.write(header)
	i = 0
	for line in f_in:
		campos = line.split(";")
		campos = list(map(lambda x: x.strip('"'), campos))
		if tree.retrieve("000"+campos[5]):
			f_out.write(line)
			i += 1
			print(f"Total escritos no novo arquivo: {i}")