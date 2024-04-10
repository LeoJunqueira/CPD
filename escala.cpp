#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>

int achaH(std::vector<int>&  arrayTam, int size){
    int i=0;
    int aux;
    
    while(size > arrayTam[i]){
        aux = i;
        i++;
    }
    return aux;
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


double shell(std::vector<int>& array, std::vector<int>& vfunc, int h){
   
    // Obtém o tempo de CPU inicial
    std::clock_t inicio = std::clock();

    while(h>0){        
        insertionShell(array, vfunc[h]);  
        h--;
    }    

    insertionShell(array, 1);
    
    // Obtém o tempo de CPU final
    std::clock_t fim = std::clock();

    // Calcula o tempo de CPU usado
    double tempoUsado = 1000.0 * (fim - inicio) / CLOCKS_PER_SEC;
    
    return tempoUsado;

}

int main() {

    std::ifstream arquivo("entrada2.txt"); // Abre o arquivo "entrada1.txt" para leitura

    if (!arquivo.is_open()) { // Verifica se o arquivo foi aberto corretamente
        std::cerr << "Erro ao abrir o arquivo de entrada." << std::endl;
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


//////////////////////////////////////////////////////////////////////////////////////////
        std::ofstream escrita("saida2.txt", std::ios::app);  // Não sobreescreve o conteúdo anterior
    
        if (!escrita.is_open()) {
            std::cerr << "Erro ao abrir o arquivo de saída." << std::endl;
        return 1;
        }

        std::ifstream cpuinfo("/proc/cpuinfo");
        if (!cpuinfo) {
            std::cerr << "Não foi possível abrir o arquivo /proc/cpuinfo" << std::endl;
            return 1;
        }

        std::string line;
        std::size_t index;

        while (std::getline(cpuinfo, line)) {
            if (line.substr(0, 10) == "model name") {
                index = line.find(":");
                if (index != std::string::npos) {
                    std::cout << line.substr(index + 1) << std::endl;
                }
                break;
            }
        }


        double time;
        int i;
        int tamanho = tam - 1;

        time = shell(arrayPot2, pot2, p);
        escrita << "SHELL, " << tamanho << ", " << time << ", " << line.substr(index + 1) << std::endl;

        time = shell(arrayKnuth, knuth, k);
        escrita << "KNUTH, " << tamanho << ", " << time << ", " << line.substr(index + 1) << std::endl;

        time = shell(arrayCiura, ciura, c);
        escrita << "CIURA, " << tamanho << ", " << time << ", " << line.substr(index + 1) << std::endl;

        // Executa algum código...
        //for (volatile int i = 0; i < 10000000; ++i);



        // Imprime o tempo de CPU usado
        std::cout << "Tempo de CPU usado: " << time << " ms" << std::endl;
    }
    return 0;
}