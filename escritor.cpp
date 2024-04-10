#include <iostream>
#include <vector>
#include <fstream>


// Função que imprime o vetor
void imprimeVetor(const std::vector<int>& vetor){
    for(int i=0; i < vetor.size(); i++){
        std::cout << vetor[i] << " ";
    }
    std::cout << std::endl;
}


int main(){
    
    std::vector<int> array = {32,7,3,15,13,4,21,6,2,9,1,31,45,11,5,8,23,14,12,32,33,16,34,67,3,23,45,67,21,4,5,39};

    std::vector<int> arrayPot2 = array;
    std::vector<int> arrayKnuth = array;
    std::vector<int> arrayCiura = array;

    imprimeVetor(arrayPot2);
    std::cout << "Este é o arrayPot2." << std::endl;
    std::cout << std::endl;
    
    imprimeVetor(arrayKnuth);
    std::cout << "Este é o arrayKnuth." << std::endl;
    std::cout << std::endl;
    
    imprimeVetor(arrayCiura);
    std::cout << "Este é o arrayCiura." << std::endl;
    std::cout << std::endl;


    // Arquivo de saída
    std::ofstream escrita("saida.txt"); // Abre o arquivo "saida.txt" para escrita
    // std::vector<std::vector<string>> matrizSaida;

    if (!escrita.is_open()) {
        std::cerr << "Erro ao abrir o arquivo." << std::endl;
        return 0;
    }

    //matrizSaida.push_back(arrayPot2); // Adiciona o vetor da linha ao vetor da matriz



    escrita << "SEQ=CIURA" << std::endl;
   

    // Escreve o vetor no arquivo
    for (int i = 0; i < arrayPot2.size(); i++) {
        escrita << arrayPot2[i] << " ";
    }

    escrita.close(); // Fecha o arquivo

    std::cout << "Vetores salvos em 'saida.txt'." << std::endl;

///////////////////////////////////////////////////////////////////////////////////////

    std::ifstream cpuinfo("/proc/cpuinfo");
    if (!cpuinfo) {
        std::cerr << "Não foi possível abrir o arquivo /proc/cpuinfo" << std::endl;
        return 1;
    }

    std::string linha;
    
    /*while (std::getline(cpuinfo, linha)) {
        if (linha.substr(0, 7) == "cpu MHz") {
            std::cout << linha << std::endl;
        }
    }
*/
    //std::string linha;
    while (std::getline(cpuinfo, linha)) {
        if (linha.substr(0, 10) == "model name") {
            std::cout << linha << std::endl;
            break;
        }
    }

   // std::ifstream cpuinfo("/proc/cpuinfo");
    std::string line;

    while (std::getline(cpuinfo, line)) {
        if (line.substr(0, 10) == "model name") {
            std::size_t index = line.find(":");
            if (index != std::string::npos) {
                std::cout << line.substr(index + 1) << std::endl;
            }
            break;
        }
    }

    return 0;
}