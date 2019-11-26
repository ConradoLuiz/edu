import os
import pickle

arquivo_indexar = "bolsa10.csv"
meu_hash = {}
with open(arquivo_indexar, "r") as f:
	lenght = f.seek(0,2)
	f.seek(0,0)
	line = f.readline() # ler a header do csv
	
	while line:
		num_linha = f.tell()
		line = f.readline()
		campos = line.split("\t")
		if len(campos) > 1:
			meu_hash[campos[7]] = num_linha
		percent = ((num_linha/lenght) * 100)
		print(f"{percent:.2f}% lido")
		


with open("meu-hash.pickle", "wb") as f_pickle:
	pickle.dump(meu_hash, f_pickle)
