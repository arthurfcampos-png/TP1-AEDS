# Como rodar e compilar o código?

- Para executar o código em um sistema linux, basta digitar:

```makefile
# PRIMEIRO - para compilar
make 

# SEGUNDO - para executar 
make executar

# TERCEIRO - para limpar
make limpar
```

- Para executar o código em um sistema windows, basta digitar:

```makefile
# PRIMEIRO - para compilar
mingw32-make 

# SEGUNDO - para executar
mingw32-make executar

# TERCEIRO - para limpar
mingw32-make limpar
```
# 📖 Módulo de Leitura e Entrada (`leitura_entrada.h` / `.c`)

Fala galera! Esse aqui é o módulo que faz o trabalho sujo de abrir os arquivos de texto, limpar as palavras e arrancar as stopwords antes de mandar tudo pras nossas estruturas de dados (a Hash e a Patricia).

A ideia principal da implementação foi: **filtrar tudo logo na entrada**. A gente limpa as palavras na hora que lê, assim o programa economiza RAM, processamento e a gente evita o pesadelo de ter que ficar fazendo `malloc` à toa ou implementando remoção de nó em árvore.

## 🛠️ O que cada função faz (Resumão)

### `lerEntradaPrincipal(const char* arquivoEntrada, const char* arquivoStopWords)`
Essa é a função "chefe". Quem for montar o Menu lá na `main` só precisa chamar essa aqui e ela resolve o resto.
* **O que ela faz:**
  1. Calcula o tamanho ideal da Hash (sempre puxando pra potência de 2 mais próxima, pra evitar colisão de bobeira e não perder ponto).
  2. Carrega as stopwords pra memória.
  3. Lê o `entrada.txt` pra descobrir quantas fábulas a gente vai ter que processar.
  4. Dá o `malloc` pra guardar os IDs e nomes dos documentos.
  5. Chama o loop que manda cada fábula ser processada.

### `processarFabula(...)`
Abre o `.txt` de uma fábula específica e vai puxando palavra por palavra até chegar no fim do arquivo (`EOF`).
* **O que ela faz:** Pra cada palavra lida, ela chama a função de limpeza e checa se é stopword. Se a palavra passar no teste, ela já chama direto o `insereHash` (e depois vamos colocar o `inserePatricia` aqui também).

### `carregarStopWords(...)`
Lê o arquivo `Stopwords.txt` e guarda tudo numa matriz de `char` (`stopWords[500][50]`). Fizemos com matriz estática pra evitar ponteiro duplo e vazamento de memória com o Valgrind.

### Funções Auxiliares:
* **`limparPalavra(...)`:** Tira vírgula, ponto e joga tudo pra letra minúscula (como a professora pediu, os textos vão ficar sem acentuação e tudo minúsculo pro cálculo do TF-IDF bater certo).
* **`ehStopWord(...)`:** Bate a palavra lida com a nossa matriz de stopwords. Se retornar `1` (verdadeiro), a palavra é descartada e nem chega a pisar na Hash ou na Patricia.

---

## 🚀 Como plugar na `main.c`

Para juntar esse módulo com o resto do trabalho, é só fazer o seguinte:

**1. Dar o include lá no topo da main:**
```c
#include "leitura_entrada.h"

```C
int main() {
    // ... código do menu de vocês ...
    
    // Na hora que o usuário escolher a opção A (receber o arquivo de entrada):
    printf("Iniciando a leitura dos arquivos...\n");
    
    // Só passar os nomes dos arquivos principais:
    lerEntradaPrincipal("entrada.txt", "Stopwords.txt");
    
    // ... resto do código ...
    return 0;
}
```
