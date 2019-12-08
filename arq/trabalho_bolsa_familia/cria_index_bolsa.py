import os
import pickle
from bptree import BPlusTree

# LEIA O README

arquivo_indexar = "bolsa.csv"
tree = BPlusTree(order=300)
with open(arquivo_indexar, "r") as f:
	lenght = f.seek(0,2)
	f.seek(0,0)
	line = f.readline() # ler a header do csv
	while line:
		num_linha = f.tell()
		line = f.readline()
		campos = line.split("\t")
		if len(campos) > 1:
			tree.insert(campos[7], num_linha)
		percent = round(((num_linha/lenght) * 100), 5)
		if percent % 0.2 == 0:
			print(f"{percent}% lido")
		
with open("bpt_index.pickle", "wb") as f_pickle:
	pickle.dump(tree, f_pickle)
