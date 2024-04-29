#include <iostream>   // Biblioteca para entrada e saída
#include <vector>     // Biblioteca para vetores
#include <random>     // Biblioteca do Random 
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>

/////////////////////   FUNÇÕES PARA TESTE   ///////////////////

// Função que imprime o vetor
void imprimeVetor(const std::vector<int>& vetor){
    for(int i=1; i < vetor.size(); i++){    // Não imprime o índice zero (tamanho do vetor)
        std::cout << vetor[i] << " ";
    }
    std::cout << std::endl;
}

void imprimeDetalhe(const std::vector<int>& vetor, int key, int larger){
    for(int i = 1; i < vetor.size(); i++){    // Não imprime o índice zero (tamanho do vetor)
        if ((i == key) && (i == larger)) {
            std::cout << "((" << vetor[i] << "))";
        } else if (i == key) {
            std::cout << " {" << vetor[i] << "} ";
        } else if (i == larger) {
            std::cout << " [" << vetor[i] << "] ";
        } else {
            std::cout << "  " << vetor[i] << "  ";
        }
    }
    std::cout << std::endl;
}

/*
// Função que imprime o vetor destacando os elementos trocados
void imprimeStatus(const std::vector<int>& vetor, int key, int larger){
    for(int i=1; i < vetor.size(); i++){    // Não imprime o índice zero (tamanho do vetor)
        if((i == key) || (i == larger)){
                std::cout << "(" << vetor[i] << ") ";
        }else
            std::cout << vetor[i] << " ";
    }
    std::cout << std::endl;
}
*/

// Função que imprime o vetor destacando os elementos trocados
void imprimeParticao(const std::vector<int>& vetor, int fst, int lst){
    for(int i=1; i < vetor.size(); i++){    // Não imprime o índice zero (tamanho do vetor)
        if((i == fst) || (i == lst)){
            std::cout << "*" << vetor[i] << "* ";
        }else{
            std::cout << vetor[i] << " ";
        }
    }
    std::cout << std::endl;
}

void imprimePivo(const std::vector<int>& vetor, int key){
    for(int i=1; i < vetor.size(); i++){    // Não imprime o índice zero (tamanho do vetor)
        if(i == key){
            std::cout << "<<" << vetor[i] << ">> ";
        }else{
            std::cout << vetor[i] << " ";
        }
    }
    std::cout << std::endl;
}

////////////////////   FIM  -  FUNÇÕES TESTE   ///////////////////////////

// Função que recebe um vetor, o primeiro e o último número de índice deste vetor
// e devolve a mediana deste vetor
int mediana(std::vector<int> array, int first, int last){
    
    int middle = first + ((last - first)/2);
    int medio;

    /*
    // std::cout << "Informações recebidas na função mediana:" << std::endl;
    std::cout << "Índice Mediana First: " << first << std::endl;
    std::cout << "Índice Mediana Last: " << last << std::endl;
    std::cout << "Índice Mediana med: " << middle << std::endl;
    std::cout << "Mediana First: " << array[first] << std::endl;
    std::cout << "Mediana Last: " << array[last] << std::endl;
    std::cout << "Mediana med: " << array[middle] << std::endl;
    */

    // if((a > b) && (b > c) || (a < b) && (b < c))
    if(((array[first] >= array[middle]) && (array[middle] >= array[last])) || ((array[first] <= array[middle]) && (array[middle] <= array[last]))){
        medio = middle;
    }
    
    if(((array[middle] >= array[first]) && (array[first] >= array[last])) || ((array[middle] <= array[first]) && (array[first] <= array[last]))){
        medio = first;
    }

    if(((array[first] >= array[last]) && (array[last] >= array[middle])) || ((array[first] <= array[last]) && (array[last] <= array[middle]))){
        medio = last;
    }

    return medio;
}

// Função recebe o primeiro e o último número de índice deste vetor 
// e retorna um número aleatório nesse intervalo
int random(int min, int max) {
    // Cria um gerador de números aleatórios
    std::random_device rd;

    // Inicializa um gerador de números aleatórios com semente
    std::mt19937 gen(rd());

    // Define o intervalo
    std::uniform_int_distribution<> distr(min, max);

    // Gera um número aleatório no intervalo
    int aleatorio = distr(gen);

    return aleatorio;
}

// Coloca o elemento A e B de posição
void swap(std::vector<int>& array, int elmtA, int elmtB){
    
    int swp = array[elmtA];
    array[elmtA] = array[elmtB];
    array[elmtB] = swp;
    
}

