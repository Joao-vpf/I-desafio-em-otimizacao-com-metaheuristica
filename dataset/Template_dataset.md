# Template do conjunto de dados

O conjunto de dados deve seguir a seguinte estrutura:

## Número de cidades:

Indica a quantidade de cidades ou pontos no conjunto de dados.

## Pontos ou cidades:

Os pontos devem estar no formato de **coordenadas cartesianas (X, Y)**.

### Linha em branco ou distância ótima:

Para os conjuntos de dados em que o caminho ótimo já foi encontrado, é possível incluir a distância final encontrada.

# Caso o dataset seja do TSPLIB Format:

## Como a seguir:

```plaintext
AME : lu980
COMMENT : 980 locations in Luxembourg
COMMENT : Derived from National Imagery and Mapping Agency data
TYPE : TSP
DIMENSION : 980
EDGE_WEIGHT_TYPE : EUC_2D
NODE_COORD_SECTION
1 49525.5556 5940.5556
2 49525.5556 5940.5556
3 49738.8889 6345.0000
4 49608.3333 6405.8333
5 49796.6667 6155.5556
6 49828.6111 5764.7222
7 49757.7778 6353.3333
8 49716.3889 6490.0000
9 49533.3333 6316.6667
...
```

É possivel usar o **dataset_control.py** que organizará os dados da forma esperada pelo programa.