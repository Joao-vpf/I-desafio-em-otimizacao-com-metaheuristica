def remover_primeira_linha(nome_arquivo):
    with open(nome_arquivo, 'r') as arquivo:
        linhas = arquivo.readlines()
    
    with open(nome_arquivo, 'w') as arquivo:
        for linha in linhas:
            arquivo.write(' '.join(linha.split()[1:]) + '\n')
        
remover_primeira_linha("dataset/uy734.txt")