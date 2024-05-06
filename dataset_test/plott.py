import re
import matplotlib.pyplot as plt

# Função para extrair os valores do texto
def extrair_valores(texto):
    # Expressões regulares para encontrar os valores
    teste_pattern = r"Teste (\d+):"
    tempo_pattern = r"Elapsed Time: (\d+\.\d+) seconds"
    mae_pattern = r"MAE: (\d+\.\d+)"
    mse_pattern = r"MSE: ([\d+\.]+e?-?\d+)"
    r2_pattern = r"R2: (\d+\.\d+)"

    # Procura por padrões no texto
    teste_match = re.search(teste_pattern, texto)
    tempo_match = re.findall(tempo_pattern, texto)
    mae_match = re.findall(mae_pattern, texto)
    mse_match = re.findall(mse_pattern, texto)
    r2_match = re.findall(r2_pattern, texto)

    # Se não encontrar algum valor, retorna None
    if teste_match is None or tempo_match is None or mae_match is None or mse_match is None or r2_match is None:
        return None

    # Extrai os valores encontrados
    teste = int(teste_match.group(1))
    tempos = [float(tempo) for tempo in tempo_match]
    maes = [float(mae) for mae in mae_match]
    mses = [float(mse) for mse in mse_match]
    r2s = [float(r2) for r2 in r2_match]

    return teste, tempos, maes, mses, r2s

# Função para plotar os gráficos de tempos de execução
def plotar_grafico_tempo(testes, tempos, populacao):
    plt.figure(figsize=(10, 6))
    for i, (teste, tempo) in enumerate(zip(testes, tempos), start=1):
        plt.plot(range(1, len(tempo) + 1), tempo, label=f"Teste {teste}")

    # Calculando o tempo médio de execução
    tempos_concatenados = [tempo for lista_tempos in tempos for tempo in lista_tempos]
    media_tempo = sum(tempos_concatenados) / len(tempos_concatenados)
    plt.axhline(y=media_tempo, color='r', linestyle='--', label=f"Tempo médio: {media_tempo:.2f} s")

    plt.xlabel("Execução")
    plt.ylabel("Tempo (segundos)")
    plt.title("Tempos de Execução por Teste")
    plt.xticks(range(1, max(len(tempo) for tempo in tempos) + 1))
    plt.grid(True)
    plt.legend()

    plt.savefig("tempos_execucao.png")
    plt.close()

# Função para plotar os gráficos das métricas (MAE, MSE e R2)
def plotar_grafico_metricas(teste, maes, mses, r2s):
    plt.figure(figsize=(10, 6))
    plt.plot(maes, label="MAE", marker='o')
    plt.plot(mses, label="MSE", marker='o')
    plt.plot(r2s, label="R2", marker='o')

    # Calculando as médias das métricas
    media_mae = sum(maes) / len(maes) if maes else 0
    media_mse = sum(mses) / len(mses) if mses else 0
    media_r2 = sum(r2s) / len(r2s) if r2s else 0

    # Plotando as linhas das médias
    plt.axhline(y=media_mae, color='r', linestyle='--', label=f"MAE médio: {media_mae:.2f}")
    plt.axhline(y=media_mse, color='g', linestyle='--', label=f"MSE médio: {media_mse:.2f}")
    plt.axhline(y=media_r2, color='b', linestyle='--', label=f"R2 médio: {media_r2:.2f}")

    plt.xlabel("Execução")
    plt.ylabel("Valor")
    plt.title(f"Teste {teste} - MAE, MSE, R2")
    plt.grid(True)
    plt.legend()

    plt.savefig(f"teste_{teste}_metricas.png")
    plt.close()