void medianaLomuto(std::vector<int>& array, int fst, int lst, int* totalSwap, int* totalRec){
    (*totalRec)++;
    int medio = mediana(array, fst, lst);
    swap(array, fst, medio);
    (*totalSwap)++;
    
    int size = lst - fst;
    int larger = fst + 1;
    int key = fst;      // Apagar e declarar dentro do FOR

    for(int i = 1; i <= size; i++){
        key++;
        if(array[fst] > array[key]){   // Ver a lógica para números iguais  >=
            if(larger == key){
                larger++;
            }else{
                swap(array, larger, key);
                (*totalSwap)++;
                larger++;
            }
        }
    }
    swap(array, fst, larger-1);   // Coloca o pivô na posição correta
    (*totalSwap)++;
    key = larger -1;

    if((key-1) > fst){
        medianaLomuto(array, fst, key-1, totalSwap, totalRec);
    }
    if((key+1) < lst){
        medianaLomuto(array, key+1, lst, totalSwap, totalRec);
    }
}

void medianaHoare(std::vector<int>& array, int fst, int lst, int* totalSwap, int* totalRec){
    (*totalRec)++;
    int medio = mediana(array, fst, lst);
    swap(array, fst, medio);
    (*totalSwap)++;
    int loKey = fst + 1;
    int hiKey = lst;
    int key = fst;

    while(loKey < hiKey){
        if(array[loKey] > array[fst]){   // Ver a lógica para números iguais  >=
            while(loKey < hiKey){
                if(array[hiKey] < array[fst]){
                    swap(array, loKey, hiKey);
                    hiKey--;
                    loKey++;
                    key++;
                    (*totalSwap)++;
                    break;
                }else{
                    hiKey--;
                }
            }  
        }else{
            loKey++;
            key++;
        }
    }
    if(loKey == hiKey){
        if(array[loKey] < array[fst])
            key++;
    }
    swap(array, fst, key);   // Coloca o pivô na posição correta
    (*totalSwap)++;
    if((key-1) > fst){
        medianaHoare(array, fst, key-1, totalSwap, totalRec);
    }
    if((key+1) < lst){
        medianaHoare(array, key+1, lst, totalSwap, totalRec);
    }
}

void randomLomuto(std::vector<int>& array, int fst, int lst, int* totalSwap, int* totalRec){
    (*totalRec)++;
    int rand = random(fst, lst);
    swap(array, fst, rand);
    (*totalSwap)++;
    int medio = mediana(array, fst, lst);
    swap(array, fst, medio);
    (*totalSwap)++;

    int size = lst - fst;
    int larger = fst + 1;
    int key = fst;      // Apagar e declarar dentro do FOR

    for(int i = 1; i <= size; i++){
        key++;
        if(array[fst] > array[key]){   // Ver a lógica para números iguais  >=
            if(larger == key){
                larger++;
            }else{
                swap(array, larger, key);
                (*totalSwap)++;
                larger++;
            }
        }
    }
    swap(array, fst, larger-1);   // Coloca o pivô na posição correta
    (*totalSwap)++;
    key = larger -1;

    if((key-1) > fst){
        randomLomuto(array, fst, key-1, totalSwap, totalRec);
    }
    if((key+1) < lst){
        randomLomuto(array, key+1, lst, totalSwap, totalRec);
    }
}

void randomHoare(std::vector<int>& array, int fst, int lst, int* totalSwap, int* totalRec){
    (*totalRec)++;
    int rand = random(fst, lst);
    swap(array, fst, rand);
    (*totalSwap)++;
    int medio = mediana(array, fst, lst);
    swap(array, fst, medio);
    (*totalSwap)++;
    
    int loKey = fst + 1;
    int hiKey = lst;
    int key = fst;

    while(loKey < hiKey){
        if(array[loKey] > array[fst]){   // Ver a lógica para números iguais  >=
            while(loKey < hiKey){
                if(array[hiKey] < array[fst]){
                    swap(array, loKey, hiKey);
                    hiKey--;
                    loKey++;
                    key++;
                    (*totalSwap)++;
                    break;
                }else{
                    hiKey--;
                }
            }  
        }else{
            loKey++;
            key++;
        }
    }
    if(loKey == hiKey){
                if(array[loKey] < array[fst])
                    key++;
    }
    swap(array, fst, key);   // Coloca o pivô na posição correta
    (*totalSwap)++;

    if((key-1) > fst){
        randomHoare(array, fst, key-1, totalSwap, totalRec);
    }
    if((key+1) < lst){
        randomHoare(array, key+1, lst, totalSwap, totalRec);
    }
}

