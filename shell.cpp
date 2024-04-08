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

        // Apagar depois que funcionar
        // imprimeTroca(vetor, key, next);

        next = next - jump;
        key = key - jump;
    }
}

void insertionShell(std::vector<int>& array, int salto){     
    
    // imprimeVetor(array);
    
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

                // Apagar Depois que funcionar 
                // std::cout << "Chave: " << array[chave] << "  --- Próximo: " << array[prox] << std::endl;

                // Apagar Depois que funcionar 
                // std::cout << "insertionShell - Índice da chave: " << chave << " Indice do próximo: " << prox << std::endl;  
                
            }  
            // Apagar Depois que funcionar 
            // imprimeVetor(array);

        }
    // imprimeVetor(array);

}

std::ofstream escrita;

void shell(std::vector<int>& array, std::vector<int>& vfunc, int h){
// É necessário o "h" e os dois arrays.
    // while usa o "h", array da função e o "s"
    // insertion usa o array e a posição do array da função no indice "s"
    while(h>0){      

        insertionShell(array, vfunc[h]);        

        imprimeVetor(array);
        escrita << "INCR=" << vfunc[h] << std::endl;

        //s++;
        h--;
    }

    insertionShell(array, 1);


    imprimeVetor(array);
    escrita << "INCR=1"<< std::endl;
}

int main(){
    // std::vector<int> array = {32,7,3,15,13,4,21,6,2,9,1,31,45,11,5,8,23,14,12,32,33,16,34,67,3,23,45,67,21,4,5,39};
    // std::vector<int> array = {16,14,12,1,8,4,9,6,15,13,11,2,7,3,10,5};

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
std::vector<std::vector<string>> matrizSaida;


for (const auto& linha : matriz) {
    std::vector<int> array = linha; // Copiar a linha para um novo vetor


//////////////////////////////////////////////////////////////////////////////////////////      
        
    std::vector<int> arrayPot2 = array;
    std::vector<int> arrayKnuth = array;
    std::vector<int> arrayCiura = array;

    std::vector<int> pot2 = {1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768,65536,131072,262144,524288,1048576};
    std::vector<int> knuth = {1,4,13,40,121,364,1093,3280,9841,29524,88573,265720,797161,2391484};
    std::vector<int> ciura = {1,4,10,23,57,132,301,701,1577,3548,7983,17961,40412,90927,204585,460316,1035711};
    
    

    int tam = array.size();   

    // h é o indice para usar com o array de cada função.
    //int s = 1;
    int p = achaH(pot2, tam);
    int k = achaH(knuth, tam);
    int c = achaH(ciura, tam);

    // std:: cout << "Esse eh apenas h: " << h << std::endl;
    // std:: cout << "Esse eh o pot2[h]: " << pot2[h] << std::endl;
    // std:: cout << "Esse eh o salto: " << pot2[s] << std::endl;

    
    imprimeVetor(arrayPot2);
    matrizSaida.push_back(std::to_string(arrayPot2)); // Adiciona o vetor da linha ao vetor da matriz
    escrita << "SEQ=SHELL" << std::endl;
    shell(arrayPot2, pot2, p);
    // matrizSaida.push_back(arrayPot2); // Adiciona o vetor da linha ao vetor da matriz
    

    imprimeVetor(arrayKnuth);
    matrizSaida.push_back(std::to_string(arrayKnuth)); // Adiciona o vetor da linha ao vetor da matriz
    escrita << "SEQ=KNUTH" << std::endl;
    shell(arrayKnuth, knuth, k);
    // matrizSaida.push_back(arrayKnuth); // Adiciona o vetor da linha ao vetor da matriz

    imprimeVetor(arrayCiura);
    matrizSaida.push_back(std::to_string(arrayCiura)); // Adiciona o vetor da linha ao vetor da matriz
    escrita << "SEQ=CIURA" << std::endl;
    shell(arrayCiura, ciura, c);
    // matrizSaida.push_back(arrayCiura); // Adiciona o vetor da linha ao vetor da matriz

//////////////////////////////////////////////////////////////////////////////////////////      
}

// Arquivo de saída

std::ofstream escrita("saida.txt"); // Abre o arquivo "saida.txt" para escrita

    if (!escrita.is_open()) {
        std::cerr << "Erro ao abrir o arquivo." << std::endl;
        return 1;
    }

    // Escreve a matriz no arquivo
    for (const auto& linha : matrizSaida) {
        for (const auto& valor : linha) {
            escrita << valor << " ";
        }
        escrita << std::endl; // Nova linha para cada linha da matriz
    }

////////////////////////////////////////////////////////////////////////////////////

// Como converter numeros em strings

  // Vetor de números a ser copiado para uma linha da matriz
    std::vector<int> novoVetor = {10, 11, 12};

    // Converter os números em strings
    std::vector<std::string> novoVetorString;
    for (int num : novoVetor) {
        novoVetorString.push_back(std::to_string(num));
    }

/////////////////////////////////////////////////////////////////////////////////////

    escrita.close(); // Fecha o arquivo

    std::cout << "Matriz salva em 'saida.txt'." << std::endl;



   

    return 0;
}