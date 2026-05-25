#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h> 

// Variáveis globais para contagem empírica
unsigned long long comparacoes = 0;
unsigned long long trocas = 0;

// --- ALGORITMOS DE ORDENAÇÃO ---

// --- BUBBLE SORT ---
void bubbleSort(int *arr, int n) {
    comparacoes = 0;
    trocas = 0;
    for (int i = 0; i < n - 1; i++) {
        int trocou = 0;
        for (int j = 0; j < n - i - 1; j++) {
            comparacoes++;
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                trocas++;
                trocou = 1;
            }
        }
        if (!trocou) break; // Vetor já ordenado prematuramente
    }
}

// --- MERGE SORT ---
void merge(int *arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        comparacoes++;
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        trocas++;// Contabilizado como movimentação/cópia de elemento
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++; k++; trocas++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++; k++; trocas++;
    }

    free(L);
    free(R);
}

void mergeSort(int *arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

// --- QUICK SORT (PIVÔ NO PRIMEIRO ELEMENTO - CONFORME MODELO DIDÁTICO) ---
int partition(int *arr, int low, int high) {
    int pivot = arr[low]; // Pivô definido rigidamente no primeiro elemento
    int i = low;

    for (int j = low + 1; j <= high; j++) {
        comparacoes++;
        if (arr[j] < pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            trocas++;
        }
    }
    int temp = arr[low];
    arr[low] = arr[i];
    arr[i] = temp;
    trocas++;
    return i;
}

void quickSort(int *arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// --- GERADORES DE CENÁRIOS ---
void gerarAleatorio(int *arr, int n) {
    srand(42); // Semente fixa para garantir igualdade de condições entre os algoritmos
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % (n * 10);
    }
}

void gerarInverso(int *arr, int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = n - i;
    }
}

void gerarQuaseOrdenado(int *arr, int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = i;
    }
    // Desordena levemente (cerca de 2% dos elementos)
    srand(42);
    for (int k = 0; k < n / 50; k++) {
        int idx1 = rand() % n;
        int idx2 = rand() % n;
        int temp = arr[idx1];
        arr[idx1] = arr[idx2];
        arr[idx2] = temp;
    }
}

// --- FUNÇÃO PRINCIPAL DE TESTES ---
void executarTeste(const char *nomeAlgoritmo, void (*funcaoSort)(int*, int), int *original, int n) {
    int *copia = (int *)malloc(n * sizeof(int));
    if (copia == NULL) {
        printf("Erro de alocação de memória!\n");
        return;
    }
    memcpy(copia, original, n * sizeof(int));

    comparacoes = 0;
    trocas = 0;

    clock_t start = clock();
    funcaoSort(copia, n);
    clock_t end = clock();

    double tempo_ms = ((double)(end - start) / CLOCKS_PER_SEC) * 1000.0;

    printf("%-15s | N = %7d | Tempo: %10.2f ms | Comparações: %12llu | Trocas: %12llu\n", 
           nomeAlgoritmo, n, tempo_ms, (unsigned long long)comparacoes, (unsigned long long)trocas);

    free(copia);
}

// Wrapper para o Merge e Quick adequarem à assinatura padrão
void mergeSortWrapper(int *arr, int n) { mergeSort(arr, 0, n - 1); }
void quickSortWrapper(int *arr, int n) { quickSort(arr, 0, n - 1); }

