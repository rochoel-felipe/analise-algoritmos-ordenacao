# Análise Comparativa de Algoritmos de Ordenação

Repositório do artigo **"Análise Comparativa de Desempenho de Algoritmos de Ordenação em Diferentes Cenários de Entrada"**, submetido como trabalho acadêmico da disciplina de Estruturas de Dados 2 da Universidade Tecnológica Federal do Paraná (UTFPR) — Campus Apucarana.

**Autor:** Felipe Rochoel Costa  
**Contato:** feliperochoelcosta@alunos.utfpr.edu.br

---

## Algoritmos Avaliados

| Algoritmo | Complexidade (médio) | Complexidade (pior) | In-place |
|---|---|---|---|
| Bubble Sort | O(n²) | O(n²) | ✅ |
| Merge Sort  | O(n log n) | O(n log n) | ❌ |
| Quick Sort  | O(n log n) | O(n²) | ✅ |

---

## Estrutura do Repositório

```
analise-algoritmos-ordenacao/
├── src/
│   └── analise_algoritmos.c      # Implementação dos três algoritmos em C
├── data/
│   ├── README.md                 # Descrição das colunas e dos cenários
│   ├── resultados_rodada_1.csv   # Rodada 1 (descartada — versão anterior do código)
│   ├── resultados_rodada_2.csv   # Rodada 2 (válida)
│   ├── resultados_rodada_3.csv   # Rodada 3 (válida)
│   └── resultados_rodada_4.csv   # Rodada 4 (válida) — re-execução corretiva
├── docs/
│   ├── artigo.pdf                # Artigo completo compilado
│   └── artigo.tex                # Código-fonte LaTeX do artigo
├── .gitignore
├── LICENSE.txt
└── README.md                     # Este arquivo
```

---

## Como Compilar e Executar

### Pré-requisitos
- GCC (MinGW no Windows, ou gcc nativo no Linux/macOS)
- Memória RAM disponível ≥ 2 GB (para N = 1.000.000)

### Compilação
```bash
gcc -O2 -o analise src/analise_algoritmos.c
```

### Execução
```bash
./analise
```

Os resultados serão exibidos no terminal e salvos em `data/resultados_rodada_N.csv`.

---

## Ambiente de Testes

| Componente | Especificação |
|---|---|
| Processador | AMD Ryzen 5 5600G (3,90 GHz) |
| Memória RAM | 16 GB DDR4 |
| Sistema Operacional | Windows 11 Pro 64 bits (versão 24H2) |
| Compilador | GCC (MinGW) via Visual Studio Code |

---

## Cenários e Tamanhos Testados

- **Listas Aleatórias** — semente fixa `srand(42)` para reprodutibilidade
- **Listas Inversamente Ordenadas** — pior caso do Bubble Sort e do Quick Sort (pivô fixo)
- **Listas Quase Ordenadas** — ~2% dos elementos com posições permutadas

| Tamanho (n) | Bubble Sort | Merge Sort | Quick Sort |
|---|---|---|---|
| 10.000 | ✅ | ✅ | ✅ |
| 100.000 | ✅ | ✅ | ✅ |
| 500.000 | ✅ | — | — |
| 1.000.000 | ❌ (quadrático) | ✅ | ✅ |

> O Bubble Sort foi limitado a N = 500.000 para evitar tempo de execução inviável.  
> O Quick Sort utiliza pilha de 64 MB alocada dinamicamente.

---

## Sobre os Dados (`data/`)

As métricas de **comparações** e **trocas** são determinísticas (idênticas entre rodadas).  
Os **tempos** representam a média aritmética das rodadas 2, 3 e 4.  
A rodada 1 foi descartada por ter sido coletada com uma versão anterior do código.

Veja `data/README.md` para descrição detalhada das colunas dos arquivos CSV.

---

## Referências

- Cormen, T. H. et al. *Algoritmos: Teoria e Prática*. Elsevier, 3ª ed., 2012.
- Knuth, D. E. *The Art of Computer Programming, Vol. 3: Sorting and Searching*. Addison-Wesley, 2ª ed., 1998.
