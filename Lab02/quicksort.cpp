#include <iostream>   // Biblioteca para entrada e saída
#include <vector>     // Biblioteca para vetores
#include <random>     // Biblioteca do Random 

/////////////////////   FUNÇOẼS PARA TESTE   ///////////////////

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

////////////////////   FIM  -  FUNÇOES TESTE   ///////////////////////////

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

void medianaLomuto(std::vector<int>& array, int fst, int lst, const std::string& arquivo){
    
    ////////////   Impressões de teste   /////////////


    
    //std::cout << "First: " << array[fst] << std::endl;
    //std::cout << "Last: " << array[lst] << std::endl;




    // imprimeVetor(array);
    std::cout << "Partição processada:" << std::endl;
    imprimeParticao(array, fst, lst);
    int medio = mediana(array, fst, lst);
    std::cout << "Mediana: " << array[medio] << std::endl;
    swap(array, fst, medio);
    // imprimeVetor(array);
    
    int size = lst - fst;
    int larger = fst + 1;
    int key = fst;      // Apagar e declarar dentro do FOR
    int step=0;

    /*
    // Impressão de teste
    // std::cout << "Step: " << step << std::endl;
    std::cout << "First: " << array[fst] << std::endl;
    std::cout << "Last: " << array[lst] << std::endl;
    std::cout << "Larger: " << array[larger] << std::endl;
    */

    imprimeDetalhe(array, key, larger);

    for(int i = 1; i <= size; i++){
        key++;
        if(array[fst] > array[key]){   // Ver a lógica para números iguais  >=
            if(larger == key){
                larger++;
            }else{
                swap(array, larger, key);
                larger++;
            }
        }
        imprimeDetalhe(array, key, larger);
        step++;
    }

    swap(array, fst, larger-1);   // Coloca o pivô na posição correta
    key = larger -1;
    std::cout << "-----  Final da passada!  -----\n"  << std::endl;
    imprimePivo(array, key);
    
    // std::cout << "Pivô: " << array[key] << std::endl;

    if((key-1) > fst){
        medianaLomuto(array, fst, key-1, "stats-mediana-lomuto.txt");
    }
    if((key+1) < lst){
        medianaLomuto(array, key+1, lst, "stats-mediana-lomuto.txt");
    }
    // std::cout << "Valor smaller: " << array[smaller] << std::endl;
    // std::cout << "Índice smaller: " << smaller << std::endl;
}

int main(){

    // std::vector<int> array = {16,16,14,12,1,8,4,9,6,15,13,11,2,7,3,10,5};
    // std::vector<int> array = {16,16,14,12,1,8,4,9,6,15,5,11,2,7,3,10,13};
    // std::vector<int> array = {16,9,14,12,1,8,4,5,6,15,13,11,2,7,3,10,16};
    std::vector<int> array = {16,5,14,12,1,8,4,16,6,15,13,11,2,7,3,10,9};

    int i=1;
    int size = array[0];
    int first = i;
    int last = size;
    
/*
imprimeVetor(array);
int medio = mediana(array, first, last);
imprimeVetor(array);
*/

medianaLomuto(array, first, last, "stats-mediana-lomuto.txt");

///////////////   TESTES DA TROCA    ////////////////////////////////////
// Troquei o nome de algumas variáveis, os testes não vão funcionar
/*
    // int swap(array, first, last);   // Chamada da função
    // int swap(array, smaller, larger);   // Chamada da função

    std::cout << "Valor do last: " << array[last] << std::endl;

    swap(array, first, last);

    std::cout << "Valor do first: " << array[first] << std::endl;
    std::cout << "Valor do last: " << array[last] << std::endl;
*/
///////////////   FIM - TESTES DA TROCA    //////////////////////////////


///////////////   TESTES DO RANDOM    ////////////////////////////////////
/*
    // int numR = random(first, last);  // Chamada da função

    std::cout << "Índice aleatório: " << numR << std::endl;
    std::cout << "Número aleatório: " << array[numR] << std::endl;

    numR = random(1, 10);
    std::cout << "Número aleatório: " << numR << std::endl;

    numR = random(1, 10);
    std::cout << "Número aleatório: " << numR << std::endl;

    numR = random(1, 10);
    std::cout << "Número aleatório: " << numR << std::endl;
*/
///////////////   FIM - TESTES DA RANDOM    //////////////////////////////


///////////////   TESTES DA MEDIANA    //////////////////////////////////
/*
    int i=1;
    int size = array[0];
    int first = i;
    int last = size;

    // int medio = mediana(array, first, last);  // Chamada da função

    std::cout << "Tamanho do array: " << size << std::endl;
    std::cout << "Índice do first: " << first << std::endl;
    std::cout << "Índice do last: " << last << std::endl;
    std::cout << "Valor do last: " << array[last] << std::endl;
    std::cout << "Índice da mediana: " << medio << std::endl;
    std::cout << "Valor da mediana: " << array[medio] << std::endl;
*/
///////////////   FIM - TESTES DA MEDIANA    //////////////////////////////////

    // std::cout << "Rodou!" << std::endl;

    return 0;
}