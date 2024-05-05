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
```

# Resultados optidos:

## Teste 1:

**Elapsed Time:** 5.95097 seconds <br>
**Fit:** 6734.03 <br>
**path:** 23 21 24 25 22 19 14 12 8 11 10 16 18 17 15 7 6 5 4 2 3 1 0 9 13 20 28 29 31 34 36 37 32 33 35 30 26 27 <br>
**MAE:** 78.0304 <br>
**MSE:** 6088.74 <br>
**R2:** 0.999866 <br>

**Elapsed Time:** 5.88583 seconds <br>
**Fit:** 6710.34 <br>
**path:** 32 17 33 23 9 11 1 20 8 15 28 0 13 18 26 5 27 25 29 31 12 6 21 35 36 2 30 3 34 10 4 16 24 37 7 14 19 22 <br>
**MAE:** 54.3374 <br>
**MSE:** 2952.56 <br>
**R2:** 0.999934 <br>

**Elapsed Time:** 6.12113 seconds <br>
**Fit:** 6659.43 <br>
**path:** 8 11 10 18 17 16 15 12 14 19 22 25 24 21 23 27 26 30 35 33 32 37 36 34 31 29 28 20 13 9 0 1 3 2 4 5 6 7 <br>
**MAE:** 3.43153 <br>
**MSE:** 11.7754 <br>
**R2:** 1 <br>

**Elapsed Time:** 5.93696 seconds <br>
**Fit:** 6722.82 <br>
**path:** 29 28 20 13 9 0 1 3 2 4 5 6 7 8 17 18 16 15 10 11 12 14 19 22 25 24 21 23 27 26 30 35 33 32 37 36 34 31 <br>
**MAE:** 66.8202 <br>
**MSE:** 4464.93 <br>
**R2:** 0.999901 <br>

**Elapsed Time:** 5.98609 seconds <br>
**Fit:** 6809.73 <br>
**path:** 2 5 6 7 15 17 18 16 10 11 8 12 14 19 22 25 24 21 23 27 26 30 35 33 32 37 36 34 31 29 28 20 13 9 0 1 3 4 <br>
**MAE:** 153.729 <br>
**MSE:** 23632.5 <br>
**R2:** 0.99949 <br>

## Teste 2:

**Elapsed Time:** 10.9385 seconds <br>
**Fit:** 6659.43 <br>
**path:** 6 7 8 11 10 18 17 16 15 12 14 19 22 25 24 21 23 27 26 30 35 33 32 37 36 34 31 29 28 20 13 9 0 1 3 2 4 5 <br>
**MAE:** 3.43153 <br>
**MSE:** 11.7754 <br>
**R2:** 1 <br>

**Elapsed Time:** 11.662 seconds <br>
**Fit:** 6659.43 <br>
**path:** 30 26 27 23 21 24 25 22 19 14 12 15 16 17 18 10 11 8 7 6 5 4 2 3 1 0 9 13 20 28 29 31 34 36 37 32 33 35 <br>
**MAE:** 3.43153 <br>
**MSE:** 11.7754 <br>
**R2:** 1 <br>

**Elapsed Time:** 11.636 seconds <br>
**Fit:** 6659.43 <br>
**path:** 4 5 6 7 8 11 10 18 17 16 15 12 14 19 22 25 24 21 23 27 26 30 35 33 32 37 36 34 31 29 28 20 13 9 0 1 3 2 <br>
**MAE:** 3.43153 <br>
**MSE:** 11.7754 <br>
**R2:** 1 <br>

**Elapsed Time:** 11.643 seconds <br>
**Fit:** 6659.43 <br>
**path:** 22 19 14 12 15 16 17 18 10 11 8 7 6 5 4 2 3 1 0 9 13 20 28 29 31 34 36 37 32 33 35 30 26 27 23 21 24 25 <br>
**MAE:** 3.43153 <br>
**MSE:** 11.7754 <br>
**R2:** 1 <br>

**Elapsed Time:** 11.6499 seconds <br>
**Fit:** 6659.43 <br>
**path:** 10 11 8 7 6 5 4 2 3 1 0 9 13 20 28 29 31 34 36 37 32 33 35 30 26 27 23 21 24 25 22 19 14 12 15 16 17 18 <br>
**MAE:** 3.43153 <br>
**MSE:** 11.7754 <br>
**R2:** 1 <br>

## Teste 3:

**Elapsed Time:** 17.7187 seconds <br>
**Fit:** 6659.43 <br>
**path:** 32 37 36 34 31 29 28 20 13 9 0 1 3 2 4 5 6 7 8 11 10 18 17 16 15 12 14 19 22 25 24 21 23 27 26 30 35 33 <br>
**MAE:** 3.43153 <br>
**MSE:** 11.7754 <br>
**R2:** 1 <br>

**Elapsed Time:** 17.9412 seconds <br>
**Fit:** 6659.43 <br>
**path:** 5 6 7 8 11 10 18 17 16 15 12 14 19 22 25 24 21 23 27 26 30 35 33 32 37 36 34 31 29 28 20 13 9 0 1 3 2 4 <br>
**MAE:** 3.43153 <br>
**MSE:** 11.7754 <br>
**R2:** 1 <br>

**Elapsed Time:** 17.621 seconds <br>
**Fit:** 6659.43 <br>
**path:** 11 8 7 6 5 4 2 3 1 0 9 13 20 28 29 31 34 36 37 32 33 35 30 26 27 23 21 24 25 22 19 14 12 15 16 17 18 10 <br>
**MAE:** 3.43153 <br>
**MSE:** 11.7754 <br>
**R2:** 1 <br>

**Elapsed Time:** 17.6095 seconds <br>
**Fit:** 6659.43 <br>
**path:** 5 6 7 8 11 10 18 17 16 15 12 14 19 22 25 24 21 23 27 26 30 35 33 32 37 36 34 31 29 28 20 13 9 0 1 3 2 4 <br>
**MAE:** 3.43153 <br>
**MSE:** 11.7754 <br>
**R2:** 1 <br>

**Elapsed Time:** 17.5434 seconds <br>
**Fit:** 6659.43 <br>
**path:** 14 12 15 16 17 18 10 11 8 7 6 5 4 2 3 1 0 9 13 20 28 29 31 34 36 37 32 33 35 30 26 27 23 21 24 25 22 19 <br>
**MAE:** 3.43153 <br>
**MSE:** 11.7754 <br>
**R2:** 1 <br>
