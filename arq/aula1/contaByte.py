import sys

def main():
    
    with open(sys.argv[1]) as fname:
        data = fname.read()
        tam = len(data)
        count_linhas = 0
        for c in data:
            if c == "\n":
                count_linhas += 1
        
        print("O arquivo tem %d bytes e pula linha %d vezes" % (tam, count_linhas))


if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Passar nome do arquivo como argumento!")
        exit()
    main()