// --- CENTRALIZA TODA A EXECUÇÃO DENTRO DA MEMÓRIA EXPANDIDA ---
DWORD WINAPI rodarExperimentos(LPVOID lpParam) {
    int tamanhos[] = {10000, 100000, 1000000};
    int num_tamanhos = 3;

    printf("=== INICIANDO EXECUÇÃO EXPERIMENTAL ACADÊMICA ===\n");
    printf("Nota: Pilha de memoria de 64MB alocada dinamicamente via codigo para o Quick Sort.\n");
    printf("Nota 2: Para N=1.000.000, o Bubble Sort executara com N=500.000 para extrapolacao.\n\n");

    // --- CENÁRIO 1: LISTAS ALEATÓRIAS ---
    printf("--- CENÁRIO 1: LISTAS ALEATÓRIAS ---\n");
    for (int i = 0; i < num_tamanhos; i++) {
        int n = tamanhos[i];
        
        int n_bubble = (n == 1000000) ? 500000 : n;
        int *arr_bubble = (int *)malloc(n_bubble * sizeof(int));
        gerarAleatorio(arr_bubble, n_bubble);
        executarTeste("Bubble Sort", bubbleSort, arr_bubble, n_bubble);
        free(arr_bubble);

        int *arr_eficientes = (int *)malloc(n * sizeof(int));
        gerarAleatorio(arr_eficientes, n);
        executarTeste("Merge Sort", mergeSortWrapper, arr_eficientes, n);
        executarTeste("Quick Sort", quickSortWrapper, arr_eficientes, n);
        free(arr_eficientes);
    }
    printf("\n");

    // --- CENÁRIO 2: LISTAS INVERSAS ---
    printf("--- CENÁRIO 2: LISTAS INVERSAS ---\n");
    for (int i = 0; i < num_tamanhos; i++) {
        int n = tamanhos[i];
        
        int n_bubble = (n == 1000000) ? 500000 : n;
        int *arr_bubble = (int *)malloc(n_bubble * sizeof(int));
        gerarInverso(arr_bubble, n_bubble);
        executarTeste("Bubble Sort", bubbleSort, arr_bubble, n_bubble);
        free(arr_bubble);

        int *arr_eficientes = (int *)malloc(n * sizeof(int));
        gerarInverso(arr_eficientes, n);
        executarTeste("Merge Sort", mergeSortWrapper, arr_eficientes, n);
        executarTeste("Quick Sort", quickSortWrapper, arr_eficientes, n);
        free(arr_eficientes);
    }
    printf("\n");

    // --- CENÁRIO 3: LISTAS QUASE ORDENADAS ---
    printf("--- CENÁRIO 3: LISTAS QUASE ORDENADAS ---\n");
    for (int i = 0; i < num_tamanhos; i++) {
        int n = tamanhos[i];
        
        int n_bubble = (n == 1000000) ? 500000 : n;
        int *arr_bubble = (int *)malloc(n_bubble * sizeof(int));
        gerarQuaseOrdenado(arr_bubble, n_bubble);
        executarTeste("Bubble Sort", bubbleSort, arr_bubble, n_bubble);
        free(arr_bubble);

        int *arr_eficientes = (int *)malloc(n * sizeof(int));
        gerarQuaseOrdenado(arr_eficientes, n);
        executarTeste("Merge Sort", mergeSortWrapper, arr_eficientes, n);
        executarTeste("Quick Sort", quickSortWrapper, arr_eficientes, n);
        free(arr_eficientes);
    }

    printf("\n=== EXPERIMENTOS CONCLUÍDOS COM SUCESSO ===\n");
    return 0;
}

int main() {
    // Mantém a máquina ligada durante os testes
    SetThreadExecutionState(ES_CONTINUOUS | ES_SYSTEM_REQUIRED | ES_DISPLAY_REQUIRED);

    // cria a thread com 64mb de pilha para evitar crash 
    HANDLE hThread = CreateThread(NULL, 67108864, rodarExperimentos, NULL, 0, NULL);
    
    if (hThread == NULL) {
        printf("Erro fatal ao alocar memoria de execucao expandida.\n");
        return 1;
    }

    // Aguarda os experimentos finalizarem completamente antes de encerrar o programa
    WaitForSingleObject(hThread, INFINITE);
    CloseHandle(hThread);

    // Devolve o controle de energia padrão ao Windows
    SetThreadExecutionState(ES_CONTINUOUS);

    return 0;
}