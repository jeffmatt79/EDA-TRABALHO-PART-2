// Para compilar o programa, use o seguinte comando no terminal:
// g++ -std=c++17 freq.cpp -o freq

// Após compilar, execute o programa com o seguinte formato:
// ./freq dictionary <estrutura> <entrada.txt> [saida.txt]

// Onde:
// <estrutura> pode ser:
//   AVL   para usar árvore AVL
//   RBT   para usar árvore Rubro-Negra
//   HASH  para usar tabela hash com encadeamento separado
//   OPEN  para usar tabela hash com endereçamento aberto

// <entrada.txt> é o nome do arquivo de entrada contendo o texto a ser processado
// [saida.txt] é opcional e representa o nome do arquivo de saída (padrão é "saida.txt")

// Assim:
// ./freq dictionary AVL entrada.txt saida_avl.txt
// ./freq dictionary RBT entrada.txt saida_rbt.txt
// ./freq dictionary HASH entrada.txt saida_hash.txt
// ./freq dictionary OPEN entrada.txt saida_open.txt

// O programa irá ler o arquivo de entrada, processar as palavras e exibir estatísticas:
//  Total de palavras
// Número de comparações
// Tempo de execução
// Número de rotações (apenas em AVL e RBT)

// A saída com as palavras e suas frequências será gravada no arquivo de saída especificado
// O programa também permite escolher no final se deseja imprimir o dicionário completo,
// apenas palavras que começam com uma letra específica, ou ordenadas por frequência

