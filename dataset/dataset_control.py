def converter_arquivo(nome_arquivo_entrada, nome_arquivo_saida):
    with open(nome_arquivo_entrada, 'r') as arquivo:
        linhas = arquivo.readlines()
    
    with open(nome_arquivo_saida, 'w') as arquivo:
        dimensao = None
        coordenadas = []

        for linha in linhas:
            if linha.startswith('DIMENSION'):
                dimensao = int(linha.split(':')[1])
            elif linha.startswith('NODE_COORD_SECTION'):
                for linha_coordenada in linhas[linhas.index(linha)+1:]:
                    if linha_coordenada.strip() == '':
                        break
                    partes = linha_coordenada.split()
                    coordenadas.append(' '.join(partes[1:]))
                break
        
        arquivo.write(str(dimensao) + '\n')
        for coordenada in coordenadas:
            arquivo.write(coordenada + '\n')
        
converter_arquivo("dataset/lu980.txt", "dataset/lu980.txt")