//Declara��o do programa Hotel em disco

#include <iostream>
#include <Windows.h>

using namespace std;

//Defini��es
#define PAUSA							system("PAUSE")
#define LIMPAR_TELA						system("cls")

//Defini��o da acentua��o brasileira
#define ACENTUACAO_BRASILEIRA			setlocale(LC_ALL, "portuguese_brazil")

//Delimita��es do programa
#define QTDE_MAX_QUARTO_ANDAR			20
#define QTDE_MIN_QUARTO_ANDAR			5
#define QTDE_MAX_ANDAR					50
#define QTDE_MIN_ANDAR					10
#define TAMANHO_NOME					50
#define TAMANHO_SOBRENOME				60

//Caminho dos arquivos
#define CAMINHO_INFO_HOTEL				"..//hotel.mp3"
#define CAMINHO_QUARTO					"..//quarto.mp3"


//Defini��es do menu
#define FAZER_CHECK_IN					'C'
#define FAZER_CHECK_OUT					'O'
#define LANCAR_DIARIA					'L'
#define LISTAR_QUARTO					'D'
#define LISTAR_ANDAR					'A'
#define SAIR_PROGRAMA				'S'

//Defini��es das di�rias
#define VALOR_SIMPLES					50.00
#define VALOR_MEDIO						100.00
#define VALOR_SUPER						150.00
#define VALOR_SUITE						200.00

#define DESCONTO_POR_PARENTE			10

//Structs

//Structs para conter informa��es do Hotel
typedef struct tagInfoHotel {
	char nome_hotel[TAMANHO_NOME + 1];				//Para conter o nome do hotel
	int Qtde_andar,									//Para conter a quantidade de andares do hotel
		Qtde_quarto_andar;							//Para conter a quantidade de quartos por andar
}INFO_HOTEL;


//Struct para conter informa��es do Quarto
typedef struct tagQuarto {
	int indiceQuarto;								//Para conter o indice em rela��o ao arquivo
	bool flgOcupado;								//Para saber se o quarto est� livre ou ocupado	
													//True - ocupado
													//False - livre
	char nome[TAMANHO_NOME + 1],					//Para conter o nome do h�spede
		sobrenome[TAMANHO_SOBRENOME + 1];			//Para conter o sobrenome do h�spede
	
	double vlrDiaria,								//Para conter o valor da di�ria
		vlrTotalDiaria;								//Valor total da di�ria


}QUARTO;

//Prot�tipos da fun��o
bool PedirAndarQuarto(int *ptrAndar, int *ptrQuarto, char *ptrTransacao, INFO_HOTEL *ptrInfoHotel);
bool PedirAndar(int *ptrAndar, char *ptrTransacao, INFO_HOTEL *ptrInfoHotel);
int VerificarParentes(char Sobrenome[TAMANHO_SOBRENOME + 1], int QtdeQuartoHotel, FILE *fdQuarto);
bool LeituraPosicional(FILE *fdQuarto, int indice, QUARTO *ptrStQuarto);
bool GravaPosicional(FILE *fdQuarto, int indice, QUARTO *ptrStQuarto);