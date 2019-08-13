import sys

def main():
    
    with open(sys.argv[1]) as fname:
        data = fname.read()
        tam = len(data)

        print(tam)


if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Passar nome do arquivo como argumento!")
        exit()
    main()