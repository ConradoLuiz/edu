import matplotlib.pyplot as plt

f = open("teste.txt","rb")

lines = f.readlines()
chars = []
qtd = []
for line in lines:
    try:
        split = line.decode('ascii')
        if len(split) == 2:
            chars.append(split[0])
            qtd.append(split[1])
    except:
        print("Nao deu esse char")
    
print(chars)

# plt.plot(chars,qtd)
# plt.show()

