# Instancia:

# Configurações de Teste:

## Teste 1:

```plaintext
genetic
genetic.cross_active.BCR 10
genetic.cross_active.ER 1
genetic.cross_active.VR 1
genetic.P_limiar 10
genetic.P_value  20
genetic.tx_elite 20
genetic.opt_range 80
genetic.opt_path_swap_it 100
genetic.max_population 31
genetic.max_generations 500
genetic.alpha 10
genetic.fix_init -1
genetic.verbose 0
genetic.simple_verbose 1
end
grasp
grasp.l 100
end
aco
aco.verbose 0
aco.alpha 1
aco.beta 2
aco.decay 0.07
aco.max_generations 50
end
annealing
end
abc
abc.cycles_limit 50
end
MAE
MSE
R^2
output_markdown
```

## Teste 2:

```plaintext
genetic
genetic.cross_active.BCR 10
genetic.cross_active.ER 1
genetic.cross_active.VR 1
genetic.P_limiar 10
genetic.P_value  20
genetic.tx_elite 20
genetic.opt_range 80
genetic.opt_path_swap_it 100
genetic.max_population 67
genetic.max_generations 500
genetic.alpha 10
genetic.fix_init -1
genetic.verbose 0
genetic.simple_verbose 1
end
grasp
grasp.l 100
end
aco
aco.verbose 0
aco.alpha 1
aco.beta 2
aco.decay 0.07
aco.max_generations 50
end
annealing
end
abc
abc.cycles_limit 50
end
MAE
MSE
R^2
output_markdown
```

# Teste 3:

```plaintext
genetic
genetic.cross_active.BCR 10
genetic.cross_active.ER 1
genetic.cross_active.VR 1
genetic.P_limiar 10
genetic.P_value  20
genetic.tx_elite 20
genetic.opt_range 80
genetic.opt_path_swap_it 100
genetic.max_population 103
genetic.max_generations 500
genetic.alpha 10
genetic.fix_init -1
genetic.verbose 0
genetic.simple_verbose 1
end
grasp
grasp.l 100
end
aco
aco.verbose 0
aco.alpha 1
aco.beta 2
aco.decay 0.07
aco.max_generations 50
end
annealing
end
abc
abc.cycles_limit 50
end
MAE
MSE
R^2
output_markdown
```

# Resultados optidos:

## Teste 1:

**Elapsed Time:** 14.1729 seconds <br>
**Fit:** 7774.24 <br>
**path:** 45 43 33 34 35 48 0 22 19 49 15 28 29 1 6 41 20 16 2 17 30 21 31 44 18 40 7 8 9 42 32 50 10 51 13 12 46 25 26 27 11 24 3 5 14 4 23 47 37 39 38 36  <br>
**MAE:** 229.876 <br>
**MSE:** 52843.2 <br>
**R2:** 0.999126 <br>

**Elapsed Time:** 14.1703 seconds <br>
**Fit:** 7974.62 <br>
**path:** 46 1 18 23 48 20 31 2 13 32 33 50 47 25 51 6 9 37 0 24 34 22 21 40 49 15 17 30 28 45 38 3 14 35 7 5 42 43 41 19 27 26 8 12 16 10 44 4 11 39 29 36  <br>
**MAE:** 430.25 <br>
**MSE:** 185115 <br>
**R2:** 0.997089 <br>

**Elapsed Time:** 13.8118 seconds <br>
**Fit:** 7661.01 <br>
**path:** 19 31 1 35 28 10 50 16 44 46 32 15 42 4 47 7 29 30 38 8 17 41 40 39 48 49 33 27 36 18 51 43 20 26 34 12 14 21 3 22 45 37 25 2 13 5 24 11 23 0 6 9  <br>
**MAE:** 116.647 <br>
**MSE:** 13606.6 <br>
**R2:** 0.999768 <br>

**Elapsed Time:** 13.9207 seconds <br>
**Fit:** 7544.37 <br>
**path:** 47 39 50 41 31 34 44 42 3 25 21 26 20 23 24 38 12 16 18 19 0 33 40 10 45 15 8 7 37 49 30 22 1 48 51 29 46 28 35 43 4 14 13 5 9 11 32 6 27 17 36 2  <br>
**MAE:** 1.90409e-006 <br>
**MSE:** 3.62555e-012 <br>
**R2:** 1 <br>

**Elapsed Time:** 14.0839 seconds <br>
**Fit:** 7816.43 <br>
**path:** 13 23 29 16 31 43 1 3 2 47 26 50 48 19 34 22 5 44 18 6 46 45 51 10 17 8 28 12 35 38 41 37 24 20 11 30 40 21 0 15 27 7 4 39 14 49 36 33 32 42 9 25  <br>
**MAE:** 272.062 <br>
**MSE:** 74017.6 <br>
**R2:** 0.998789 <br>

## Teste 2:

