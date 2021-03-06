CUDA:
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <iostream>
#include <vector>

/* --------------------------------------------------------------------
Implementati un program CUDA ce efectueaza adunarea a doua matrici patratice
cu N linii si N coloane
Urmati, pe rand, pasii de mai jos.
--------------------------------------------------------------------*/
__global__ void matrix_matrix_add(float *a, float *b, float *c, int N);
int main()
{
	// Numarul N de linii/coloane
	int N = 1024;
	// Prima matricea
	float *a_h;
	// A 2-a matrice
	float *b_h;
	// Matricea rezultat
	float *c_h;
	/* --------------------------------------------------------------------
	1. Alocati memorie pe host pentru cele trei matrici:
	* Matricea este de N linii si N coloane si este alocată ca un singur
	bloc de memorie (un o singura alocare de N*N elemente)
	0.7142 puncte
	----------------------------------------------------------------------*/
	/* ------------------------ REZOLVARE PCT 1 -----------------------------*/
	/* ------------------------ CODUL TAU DE AICI ---------------------------*/
	a_h = new float[N*N];
	b_h = new float[N*N];
	c_h = new float[N*N];
	/* ------------------------ CODUL TAU PANA AICI ---------------------------*/
	/* --------------------------------------------------------------------
	2. Initializati cele doua matrici a si b după cum urmeaza:
	* Prima matrice va fi initializata cu zero peste tot exceptand diagonala
	principala unde elementele au valoarea 5
	* A 2-a matrice va fi initializată cu 1 peste tot exceptand diagonala
	secundara unde elementele au valoarea 3
	0.7142 puncte
	----------------------------------------------------------------------*/
	/* ------------------------ REZOLVARE PCT 2 -----------------------------*/
	/* ------------------------ CODUL TAU DE AICI ---------------------------*/
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (i == j)
			{
				a_h[i*N + j] = 5;
			}
			else
			{
				a_h[i*N + j] = 0;
			}
		}
	}

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			
			if (j == (N-1) - i)
			{
				b_h[i*N + j] = 3;
			}
			else
			{
				b_h[i*N + j] = 1;
			}
		}
	}
	/* ------------------------ CODUL TAU PANA AICI ---------------------------*/
	// Cele trei matrici pentru memoria device
	float *a_d;
	float *b_d;
	float *c_d;
	/* --------------------------------------------------------------------
	3. Alocati memorie pe device pentru cele trei matrici
	0.7142 puncte
	----------------------------------------------------------------------*/
	/* ------------------------ REZOLVARE PCT 3 -----------------------------*/
	/* ------------------------ CODUL TAU DE AICI ---------------------------*/
	cudaMalloc((void**)&a_d, N*N * sizeof(float));
	cudaMalloc((void**)&b_d, N*N * sizeof(float));
	cudaMalloc((void**)&c_d, N*N * sizeof(float));
	/* ------------------------ CODUL TAU PANA AICI ---------------------------*/
	/* --------------------------------------------------------------------
	4. Copiati continutul celor doua matrici a si b de pe host pe device
	0.7142 puncte
	----------------------------------------------------------------------*/
	/* ------------------------ REZOLVARE PCT 4 -----------------------------*/
	/* ------------------------ CODUL TAU DE AICI ---------------------------*/
	cudaMemcpy(a_d, a_h, N*N * sizeof(float), cudaMemcpyHostToDevice);
	cudaMemcpy(b_d, b_h, N*N * sizeof(float), cudaMemcpyHostToDevice);
	/* ------------------------ CODUL TAU PANA AICI ---------------------------*/
	// Numarul de thread-uri pe bloc
	dim3 threadsPerBlock;
	threadsPerBlock.x = 32;
	threadsPerBlock.y = 32;
	threadsPerBlock.z = 1;
	// Numarul de blocuri
	dim3 numBlocks;
	/* --------------------------------------------------------------------
	5. Calculati numarul de blocuri astfel incat:
	* se obtine un grid 2D de thread-uri
	* Se va lansa in executie cate un thread pentru fiecare element din matrice
	deci NxN in total
	0.7142 puncte
	----------------------------------------------------------------------*/
	/* ------------------------ REZOLVARE PCT 5 -----------------------------*/
	/* ------------------------ CODUL TAU DE AICI ---------------------------*/
	numBlocks.x = N / threadsPerBlock.x;
	numBlocks.y = N / threadsPerBlock.y;
	numBlocks.z = 1;
	/* ------------------------ CODUL TAU PANA AICI ---------------------------*/
	// Se lanseaza in executie kernel-ul cuda
	matrix_matrix_add << <numBlocks, threadsPerBlock >> > (a_d, b_d, c_d, N);
	/* --------------------------------------------------------------------
	6. Copiati continutul matricei rezultat c de pe device pe host
	0.7142 puncte
	----------------------------------------------------------------------*/
	/* ------------------------ REZOLVARE PCT 6 -----------------------------*/
	/* ------------------------ CODUL TAU DE AICI ---------------------------*/
	cudaMemcpy(c_h, c_d, N*N * sizeof(float), cudaMemcpyDeviceToHost);
	/* ------------------------ CODUL TAU PANA AICI ---------------------------*/
	return 0;
}
__global__ void matrix_matrix_add(float *a, float *b, float *c, int N)
{
	// Indicele fiecarui thread
	int index;
	/* --------------------------------------------------------------------
	7. Calculati valoarea celor doi indici i si j utilizand variabilele
	predefinite blockDim, blocIdx si threadIdx astfel incat fiecare thread
	sa corespunda unei pozitii din matrice
	0.7142 puncte
	----------------------------------------------------------------------*/
	/* ------------------------ REZOLVARE PCT 7 -----------------------------*/
	/* ------------------------ CODUL TAU DE AICI ---------------------------*/
	int i = blockDim.x*blockIdx.x + threadIdx.x;
	int j = blockDim.y*blockIdx.y + threadIdx.y;
	/* ------------------------ CODUL TAU PANA AICI ---------------------------*/
	/* --------------------------------------------------------------------
	8. efectuati adunarea matricilor a si b si scrieti rezultatul in c (c = a+b)
	2 puncte
	----------------------------------------------------------------------*/
	/* ------------------------ REZOLVARE PCT 8 -----------------------------*/
	/* ------------------------ CODUL TAU DE AICI ---------------------------*/
	c[i*N + j] = a[i*N + j] + b[i*N + j];
	/* ------------------------ CODUL TAU PANA AICI ---------------------------*/
}
