#include <bits/stdc++.h>
#include <chrono>

using namespace std;

#define IMAGE_SIZE 10000
static int KERNEL_SIZE = 5;
static int KERNEL_AMPLITUDE = KERNEL_SIZE/2;
static int SEED = 42;

long image[IMAGE_SIZE][IMAGE_SIZE];
long new_image[IMAGE_SIZE][IMAGE_SIZE];

int random_byte(int seed){
    srand(SEED);
    return rand() % 256; 
}

void init_images(){
    for(int i = 0; i < IMAGE_SIZE; i++){
        for(int j = 0; j < IMAGE_SIZE; j++){
            new_image[i][j] = 0;
            int aux = 0;
            image[i][j] = aux;
            aux = (aux + 1) % 256;
            //image[i][j] = random_byte(SEED);
            //SEED++;
        }    
    }
    SEED = 42;
}

void convolution_version_1(){
    for(int linha = 0; linha < IMAGE_SIZE; linha++){
        for(int coluna = 0; coluna < IMAGE_SIZE; coluna++){
            for(int m = linha - KERNEL_AMPLITUDE; m <= linha + KERNEL_AMPLITUDE; m++){
                for(int n = coluna - KERNEL_AMPLITUDE; n <= coluna + KERNEL_AMPLITUDE; n++){
                    if (m >= 0 && m < IMAGE_SIZE && n >= 0 && n < IMAGE_SIZE)
                        new_image[m][n] = image[m][n] / (KERNEL_SIZE*KERNEL_SIZE);                        
                }
            }
        }
    }
}

int main(){

    init_images();
    
    cout << "Criou\n";
    
    auto start = chrono::steady_clock::now();

    convolution_version_1();

    auto end = chrono::steady_clock::now();

    int elapsed_time = chrono::duration_cast<chrono::seconds>(end - start).count();

    cout << "Elapsed time in covolution version 1: " << elapsed_time << "s.";
    
    return 0;
}