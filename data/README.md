# Dados dos Experimentos

Este diretório contém os resultados brutos das execuções dos experimentos de ordenação.

---

## Arquivos

| Arquivo | Status | Observação |
|---|---|---|
| `resultados_rodada_1.csv` | ✅ Válido | |
| `resultados_rodada_2.csv` | ✅ Válido | |
| `resultados_rodada_3.csv` | ✅ Válido | |

As médias publicadas no artigo foram calculadas **apenas sobre as rodadas 2, 3 e 4**.

---

## Formato das Colunas

| Coluna | Tipo | Descrição |
|---|---|---|
| `Cenário` | string | `Listas Aleatórias`, `Listas Inversas` ou `Listas Quase Ordenadas` |
| `Algoritmo` | string | `Bubble Sort`, `Merge Sort` ou `Quick Sort` |
| `N` | inteiro | Tamanho do vetor testado |
| `Tempo_ms` | float | Tempo de execução em milissegundos |
| `Comparações` | inteiro | Número total de comparações de chaves realizadas |
| `Trocas` | inteiro | Número total de trocas de posição realizadas |

---

## Notas Importantes

- **Comparações e Trocas são determinísticas:** para uma mesma entrada, esses valores são idênticos em todas as rodadas. Qualquer divergência indica entrada diferente ou bug no código.
- **Tempos variam entre rodadas:** dependem do estado do sistema operacional, processos em background e cache de CPU. Use sempre a média de múltiplas rodadas.
- **Bubble Sort limitado a N = 500.000:** para N = 1.000.000, o tempo estimado excede 30 minutos.
- **Quick Sort requer pilha de 64 MB:** alocada dinamicamente no código para suportar N = 1.000.000 no pior caso sem stack overflow.
- **Semente aleatória fixa:** `srand(42)` garante que as listas aleatórias sejam idênticas entre rodadas.