**Elapsed Time:** 24.4097 seconds <br>
**Fit:** 8353.29 <br>
**path:** 9 35 40 42 44 38 36 41 34 23 45 17 15 25 27 49 7 29 32 19 1 16 43 50 48 18 21 5 10 33 39 30 20 14 31 47 13 22 12 8 11 51 4 6 37 46 24 3 26 0 2 28  <br>
**MAE:** 808.929 <br>
**MSE:** 654366 <br>
**R2:** 0.990622 <br>

**Elapsed Time:** 24.4022 seconds <br>
**Fit:** 7729.5 <br>
**path:** 7 42 29 14 34 10 33 19 16 21 39 0 4 40 17 32 20 23 43 27 38 51 45 1 12 46 28 15 8 26 36 11 3 35 6 24 30 25 50 13 18 44 41 2 49 31 22 5 48 37 9 47  <br>
**MAE:** 185.135 <br>
**MSE:** 34274.9 <br>
**R2:** 0.999426 <br>

**Elapsed Time:** 24.4022 seconds <br>
**Fit:** 7729.5 <br>
**path:** 7 42 29 14 34 10 33 19 16 21 39 0 4 40 17 32 20 23 43 27 38 51 45 1 12 46 28 15 8 26 36 11 3 35 6 24 30 25 50 13 18 44 41 2 49 31 22 5 48 37 9 47  <br>
**MAE:** 185.135 <br>
**MSE:** 34274.9 <br>
**R2:** 0.999426 <br>

**Elapsed Time:** 24.0499 seconds <br>
**Fit:** 7893.01 <br>
**path:** 44 16 38 2 24 4 15 12 30 17 36 7 35 20 6 33 25 40 51 37 31 8 26 22 23 27 11 43 47 0 34 5 50 28 48 45 39 18 21 41 42 19 1 32 10 3 13 29 49 46 14 9  <br>
**MAE:** 348.64 <br>
**MSE:** 121550 <br>
**R2:** 0.998049 <br>

**Elapsed Time:** 24.4152 seconds <br>
**Fit:** 7544.37 <br>
**path:** 47 2 12 41 51 3 48 0 25 19 1 34 29 45 13 27 9 30 32 10 28 8 23 42 16 5 44 46 36 22 24 49 20 31 7 14 21 26 6 17 35 40 43 38 15 50 33 4 39 18 37 11  <br>
**MAE:** 1.90409e-006 <br>
**MSE:** 3.62555e-012 <br>
**R2:** 1 <br>

## Teste 3:

**Elapsed Time:** 35.1988 seconds <br>
**Fit:** 7880.59 <br>
**path:** 28 15 45 43 33 34 35 48 31 38 39 36 37 47 23 4 14 5 3 24 11 27 26 25 46 12 13 51 10 50 32 42 9 8 7 40 18 44 2 16 20 41 6 1 29 22 30 17 21 0 19 49  <br>
**MAE:** 336.224 <br>
**MSE:** 113047 <br>
**R2:** 0.99818 <br>

**Elapsed Time:** 35.7595 seconds <br>
**Fit:** 7777.33 <br>
**path:** 4 9 26 20 38 40 22 46 16 45 44 50 18 32 21 33 3 15 25 42 39 6 24 8 28 31 0 23 7 1 43 36 34 5 47 14 17 49 37 12 2 13 29 10 41 30 11 19 27 51 35 48  <br>
**MAE:** 232.966 <br>
**MSE:** 54273.3 <br>
**R2:** 0.999103 <br>

**Elapsed Time:** 35.8463 seconds <br>
**Fit:** 7969.94 <br>
**path:** 19 49 29 1 6 41 20 16 2 44 18 40 7 8 9 32 42 3 24 11 50 10 51 13 12 26 27 25 46 28 15 43 45 47 23 4 5 14 37 36 39 38 33 34 35 48 31 0 21 17 30 22  <br>
**MAE:** 425.574 <br>
**MSE:** 181113 <br>
**R2:** 0.997149 <br>

**Elapsed Time:** 35.8589 seconds <br>
**Fit:** 7816.43 <br>
**path:** 36 50 26 32 15 11 20 42 43 16 7 19 51 3 0 48 28 21 45 23 14 49 22 46 27 31 8 38 40 2 10 18 5 1 12 25 41 34 24 39 37 30 13 9 6 44 35 17 33 29 47 4  <br>
**MAE:** 272.062 <br>
**MSE:** 74017.6 <br>
**R2:** 0.998789 <br>

**Elapsed Time:** 35.5488 seconds <br>
**Fit:** 8054.73 <br>
**path:** 13 12 26 27 25 46 28 29 1 6 41 20 16 2 17 30 21 0 34 33 43 22 19 49 15 45 47 23 4 5 14 37 36 39 38 35 48 31 44 18 40 7 8 9 32 42 3 24 11 50 10 51  <br>
**MAE:** 510.366 <br>
**MSE:** 260474 <br>
**R2:** 0.995985 <br>
