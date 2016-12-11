//Funções do programa de Hotel em disco

#include "Header.h"

//Função para pedir um andar e um quarto válido
//	Parametros
//		Entrada:
//			int *ptrAndar ------------------------------------- Ponteiro que aponta para a variável andar
//			int *ptrQuarto ------------------------------------ Ponteiro que aponta para a variável quarto
//			char *ptrTransacao --------------------------------- Transação
//			INFO_HOTEL *ptrInfoHotel -------------------------- Ponteiro de Struct para armazenar as informações do Hotel
//		Saída:
//			True - dados inseridos OK
//			False - Usuário cancelou a operação
bool PedirAndarQuarto(int *ptrAndar, int *ptrQuarto, char *ptrTransacao, INFO_HOTEL *ptrInfoHotel)
{

	cout << "\n\t" << ptrTransacao<<endl;

	do {

		cout << "Insira um andar válido entre 1 e " << ptrInfoHotel->Qtde_andar << endl
			<<"Ou zero para cancelar a transação: ";
		cin >> *ptrAndar;


	} while (*ptrAndar < 0 || *ptrAndar > ptrInfoHotel->Qtde_andar);

	if (*ptrAndar == 0)
		return false;

	do {

		cout << "Insira um quarto válido entre 1 e " << ptrInfoHotel->Qtde_quarto_andar << endl
			<< "Ou zero para cancelar a transação: ";
		cin >> *ptrQuarto;


	} while (*ptrQuarto < 0 || *ptrQuarto > ptrInfoHotel->Qtde_quarto_andar);

	if (*ptrQuarto == 0)
		return false;

	return true;

}

//Função para pedir um andar válido
//	Parametros
//			int *ptrAndar------------------------------------ - Ponteiro que aponta para a variável andar
//			char *ptrTransacao --------------------------------- Transação
//			INFO_HOTEL *ptrInfoHotel -------------------------- Ponteiro de Struct para armazenar as informações do Hotel
//			True - dados inseridos OK
//			False - Usuário cancelou a operação
bool PedirAndar(int *ptrAndar, char *ptrTransacao, INFO_HOTEL *ptrInfoHotel)
{
	cout << "\n\t" << ptrTransacao << endl;

	do {

		cout << "Insira um andar válido entre 1 e " << ptrInfoHotel->Qtde_andar << endl
			<< "Ou zero para cancelar a transação: ";
		cin >> *ptrAndar;


	} while (*ptrAndar < 0 || *ptrAndar > ptrInfoHotel->Qtde_andar);

	if (*ptrAndar == 0)
		return false;

	return true;

}

//Função que verifica a quantidade de parentes 
//	Parâmetros
//		Entrada:
//			char Sobrenome[TAMANHO_SOBRENOME + 1] ----------------------- Char para receber o sobrenome
//			int QtdeQuartoHotel ----------------------------------------- Quantidade de quartos no Hotel
//			FILE *fdQuarto ---------------------------------------------- File descriptor para o arquivo quarto.mp3
//		Saída: a quantidade de parentes que a função encontrou
int VerificarParentes(char Sobrenome[TAMANHO_SOBRENOME + 1], int QtdeQuartoHotel, FILE *fdQuarto)
{

	QUARTO stQuarto;						//Struct para conter informações do quarto
	int nContador = 0;						//Contador para quantidade de parentes
	int i;									//Contador genérico

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

//Função para ler o arquivo posicionalmente
//	Parâmetros
//		Entrada:
//			FILE *fdQuarto --------------------------------- Ponteiro File Descriptor do arquivo quarto.mp3
//			int indice ------------------------------------- Indice do arquivo
//			QUARTO *ptrStQuarto ---------------------------- Struct para conter as informações do quarto
//		Saída:
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

//Função para gravar o arquivo posicionalmente
//	Parâmetros
//		Entrada:
//			FILE *fdQuarto --------------------------------- Ponteiro File Descriptor do arquivo quarto.mp3
//			int indice ------------------------------------- Indice do arquivo
//			QUARTO *ptrStQuarto ---------------------------- Struct para conter as informações do quarto
//		Saída:
//			True - Gravação ok
//			False - Erro de seek ou de gravação

bool GravaPosicional(FILE *fdQuarto, int indice, QUARTO *ptrStQuarto)
{

	if (fseek(fdQuarto, indice * sizeof(QUARTO), SEEK_SET) != 0)//Erro de seek;
		return false;

	if (fwrite(ptrStQuarto, sizeof(QUARTO), 1, fdQuarto) == 0)//Erro de gravação
		return false;

	return true;

}