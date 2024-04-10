#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

int achaH(std::vector<int>&  arrayTam, int size){
    int i=0;
    int aux;
    
    while(size > arrayTam[i]){
        aux = i;
        i++;
    }
    return aux;
}

// Função que imprime o vetor
void imprimeVetor(const std::vector<int>& vetor){
    for(int i=0; i < vetor.size(); i++){
        std::cout << vetor[i] << " ";
    }
    // std::cout << std::endl;
}

// Função que imprime o vetor destacando os elementos trocados
void imprimeTroca(const std::vector<int>& vetor, int key, int next){
    for(int i=0; i < vetor.size(); i++){
        if(i == key || i == next){
            std::cout << "(" << vetor[i] << ") ";
        }else{
            std::cout << vetor[i] << " ";
        }
    }
    std::cout << std::endl;
}

// Função que compara os elementos do vetor
void insereShell(std::vector<int>& vetor, int key, int next, int jump){
    while(key >= 0 && vetor[key] > vetor[next]){
        if(vetor[next] < vetor[key]){
            int swap = vetor[next];
            vetor[next] = vetor[key];
            vetor[key] = swap;
        }
        next = next - jump;
        key = key - jump;
    }
}

void insertionShell(std::vector<int>& array, int salto){     
       
    // O "i" mantém a posição da "chave"
    // A "chave" é a posição usada para comparar com as próximas posições
    // O "prox" é a nova posição que vai ser comparada com a "chave"

    for(int i = 0; i < salto; i++){    
        int chave = i;
        int prox = i + salto;

        while(prox <= (array.size()-1)){

            // Apagar Depois que funcionar 
            // std::cout << "Chave: " << array[chave] << "  --- Próximo: " << array[prox] << std::endl;
            // std::cout << "insertionShell - Índice da chave: " << chave << " Indice do próximo: " << prox << std::endl;

            if(array[chave] > array[prox]){
                insereShell(array, chave, prox, salto);
            }
                
            chave = chave + salto;
            prox = prox + salto;   
        }            
    }
}


void shell(std::vector<int>& array, std::vector<int>& vfunc, int h, const std::string& saida, const std::string& nomeFunc){
    std::ofstream escrita(saida, std::ios::app);  // Não sobreescreve o conteúdo anterior
    
    if (!escrita.is_open()) {
        std::cerr << "Erro ao abrir o arquivo." << std::endl;
        return;
    }

    // Escreve o vetor no arquivo
    for (int i = 0; i < array.size(); i++) {
        escrita << array[i] << " ";
    }

    escrita << "SEQ=" << nomeFunc << std::endl;

    while(h>0){        

        insertionShell(array, vfunc[h]);        

        // Escreve o vetor no arquivo
        for (int i = 0; i < array.size(); i++) {
            escrita << array[i] << " ";
        }

        escrita << "INCR=" << vfunc[h] << std::endl;

        h--;
    }    

    insertionShell(array, 1);

    // Escreve o vetor no arquivo
    for (int i = 0; i < array.size(); i++) {
        escrita << array[i] << " ";
    }

    escrita << "INCR=1"<< std::endl;

    escrita.close(); // Fecha o arquivo
}

int main(){
        
    std::ifstream arquivo("entrada1.txt"); // Abre o arquivo "entrada1.txt" para leitura

    if (!arquivo.is_open()) { // Verifica se o arquivo foi aberto corretamente
        std::cerr << "Erro ao abrir o arquivo." << std::endl;
        return 1;
    }

    std::vector<std::vector<int>> matriz; // Vetor de vetores para armazenar as linhas da matriz

    std::string linha;
    while (std::getline(arquivo, linha)) { // Lê cada linha do arquivo
        std::vector<int> numerosLinha; // Vetor para armazenar os números da linha atual

        std::istringstream iss(linha);
        int numero;
        while (iss >> numero) { // Lê cada número da linha
            numerosLinha.push_back(numero); // Adiciona o número ao vetor da linha atual
        }
        matriz.push_back(numerosLinha); // Adiciona o vetor da linha ao vetor da matriz
        }

    arquivo.close(); // Fecha o arquivo

    std::vector<int> array;
    
    for (const auto& linha : matriz) {
        std::vector<int> array = linha; // Copiar a linha para um novo vetor
        
        std::vector<int> arrayPot2 = array;
        std::vector<int> arrayKnuth = array;
        std::vector<int> arrayCiura = array;

        std::vector<int> pot2 = {1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768,65536,131072,262144,524288,1048576};
        std::vector<int> knuth = {1,4,13,40,121,364,1093,3280,9841,29524,88573,265720,797161,2391484};
        std::vector<int> ciura = {1,4,10,23,57,132,301,701,1577,3548,7983,17961,40412,90927,204585,460316,1035711};
        
        int tam = array.size();   

        int p = achaH(pot2, tam);
        int k = achaH(knuth, tam);
        int c = achaH(ciura, tam);
    
        
        shell(arrayPot2, pot2, p, "saida1.txt", "SHELL");
                  
        shell(arrayKnuth, knuth, k, "saida1.txt", "KNUTH");
                       
        shell(arrayCiura, ciura, c, "saida1.txt", "CIURA");          
    }

    std::cout << "Vetores salvos em 'saida1.txt'." << std::endl;

    return 0;
}