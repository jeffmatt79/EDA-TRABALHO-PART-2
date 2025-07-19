#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <cctype>
#include "TextProcessor.h"
#include "AVLTree.h"
#include "RedBlackTree.h"
#include "hash.h"
#include "openHash.h"

using namespace std;

template<typename Tree>
void write(Tree& dicionario, const string& arquivoSaida) {
    ofstream outFile(arquivoSaida);
    if (!outFile.is_open()) {
        cerr << "Erro ao abrir o arquivo de saída." << endl;
        return;
    }
 
    cout << "Deseja imprimir o dicionário completo ou palavras que começam com uma letra específica?\n";
    cout << "Digite 'completo', 'freq' ou uma letra (ex: a): ";
    string escolha;
    cin >> escolha;
    auto inicio = std::chrono::high_resolution_clock::now();
    if (escolha == "completo") {
         dicionario.printInOrder(outFile);
    } else if (escolha.size() == 1 && isalpha(escolha[0])) {
        char letra = tolower(escolha[0]);
        outFile << "Palavras que começam com '" << letra << "':\n";
        dicionario.printChar(letra, outFile);
    } else if(escolha == "freq") {
          std::vector<std::pair<std::string, int>> vec;
        dicionario.toVector(vec);
        sort(vec.begin(), vec.end(),
            [](const pair<string, int>& a, const pair<string, int>& b) {
                return a.second > b.second; 
            });

        outFile << "Palavras ordenadas por frequência:\n";
        for (const auto& p : vec) {
            outFile << p.first << ": " << p.second << "\n";
        }
    } 
     else {
        std::cerr << "Opção inválida." << std::endl;
    }
    
    auto fim = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duracao = fim - inicio;
    cout << "Tempo para gerar a saída: " << duracao.count() << " segundos" << endl;
}

int main(int argc, char* argv[]) {
    if (argc < 4) {
        cerr << "Uso: ./freq dictionary <estrutura> <entrada.txt> [saida.txt]" << endl;
        return 1;
    }

    string estrutura = argv[2];
    string arquivoEntrada = argv[3];
    string arquivoSaida = (argc == 5) ? argv[4] : "saida.txt";
    ifstream inFile(arquivoEntrada);
    if (!inFile.is_open()) {
        cerr << "Erro ao abrir o arquivo de entrada." << endl;
        return 1;
    }
    if (estrutura == "AVL") {
     AVLTree<string, int> dicionario;
       string palavra;
    auto inicio = chrono::high_resolution_clock::now();

    while (inFile >> palavra) {
        palavra = TextProcessor::normalize(palavra);
        if (palavra.empty()) continue;  
            dicionario.insert(palavra, 1);    
    } 
auto fim = chrono::high_resolution_clock::now();
    chrono::duration<double> duracao = fim - inicio;
     write(dicionario,arquivoSaida );
    cout << "Palavras: " << dicionario.size() << endl;
    cout << "Comparacoes: " << dicionario.getComparisons() << endl;
    cout << "Tempo: " << duracao.count() << " segundos" << endl;
    cout << "rotações: " << dicionario.getRotations() << endl;
   }     
    else if(estrutura == "RBT"){
        RedBlackTree<string, int> dicionario;
         string palavra;
    auto inicio = chrono::high_resolution_clock::now();
   
    while (inFile >> palavra) {
        palavra = TextProcessor::normalize(palavra);
        if (palavra.empty()) continue;

      /*  if (dicionario.exists(palavra)) {
            int freq = dicionario.get(palavra);                
            dicionario.update(palavra, freq + 1);
        } else {   */
            dicionario.insert(palavra, 1);
       // }
      
    }
     auto fim = chrono::high_resolution_clock::now();
    chrono::duration<double> duracao = fim - inicio;
     write(dicionario,arquivoSaida );
     
  /*  ofstream outFile(arquivoSaida);
    char letra = 'a';
    outFile << "Palavras que começam com '" << letra << "':\n";
    dicionario.printChar(letra, outFile); */
   
    cout << "Palavras: " << dicionario.size() << endl;
    cout << "Comparacoes: " << dicionario.getComparisons() << endl;
    cout << "Tempo: " << duracao.count() << " segundos" << endl; 
    cout << "rotações: " << dicionario.getRotations() << endl;
    }
    else if (estrutura == "HASH") {
        ChainedHashTable<string, int> dicionario;
        string palavra;
        auto inicio = chrono::high_resolution_clock::now();

        while (inFile >> palavra) {
            palavra = TextProcessor::normalize(palavra);
            if (!palavra.empty())
                dicionario.insert(palavra);  
        }

        auto fim = chrono::high_resolution_clock::now();
        chrono::duration<double> duracao = fim - inicio;

       dicionario.write(dicionario, arquivoSaida); // no dicionário 

        cout << "Palavras: " << dicionario.size() << endl;
        cout << "Tempo: " << duracao.count() << " segundos" << endl;
        cout << "Comparacoes: " << dicionario.getComparisons() << endl;
        cout << "colisões " << dicionario.getCollisions() << endl;
    } 
    else if (estrutura == "OPEN") {
        HashOpen<string, int> dicionario;
        string palavra;
       auto inicio = chrono::high_resolution_clock::now();

        while (inFile >> palavra) {
            palavra = TextProcessor::normalize(palavra);
            if (palavra.empty()) continue;

            int atual;
            if (dicionario.find(palavra, atual)) {
                dicionario.insert(palavra, atual + 1);
            } else {
                dicionario.insert(palavra, 1);
            }
        }
        
        auto fim = chrono::high_resolution_clock::now();
        std::vector<std::pair<std::string, int>> vec;
        chrono::duration<double> duracao = fim - inicio;
        for (char c = 'a'; c <= 'z'; ++c) {
            for (int i = 0; i < 10000; ++i) {
                string tentativa = string(1, c);
                int valor;
                if (dicionario.find(tentativa, valor)) {
                    vec.push_back({tentativa, valor});
                }
            }
        }

        sort(vec.begin(), vec.end(), [](const auto& a, const auto& b) {
            return a.second > b.second;
        });

        ofstream outFile(arquivoSaida);
        for (auto& p : vec) {
            outFile << p.first << " " << p.second << "\n";
        }

        cout << "Palavras: " << dicionario.size() << endl;
        cout << "Comparacoes: " << dicionario.getComparisons() << endl;
        cout << "Tempo: " << duracao.count() << " segundos" << endl;

  }  
}
