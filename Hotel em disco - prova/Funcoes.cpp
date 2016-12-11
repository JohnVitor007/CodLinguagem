//Fun��es do programa de Hotel em disco

#include "Header.h"

//Fun��o para pedir um andar e um quarto v�lido
//	Parametros
//		Entrada:
//			int *ptrAndar ------------------------------------- Ponteiro que aponta para a vari�vel andar
//			int *ptrQuarto ------------------------------------ Ponteiro que aponta para a vari�vel quarto
//			char *ptrTransacao --------------------------------- Transa��o
//			INFO_HOTEL *ptrInfoHotel -------------------------- Ponteiro de Struct para armazenar as informa��es do Hotel
//		Sa�da:
//			True - dados inseridos OK
//			False - Usu�rio cancelou a opera��o
bool PedirAndarQuarto(int *ptrAndar, int *ptrQuarto, char *ptrTransacao, INFO_HOTEL *ptrInfoHotel)
{

	cout << "\n\t" << ptrTransacao<<endl;

	do {

		cout << "Insira um andar v�lido entre 1 e " << ptrInfoHotel->Qtde_andar << endl
			<<"Ou zero para cancelar a transa��o: ";
		cin >> *ptrAndar;


	} while (*ptrAndar < 0 || *ptrAndar > ptrInfoHotel->Qtde_andar);

	if (*ptrAndar == 0)
		return false;

	do {

		cout << "Insira um quarto v�lido entre 1 e " << ptrInfoHotel->Qtde_quarto_andar << endl
			<< "Ou zero para cancelar a transa��o: ";
		cin >> *ptrQuarto;


	} while (*ptrQuarto < 0 || *ptrQuarto > ptrInfoHotel->Qtde_quarto_andar);

	if (*ptrQuarto == 0)
		return false;

	return true;

}

//Fun��o para pedir um andar v�lido
//	Parametros
//			int *ptrAndar------------------------------------ - Ponteiro que aponta para a vari�vel andar
//			char *ptrTransacao --------------------------------- Transa��o
//			INFO_HOTEL *ptrInfoHotel -------------------------- Ponteiro de Struct para armazenar as informa��es do Hotel
//			True - dados inseridos OK
//			False - Usu�rio cancelou a opera��o
bool PedirAndar(int *ptrAndar, char *ptrTransacao, INFO_HOTEL *ptrInfoHotel)
{
	cout << "\n\t" << ptrTransacao << endl;

	do {

		cout << "Insira um andar v�lido entre 1 e " << ptrInfoHotel->Qtde_andar << endl
			<< "Ou zero para cancelar a transa��o: ";
		cin >> *ptrAndar;


	} while (*ptrAndar < 0 || *ptrAndar > ptrInfoHotel->Qtde_andar);

	if (*ptrAndar == 0)
		return false;

	return true;

}

//Fun��o que verifica a quantidade de parentes 
//	Par�metros
//		Entrada:
//			char Sobrenome[TAMANHO_SOBRENOME + 1] ----------------------- Char para receber o sobrenome
//			int QtdeQuartoHotel ----------------------------------------- Quantidade de quartos no Hotel
//			FILE *fdQuarto ---------------------------------------------- File descriptor para o arquivo quarto.mp3
//		Sa�da: a quantidade de parentes que a fun��o encontrou
int VerificarParentes(char Sobrenome[TAMANHO_SOBRENOME + 1], int QtdeQuartoHotel, FILE *fdQuarto)
{

	QUARTO stQuarto;						//Struct para conter informa��es do quarto
	int nContador = 0;						//Contador para quantidade de parentes
	int i;									//Contador gen�rico

	for (i = 0; i < QtdeQuartoHotel; i++)
	{
		
		if (fseek(fdQuarto, i * sizeof(QUARTO), SEEK_SET) != 0)//Erro de seek ?
			return 0;
		if (fread_s(&stQuarto, sizeof(QUARTO), sizeof(QUARTO), 1, fdQuarto) == 0)//Erro de leitura
			return 0;

		if (strcmp(stQuarto.sobrenome, Sobrenome) == 0)
			nContador++;
	}

	return nContador;

}

//Fun��o para ler o arquivo posicionalmente
//	Par�metros
//		Entrada:
//			FILE *fdQuarto --------------------------------- Ponteiro File Descriptor do arquivo quarto.mp3
//			int indice ------------------------------------- Indice do arquivo
//			QUARTO *ptrStQuarto ---------------------------- Struct para conter as informa��es do quarto
//		Sa�da:
//			True - Leitura ok
//			False - Erro de seek ou de leitura

bool LeituraPosicional(FILE *fdQuarto, int indice, QUARTO *ptrStQuarto)
{

	if (fseek(fdQuarto, indice * sizeof(QUARTO), SEEK_SET) != 0)//Erro de seek ?
		return false;

	if (fread_s(ptrStQuarto, sizeof(QUARTO), sizeof(QUARTO), 1, fdQuarto) == 0)//Erro de leitura
		return false;

	return true;

}

//Fun��o para gravar o arquivo posicionalmente
//	Par�metros
//		Entrada:
//			FILE *fdQuarto --------------------------------- Ponteiro File Descriptor do arquivo quarto.mp3
//			int indice ------------------------------------- Indice do arquivo
//			QUARTO *ptrStQuarto ---------------------------- Struct para conter as informa��es do quarto
//		Sa�da:
//			True - Grava��o ok
//			False - Erro de seek ou de grava��o

bool GravaPosicional(FILE *fdQuarto, int indice, QUARTO *ptrStQuarto)
{

	if (fseek(fdQuarto, indice * sizeof(QUARTO), SEEK_SET) != 0)//Erro de seek;
		return false;

	if (fwrite(ptrStQuarto, sizeof(QUARTO), 1, fdQuarto) == 0)//Erro de grava��o
		return false;

	return true;

}