# Texto fornecido
texto = """
Teste 1:
Elapsed Time: 5.95097 seconds
Fit: 6734.03
path: 23 21 24 25 22 19 14 12 8 11 10 16 18 17 15 7 6 5 4 2 3 1 0 9 13 20 28 29 31 34 36 37 32 33 35 30 26 27
MAE: 78.0304
MSE: 6088.74
R2: 0.999866

Elapsed Time: 5.88583 seconds
Fit: 6710.34
path: 32 17 33 23 9 11 1 20 8 15 28 0 13 18 26 5 27 25 29 31 12 6 21 35 36 2 30 3 34 10 4 16 24 37 7 14 19 22
MAE: 54.3374
MSE: 2952.56
R2: 0.999934

Elapsed Time: 6.12113 seconds
Fit: 6659.43
path: 8 11 10 18 17 16 15 12 14 19 22 25 24 21 23 27 26 30 35 33 32 37 36 34 31 29 28 20 13 9 0 1 3 2 4 5 6 7
MAE: 3.43153
MSE: 11.7754
R2: 1

Elapsed Time: 5.93696 seconds
Fit: 6722.82
path: 29 28 20 13 9 0 1 3 2 4 5 6 7 8 17 18 16 15 10 11 12 14 19 22 25 24 21 23 27 26 30 35 33 32 37 36 34 31
MAE: 66.8202
MSE: 4464.93
R2: 0.999901

Elapsed Time: 5.98609 seconds
Fit: 6809.73
path: 2 5 6 7 15 17 18 16 10 11 8 12 14 19 22 25 24 21 23 27 26 30 35 33 32 37 36 34 31 29 28 20 13 9 0 1 3 4
MAE: 153.729
MSE: 23632.5
R2: 0.99949

Teste 2:
Elapsed Time: 10.9385 seconds
Fit: 6659.43
path: 6 7 8 11 10 18 17 16 15 12 14 19 22 25 24 21 23 27 26 30 35 33 32 37 36 34 31 29 28 20 13 9 0 1 3 2 4 5
MAE: 3.43153
MSE: 11.7754
R2: 1

Elapsed Time: 11.662 seconds
Fit: 6659.43
path: 30 26 27 23 21 24 25 22 19 14 12 15 16 17 18 10 11 8 7 6 5 4 2 3 1 0 9 13 20 28 29 31 34 36 37 32 33 35
MAE: 3.43153
MSE: 11.7754
R2: 1

Elapsed Time: 11.636 seconds
Fit: 6659.43
path: 4 5 6 7 8 11 10 18 17 16 15 12 14 19 22 25 24 21 23 27 26 30 35 33 32 37 36 34 31 29 28 20 13 9 0 1 3 2
MAE: 3.43153
MSE: 11.7754
R2: 1

Elapsed Time: 11.643 seconds
Fit: 6659.43
path: 22 19 14 12 15 16 17 18 10 11 8 7 6 5 4 2 3 1 0 9 13 20 28 29 31 34 36 37 32 33 35 30 26 27 23 21 24 25
MAE: 3.43153
MSE: 11.7754
R2: 1

Elapsed Time: 11.6499 seconds
Fit: 6659.43
path: 10 11 8 7 6 5 4 2 3 1 0 9 13 20 28 29 31 34 36 37 32 33 35 30 26 27 23 21 24 25 22 19 14 12 15 16 17 18
MAE: 3.43153
MSE: 11.7754
R2: 1

Teste 3:
Elapsed Time: 17.7187 seconds
Fit: 6659.43
path: 32 37 36 34 31 29 28 20 13 9 0 1 3 2 4 5 6 7 8 11 10 18 17 16 15 12 14 19 22 25 24 21 23 27 26 30 35 33
MAE: 3.43153
MSE: 11.7754
R2: 1

Elapsed Time: 17.9412 seconds
Fit: 6659.43
path: 5 6 7 8 11 10 18 17 16 15 12 14 19 22 25 24 21 23 27 26 30 35 33 32 37 36 34 31 29 28 20 13 9 0 1 3 2 4
MAE: 3.43153
MSE: 11.7754
R2: 1

Elapsed Time: 17.621 seconds
Fit: 6659.43
path: 11 8 7 6 5 4 2 3 1 0 9 13 20 28 29 31 34 36 37 32 33 35 30 26 27 23 21 24 25 22 19 14 12 15 16 17 18 10
MAE: 3.43153
MSE: 11.7754
R2: 1

Elapsed Time: 17.6095 seconds
Fit: 6659.43
path: 5 6 7 8 11 10 18 17 16 15 12 14 19 22 25 24 21 23 27 26 30 35 33 32 37 36 34 31 29 28 20 13 9 0 1 3 2 4
MAE: 3.43153
MSE: 11.7754
R2: 1

Elapsed Time: 17.5434 seconds
Fit: 6659.43
path: 14 12 15 16 17 18 10 11 8 7 6 5 4 2 3 1 0 9 13 20 28 29 31 34 36 37 32 33 35 30 26 27 23 21 24 25 22 19
MAE: 3.43153
MSE: 11.7754
R2: 1
"""

# População para cada teste
populacao = {1: 31, 2: 67, 3: 103}

# Dividindo o texto em partes separadas para cada teste
testes = texto.split("Teste")

# Inicializando listas vazias para armazenar os tempos de execução de cada teste e as métricas de cada teste
tempos_por_teste = [[] for _ in range(len(testes)-1)]
maes_por_teste = [[] for _ in range(len(testes)-1)]
mses_por_teste = [[] for _ in range(len(testes)-1)]
r2s_por_teste = [[] for _ in range(len(testes)-1)]
testes_num = []

# Iterando sobre cada parte do texto
for i, parte in enumerate(testes[1:], start=1):
    # Extrai os valores de cada parte
    valores = extrair_valores("Teste" + parte)

    # Se os valores forem extraídos com sucesso, armazenar os tempos de execução, métricas e o número do teste
    if valores:
        teste, tempos, maes, mses, r2s = valores
        tempos_por_teste[i-1] = tempos
        maes_por_teste[i-1] = maes
        mses_por_teste[i-1] = mses
        r2s_por_teste[i-1] = r2s
        testes_num.append(teste)

# Plotando o gráfico dos tempos de execução
plotar_grafico_tempo(testes_num, tempos_por_teste, populacao)

# Iterando sobre cada teste e plotando os gráficos das métricas
for teste, tempos, maes, mses, r2s in zip(testes_num, tempos_por_teste, maes_por_teste, mses_por_teste, r2s_por_teste):
    plotar_grafico_metricas(teste, maes, mses, r2s)

print("Gráficos gerados com sucesso!")