int main(){

    std::ifstream arquivo("entrada-quicksort.txt"); // Abre o arquivo "entrada1.txt" para leitura

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

////////////////   FIM DA LEITURA   ///////////////


///////////////   Abre o arquivo de escrita   ////////////////
    std::ofstream escritaMH("stats-mediana-hoare.txt");
    
    if (!escritaMH.is_open()) {
        std::cerr << "Erro ao abrir o arquivo de saída." << std::endl;
    return 1;
    }

    std::vector<int> array;
    
    //////////   Mediana Hoare   ///////////
    for (const auto& linha : matriz) {
        std::vector<int> array = linha; // Copiar a linha para um novo vetor
  
        int i=1;
        int size = array[0];
        int first = i;
        int last = size;
        int totalSwap = 0;
        int totalRec = 0;

        // Obtém o tempo de CPU inicial
        std::clock_t inicio = std::clock();

        std::cout << "**************************   medianaHoare   *************" << std::endl;
        medianaHoare(array, first, last, &totalSwap, &totalRec);

        // Obtém o tempo de CPU final
        std::clock_t fim = std::clock();

        // Calcula o tempo de CPU usado
        double time = 1000.0 * (fim - inicio) / CLOCKS_PER_SEC;

        escritaMH << "TAMANHO DA ENTRADA " << size << std::endl;
        escritaMH << "SWAPS " << totalSwap << std::endl;
        escritaMH << "RECURSOES " << totalRec << std::endl;
        escritaMH << "TEMPO " << time << std::endl;
        std::cout << "Mediana Hoare" << totalSwap << std::endl;    
    }

    //////////   Mediana Lomuto   ///////////
    std::ofstream escritaML("stats-mediana-lomuto.txt");
    
    if (!escritaML.is_open()) {
        std::cerr << "Erro ao abrir o arquivo de saída." << std::endl;
    return 1;
    }

    for (const auto& linha : matriz) {
        std::vector<int> array = linha; // Copiar a linha para um novo vetor
  
        int i=1;
        int size = array[0];
        int first = i;
        int last = size;
        int totalSwap = 0;
        int totalRec = 0;

        // Obtém o tempo de CPU inicial
        std::clock_t inicio = std::clock();

        std::cout << "**************************   medianaLomuto   *************" << std::endl;
        medianaLomuto(array, first, last, &totalSwap, &totalRec);

        // Obtém o tempo de CPU final
        std::clock_t fim = std::clock();

        // Calcula o tempo de CPU usado
        double time = 1000.0 * (fim - inicio) / CLOCKS_PER_SEC;

        escritaML << "TAMANHO DA ENTRADA " << size << std::endl;
        escritaML << "SWAPS " << totalSwap << std::endl;
        escritaML << "RECURSOES " << totalRec << std::endl;
        escritaML << "TEMPO " << time << std::endl;
        std::cout << "Mediana Lomuto" << totalSwap << std::endl;    
    }
    
    //////////   Aleatório Hoare   ///////////
    std::ofstream escritaRH("stats-aleatorio-hoare.txt"); 
    
    if (!escritaRH.is_open()) {
        std::cerr << "Erro ao abrir o arquivo de saída." << std::endl;
    return 1;
    }

    for (const auto& linha : matriz) {
        std::vector<int> array = linha; // Copiar a linha para um novo vetor
  
        int i=1;
        int size = array[0];
        int first = i;
        int last = size;
        int totalSwap = 0;
        int totalRec = 0;

        // Obtém o tempo de CPU inicial
        std::clock_t inicio = std::clock();

        std::cout << "**************************   randomHoare   *************" << std::endl;
        randomHoare(array, first, last, &totalSwap, &totalRec);

        // Obtém o tempo de CPU final
        std::clock_t fim = std::clock();

        // Calcula o tempo de CPU usado
        double time = 1000.0 * (fim - inicio) / CLOCKS_PER_SEC;

        escritaRH << "TAMANHO DA ENTRADA " << size << std::endl;
        escritaRH << "SWAPS " << totalSwap << std::endl;
        escritaRH << "RECURSOES " << totalRec << std::endl;
        escritaRH << "TEMPO " << time << std::endl;
        std::cout << "Random Hoare" << totalSwap << std::endl;    
    }

    //////////   Aleatorio Lomuto   ///////////
    std::ofstream escritaRL("stats-aleatorio-lomuto.txt"); 
    
    if (!escritaRL.is_open()) {
        std::cerr << "Erro ao abrir o arquivo de saída." << std::endl;
    return 1;
    }

    for (const auto& linha : matriz) {
        std::vector<int> array = linha; // Copiar a linha para um novo vetor
  
        int i=1;
        int size = array[0];
        int first = i;
        int last = size;
        int totalSwap = 0;
        int totalRec = 0;

        // Obtém o tempo de CPU inicial
        std::clock_t inicio = std::clock();

        std::cout << "**************************   rondomLomuto   *************" << std::endl;
        randomLomuto(array, first, last, &totalSwap, &totalRec);

        // Obtém o tempo de CPU final
        std::clock_t fim = std::clock();

        // Calcula o tempo de CPU usado
        double time = 1000.0 * (fim - inicio) / CLOCKS_PER_SEC;

        escritaRL << "TAMANHO DA ENTRADA " << size << std::endl;
        escritaRL << "SWAPS " << totalSwap << std::endl;
        escritaRL << "RECURSOES " << totalRec << std::endl;
        escritaRL << "TEMPO " << time << std::endl;
        std::cout << "Random Lomuto" << totalSwap << std::endl;    
    }
    return 0;
}