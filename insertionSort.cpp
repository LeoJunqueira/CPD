#include <iostream>
#include <vector>

// Função que imprime o vetor
void imprimeVetor(const std::vector<int>& vetor){
    for(int i=0; i < vetor.size(); i++){
        std::cout << vetor[i] << " ";
    }
    std::cout << std::endl;
}

// Função que compara os elementos do vetor
void insere(std::vector<int>& vetor, int comp, int busc){
    while(comp >= 0){
        if(vetor[busc] < vetor[comp]){
            int swap = vetor[busc];
            vetor[busc] = vetor[comp];
            vetor[comp] = swap;
        }
        busc--;
        comp--;
    }
}

int main(){

    std::vector<int> array = {12,2,5,4,8,7,6,9,1,15};

    imprimeVetor(array);

    for(int base = 0; base < (array.size()-1); base++){
        int chave = base;
        int buscado = base + 1;
        if(array[chave] > array[buscado]){
            insere(array, chave, buscado);
        }
    }

    imprimeVetor(array);

    return 0;
}