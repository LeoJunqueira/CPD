#include <iostream>
#include <vector>

// Função que imprime o vetor
void imprimeVetor(const std::vector<int>& vetor){
    for(int i=0; i < vetor.size(); i++){
        std::cout << vetor[i] << " ";
    }
    std::cout << std::endl;
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
void insereShell(std::vector<int>& vetor, int key, int next, int group){
    while(key >= 0){
        if(vetor[next] < vetor[key]){
            int swap = vetor[next];
            vetor[next] = vetor[key];
            vetor[key] = swap;
        }

        //Apagar depois que funcionar
        imprimeTroca(vetor, key, next);

        next = next - group;
        key = key - group;
    }
}

int main(){
        
    /*
    std::vector<int> array = {32,7,3,15,13,4,21,6,2,9,1,31,45,11,5,8,23,14,12,32,33,16,34,67,3,23,45,67,21,4,5,39};
    
    int h = 16;
    int inc = 0;
    */    

    // imprimeVetor(array);
    
        // A "base" mantém a posição da "chave"
        // A "chave" é a posição usada para comparar com as próximas posições
        // O "prox" é a nova posição que vai ser comparada com a "chave"

        for(int i = 0; i < h; i++){    
            int chave = i;
            int prox = i + h;
            if(array[chave] > array[prox]){
                insereShell(array, chave, prox, h);
            }            
        }
    // imprimeVetor(array);

    return 0;
}