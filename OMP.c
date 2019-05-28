OpenMP:
#include "pch.h"
#include <iostream>
#include <omp.h>
/* --------------------------------------------------------------------
Implementați un program ce calculează produsul a 2 matrici
cu N linii și N coloane iar apoi paralelizați programul utilizand
OpenMP
Urmati, pe rand, pasii de mai jos.
--------------------------------------------------------------------*/
int main()
{
	// Numarul N de linii/coloane
	int N = 1000;
	// Prima matrice
	int *a;
	// A 2-a matrice
	int *b;
	// Matricea rezultat
	int *c;
	/* --------------------------------------------------------------------
	1. Alocati memorie pe host pentru cele trei matrici:
	0.333 puncte
	--------------------------------------------------------------------*/
	/* ------------------------ REZOLVARE PCT 1 -----------------------------*/
	/* ------------------------ CODUL TAU DE AICI ---------------------------*/
	a = new int[N*N];
	b = new int[N*N];
	c = new int[N*N];
	/* ------------------------ CODUL TAU PANA AICI ---------------------------*/
	/* --------------------------------------------------------------------
	2. Initializați matricile a si b dupa cum urmeaza: elementele de pe prima coloana
	au valoarea 1, elementele de pe a 2-a coloana au valoarea 2, cele de pe a
	3-a au valoarea 4, etc
	0.333 puncte
	--------------------------------------------------------------------*/
	/* ------------------------ REZOLVARE PCT 2 -----------------------------*/
	/* ------------------------ CODUL TAU DE AICI ---------------------------*/
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			a[i*N + j] = j+1;
		}
	}

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			b[i*N + j] = j + 1;
		}
	}
	/* ------------------------ CODUL TAU PANA AICI ---------------------------*/
	/* --------------------------------------------------------------------
	3. Implementați inmultirea celor doua matrici si scrieti rezultatul in
	matiricea c
	0.333 puncte
	--------------------------------------------------------------------*/
	/* ------------------------ REZOLVARE PCT 3 -----------------------------*/
	/* ------------------------ CODUL TAU DE AICI ---------------------------*/
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
			for (int k = 0; k < N; k++)
			{
				c[i*N + j] = a[i*N + k] * b[k*N + j];
			}
	}
	/* ------------------------ CODUL TAU PANA AICI ---------------------------*/
	/* --------------------------------------------------------------------
	4. Implementați varianta paralela a calculului de la cerinta precedenta
	Indicatie: doar bucla for exterioara (ce parcurge liniile) se distribuie
	pe mai multe fire de executie
	1 punct
	--------------------------------------------------------------------* /
	/* ------------------------ REZOLVARE PCT 4 -----------------------------*/
	/* ------------------------ CODUL TAU DE AICI ---------------------------*/
	omp_set_num_threads(4);
#pragma omp parallel
	
	int id = omp_get_thread_num();

	int totalThreads = omp_get_num_threads();

	int start = N / totalThreads * id;
	int end = N / totalThreads * (id + 1);

	for (int i = start; i < end; i++)
	{
		for (int j = 0; j < N; j++)
			for (int k = 0; k < N; k++)
			{
				c[i*N + j] = a[i*N + k] * b[k*N + j];
			}
	}
	/* ------------------------ CODUL TAU PANA AICI ---------------------------*/
}
