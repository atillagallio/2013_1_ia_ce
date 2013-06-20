#include <iostream>
#include <cstdlib>
#include <cmath>
#include <unistd.h>

#define NR_BITS 4

using namespace std;


typedef struct _Gene
{
	int alelo; /*Valor do gene */
	int locus; /*Posição do gene*/
}Gene;

/*Genótipo: Estrutura, indivíduo candidato à seleção x*/
/*Fenótipo: Solução, valor da função f(x) para um dado indivíduo*/

typedef struct _Cromossomo
{
//	Gene gene;
	int numero;
	int numero_bits;
	int* bit;
}Cromossomo;

void print_cromossomo (Cromossomo *c)
{
	cout << "Cromossomo " << c->numero << endl;

	for (int i = 0; i < c->numero_bits; ++i)
	{
		cout << c->bit[i] << " ";
	}

	cout << endl;
}

int randomize_bit ()
{
	usleep ((rand() % 9) + 1);
	return rand() % 2;
}

Cromossomo* randomize_cromossomo(int nr)
{
	sleep(1);
	Cromossomo *cromossomo;
	cromossomo = (Cromossomo *) malloc (sizeof (Cromossomo));
	cromossomo->numero = nr;
	cromossomo->numero_bits = NR_BITS;
	cromossomo->bit = (int *) malloc (sizeof (int) * cromossomo->numero_bits);

	for (int i = 0; i < cromossomo->numero_bits; ++i)
		cromossomo->bit[i] = randomize_bit();

//	cout << "Cromossomo Criado!" << endl;
	print_cromossomo(cromossomo);
	cout << endl;
	sleep(1);
	return cromossomo;
}

int crossover (Cromossomo* c1, Cromossomo* c2)
{
//	cout << "Doing crossover!" << endl;

	int split;
	usleep (rand() % 4);
	split = (rand() % (NR_BITS - 1) + 1);

//	cout << "Split on: " << split+1 << endl;

	if (c1->numero_bits != c2->numero_bits)
		return -1;

	int numero_bits = c1->numero_bits;

	int temp;

//	cout << "Before crossover!" << endl;

//	print_cromossomo(c1);
//	print_cromossomo(c2);

	for (int i = split; i < numero_bits; ++i)
	{
		temp = c1->bit[i];
		c1->bit[i] = c2->bit[i];
		c2->bit[i] = temp;
	}

//	cout << "After crossover!" << endl;

//	print_cromossomo(c1);
//	print_cromossomo(c2);

//	cout << endl;
	return 0;
}

int main()
{
	/*crossover: troca duas partes entre cromossomo, iniciais ou finais*/

	srand (time (NULL));
	int numero = 1;

	Cromossomo *cromossomo_1;
	cromossomo_1 = randomize_cromossomo(numero);

	numero++;

	Cromossomo *cromossomo_2;
	cromossomo_2 = randomize_cromossomo(numero);

	numero++;

	Cromossomo *cromossomo_3;
	cromossomo_3 = randomize_cromossomo(numero);

	int err;
	err = crossover(cromossomo_1, cromossomo_2);
	if (err < 0)
		cout << "Erro no crossover: " << err;

	err = crossover(cromossomo_1, cromossomo_3);
	if (err < 0)
		cout << "Erro no crossover: " << err;

	err = crossover(cromossomo_2, cromossomo_3);
	if (err < 0)
		cout << "Erro no crossover: " << err;

	print_cromossomo(cromossomo_1);
	print_cromossomo(cromossomo_2);
	print_cromossomo(cromossomo_3);


	return 0;
}
