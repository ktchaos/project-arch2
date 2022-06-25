#include <bits/stdc++.h>
#include <chrono>
#include <omp.h>

using namespace std;

#define IMAGE_SIZE 10000
static int KERNEL_SIZE = 5;
static int KERNEL_AMPLITUDE = KERNEL_SIZE/2;
static int SEED = 42;

int image[IMAGE_SIZE][IMAGE_SIZE];
int new_image[IMAGE_SIZE][IMAGE_SIZE];

int random_byte(int seed){
    srand(SEED);
    return rand() % 256; 
}

void init_images(){
    int aux = 0;
    for(int i = 0; i < IMAGE_SIZE; i++){
        for(int j = 0; j < IMAGE_SIZE; j++){
            new_image[i][j] = 0;
            image[i][j] = aux;
            aux = (aux + 1) % 256;
            if (aux == 0)
                aux++;
            //image[i][j] = random_byte(SEED);
            //SEED++;
        }    
    }
    SEED = 42;
}

void convolution_version_1(){
    for(int linha = 0; linha < IMAGE_SIZE; linha++){
        for(int coluna = 0; coluna < IMAGE_SIZE; coluna++){
            float sum = 0;
            for(int m = linha - KERNEL_AMPLITUDE; m <= linha + KERNEL_AMPLITUDE; m++){
                for(int n = coluna - KERNEL_AMPLITUDE; n <= coluna + KERNEL_AMPLITUDE; n++){
                    if (m >= 0 && m < IMAGE_SIZE && n >= 0 && n < IMAGE_SIZE)
                        sum += (image[m][n] / KERNEL_SIZE*KERNEL_SIZE);    
                }
            }
            new_image[linha][coluna] = sum;
        }
    }
}

void convolution_version_openmp(){
    #pragma omp parallel for collapse(2)
    for(int linha = 0; linha < IMAGE_SIZE; linha++){
        for(int coluna = 0; coluna < IMAGE_SIZE; coluna++){
            int sum = 0;
            for(int m = linha - KERNEL_AMPLITUDE; m <= linha + KERNEL_AMPLITUDE; m++){
                for(int n = coluna - KERNEL_AMPLITUDE; n <= coluna + KERNEL_AMPLITUDE; n++){
                    if (m >= 0 && m < IMAGE_SIZE && n >= 0 && n < IMAGE_SIZE)
                        sum += image[m][n];                     
                }
            }
            new_image[linha][coluna] = sum / (KERNEL_SIZE*KERNEL_SIZE);
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

    cout << "Elapsed time in convolution version 1: " << elapsed_time << "s.\n";

    start = chrono::steady_clock::now();

    convolution_version_openmp();

    end = chrono::steady_clock::now();

    elapsed_time = chrono::duration_cast<chrono::seconds>(end - start).count();

    cout << "Elapsed time in convolution version openmp: " << elapsed_time << "s.";
    
    return 0;
}