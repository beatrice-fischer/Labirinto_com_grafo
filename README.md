# 🔍 Labirinto com Grafos — BFS em C

Projeto acadêmico da disciplina de **Estrutura de Dados** do segundo semestre de Engenharia de Software da Católica de Santa Catarina, que resolve um labirinto utilizando **grafos** e o algoritmo de **Busca em Largura (BFS)**, implementado em **C ANSI** e testado por prova de autoria.

---

## 📚 Como o labirinto é representado
O labirinto é armazenado como uma **matriz de caracteres** (21 linhas × 49 colunas) e interpretado como um **grafo não direcionado**:

| Símbolo | Significado |
|---------|-------------|
| `#`     | Parede (sem vértice) |
| `.`     | Espaço livre (vértice) |
| `E`     | Entrada (vértice inicial) |
| `S`     | Saída (vértice final) |
| `*`     | Caminho encontrado pelo BFS |

Cada célula livre é um **vértice** e cada movimento possível entre duas células adjacentes (cima, baixo, esquerda, direita) é uma **aresta**.

---

## 📚 Algoritmo BFS
O BFS (Breadth-First Search) explora o grafo nível por nível a partir da entrada, garantindo que o **primeiro caminho encontrado até a saída seja sempre o menor** em número de passos.

**Etapas:**
1. Insere a entrada em uma fila
2. Remove o primeiro elemento da fila (vértice atual)
3. Se é a saída, termina com sucesso
4. Senão, insere na fila todos os vizinhos válidos ainda não visitados
5. Repete até encontrar a saída ou esvaziar a fila

Após o BFS, o caminho é reconstruído percorrendo de trás para frente a **matriz de pais**, que registra por qual célula cada posição foi alcançada.

---

## 🗂️ Estrutura do código
```
n3-grafo.cpp
│
├── escolherParede()     — retorna o caractere Unicode correto para cada parede
├── exibirLabirinto()    — imprime a grade com cores no terminal
├── localizarEntrada()   — encontra a posição do 'E' na matriz
├── localizarSaida()     — encontra a posição do 'S' na matriz
├── posicaoValida()      — verifica se uma célula pode ser visitada
├── bfs()                — algoritmo de busca em largura
├── marcarCaminho()      — reconstrói e marca o caminho com '*'
└── main()               — fluxo principal do programa
```

---

## 📚 Recursos visuais
As cores no terminal são aplicadas via **API do Windows** (`SetConsoleTextAttribute`):
- 🟢 `*` — caminho encontrado (verde)
- 🔴 `E` / `S` — entrada e saída (vermelho)

---

## 📚 Como compilar e executar

### Pré-requisitos
- Compilador GCC (MinGW no Windows)
- Windows (devido ao uso de `windows.h` para cores)
- Terminal com suporte a UTF-8 (Windows Terminal ou VS Code)

### Compilar
```bash
gcc -o labirinto grafo_beatrice_e_gabriele.cpp
```

### Executar
```bash
./labirinto
```
> **Dica:** Se os traços das paredes aparecerem como caracteres estranhos no `cmd.exe`, adicione `SetConsoleOutputCP(CP_UTF8);` no início do `main()` ou use o **Windows Terminal**.

---

## 📚 Conceitos aplicados
- Representação de grafos com matriz;
- Busca em Largura (BFS);
- Reconstrução de caminho com matriz de pais;
- Controle de vértices visitados;
- Manipulação de strings e matrizes em C;
- Saída colorida no terminal via API do Windows.

---

<img width="621" height="593" alt="Captura de tela 2026-06-24 180119" src="https://github.com/user-attachments/assets/9c10149c-64c9-4ca4-bfe0-0d35a3647c6f" />
<img width="476" height="557" alt="Captura de tela 2026-06-24 180143" src="https://github.com/user-attachments/assets/3e3a5404-2657-4e16-b84b-542038f38310" />
