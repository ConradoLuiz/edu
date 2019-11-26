import pickle

with open("meu-hash.pickle", "rb") as f_pickle:
	meu_hash = pickle.load(f_pickle)


with open("bolsa10 - 2.csv", "r")  as f_in, open("bolsa4.csv", "w") as f_out:
	header = f_in.readline()
	f_out.write(header)
	for line in f_in:
		campos = line.split("\t")
		if campos[7] in meu_hash:
			f_out.write(line)