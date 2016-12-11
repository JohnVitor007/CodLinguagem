//Programa de Hotel em disco
//John Vitor da Silva Quispe - 10/12/2016 - Versão 0.1

#include "Header.h"

//Entry Point do programa

void main(void)
{

	int i, j,							//Indices genérico
		nAndar,							//Para conter o número do andar
		nQuarto,						//Para conter o número do quarto
		nIndice,						//Para conter o índice do quarto
		nQtdeParentes;
		
	double vlrDiaria,					//Para conter o valor da diária
		vlrTotal = 0.0;

	bool flgTemGente;					//Para ver se tem hóspede num certo andar

	char cWork[200],					//Para o uso da sprintf_s
		cOpcao;							//Para a opção do operador

	FILE *fdInfoHotel,					//File descriptor para hotel.mp3
		*fdQuarto;						//File descriptor para quarto.mp3

	INFO_HOTEL *ptrInfoHotel,			//Ponteiro de struct para conter informações do infoHotel;
		stInfoHotel;					//Struct para conter informações do Hotel

	QUARTO stQuarto;					//Struct para conter informações do quarto Hotel

	SYSTEMTIME stTime;					//Para conter a data e hora do sistema

	ptrInfoHotel = &stInfoHotel;		//Atribuindo o endereço de memória ao ponteiro

	ACENTUACAO_BRASILEIRA;

	if(fopen_s(&fdInfoHotel, CAMINHO_INFO_HOTEL, "r+b") != 0)//Deu erro em abrir o arquivo
	{ 
		if (fopen_s(&fdInfoHotel, CAMINHO_INFO_HOTEL, "w+b") != 0)
		{//Erro irecuperável
			
			cout << "Erro na abertura do arquivo " << CAMINHO_INFO_HOTEL << endl;
			PAUSA;
			return;			//Retorn ao S.0

		}

		//Configuração do arquivo hotel.mp3
		cout << "\n\tPROGRAMA DE GERENCIAMENTO DE HOTEL - CONFIGURAÇÃO DO PROGRAMA" << endl;
		

		cout << "\nInsira o nome do Hotel: ";
		cin.getline(ptrInfoHotel->nome_hotel, TAMANHO_NOME, '\n');

		do {

			cout << "Insira a quantidade de andar válido entre " << QTDE_MIN_ANDAR << " e " << QTDE_MAX_ANDAR << ": " ;
			cin >> ptrInfoHotel->Qtde_andar;

		} while (ptrInfoHotel->Qtde_andar < QTDE_MIN_ANDAR || ptrInfoHotel->Qtde_andar > QTDE_MAX_ANDAR);

		do {

			cout << "Insira a quantidade de quartos por andar válido entre " << QTDE_MIN_QUARTO_ANDAR << " e " << QTDE_MAX_QUARTO_ANDAR << ": ";
			cin >> ptrInfoHotel->Qtde_quarto_andar;

		} while (ptrInfoHotel->Qtde_quarto_andar < QTDE_MIN_QUARTO_ANDAR || ptrInfoHotel->Qtde_quarto_andar > QTDE_MAX_QUARTO_ANDAR);

		if (fwrite(ptrInfoHotel, sizeof(INFO_HOTEL), 1, fdInfoHotel) == 0)
		{
			cout << "Erro de gravação" << endl;
			PAUSA;
			return;
			fclose(fdInfoHotel);
		}

		fclose(fdInfoHotel);

		if (fopen_s(&fdQuarto, CAMINHO_QUARTO, "w+b") != 0)
		{//Erro irecuperável 
			cout << "Erro de irrecuperável" << endl;
			PAUSA;
			return;	
			fclose(fdQuarto);
		}

		for (i = 1; i <= ptrInfoHotel->Qtde_andar; i++)
		{
			for (j = 0; j < ptrInfoHotel->Qtde_quarto_andar; j++)
			{

				stQuarto.flgOcupado = false;
				stQuarto.indiceQuarto = (i - 1) * ptrInfoHotel->Qtde_quarto_andar + j;
				stQuarto.nome[0] = NULL;
				stQuarto.sobrenome[0] = NULL;
				stQuarto.vlrTotalDiaria = 0.0;

				switch (i)
				{

				case 0:
				case 1:
					stQuarto.vlrDiaria = VALOR_SIMPLES;
					break;
				case 2:
				case 3:
					stQuarto.vlrDiaria = VALOR_MEDIO;
					break;
				case 4:
				case 5:
					stQuarto.vlrDiaria = VALOR_SUPER;
					break;

				default:
					stQuarto.vlrDiaria = VALOR_SUITE;

				}

				if (fwrite(&stQuarto, sizeof(QUARTO), 1, fdQuarto) == 0)
				{//Erro de gravação

					cout << "Erro de gravação" << endl;
					PAUSA;
					return;				//Retorna ao S.O
					fclose(fdQuarto);

				}
			
			}
		}

		LIMPAR_TELA;
		cout << "\nO HOTEL " << ptrInfoHotel->nome_hotel << " possui: " << endl
			<< "- " << (i - 1) << " Andares." << endl
			<<"- "<< j << " Quartos por andar"<<endl;
		PAUSA;

		LIMPAR_TELA;

		cout << "\n\tFORAM GRAVADOS " << (i - 1) * j << " REGISTROS" << endl;
		PAUSA;

	}
	else {
	
		if (fread_s(ptrInfoHotel, sizeof(INFO_HOTEL), sizeof(INFO_HOTEL), 1, fdInfoHotel) == 0)
		{//Erro de leitura ?
			cout << "Erro de leitura" << endl;
			PAUSA;
			return;			//retorna ao S.O
			fclose(fdInfoHotel);
		}


		if (fopen_s(&fdQuarto, CAMINHO_QUARTO, "r+b") != 0)
		{//Erro de abertura do arquivo
			cout << "Erro de abertura do arquivo " << CAMINHO_QUARTO << endl;
			PAUSA;
			return;				//Retorna ao S.0
			fclose(fdQuarto);
		}

		if (fread_s(&stQuarto, sizeof(QUARTO), sizeof(QUARTO), 1, fdQuarto) == 0)
		{//Erro de leitura
			cout << "Erro de leitura"<<endl;
			PAUSA;
			return;
		}
		
	}

	GetLocalTime(&stTime);
	
	while (true)
	{

		LIMPAR_TELA;

		sprintf_s(cWork, sizeof(cWork), "\n\tFATEC DE MOGI - SISTEMA DE GERENCIAMENTO DE HOTEL EM DISCO\n\t %2s - Dia %02d/%02d/%04d às %02d:%02d",
			ptrInfoHotel->nome_hotel, stTime.wDay, stTime.wMonth, stTime.wYear, stTime.wHour, stTime.wMinute);

		cout << cWork<<endl;

		cout << "\n\tEscolha uma das opções abaixo: "<<endl
			<< "\t\t" << FAZER_CHECK_IN << " - Fazer Check-In" << endl
			<< "\t\t" << FAZER_CHECK_OUT << " - Fazer Check-out" << endl
			<< "\t\t" << LANCAR_DIARIA << " - Lançar Diária" << endl
			<< "\t\t" << LISTAR_QUARTO << " - Listar Quarto" << endl
			<< "\t\t" << LISTAR_ANDAR << " - Listar Andar" << endl
			<< "\t\t" << SAIR_PROGRAMA << " - Sair do Programa" << endl
			<< "\tSelecione: ";

		cin >> cOpcao;

		cOpcao = toupper(cOpcao);

		switch (cOpcao)
		{
			case FAZER_CHECK_IN:

				if (!PedirAndarQuarto(&nAndar, &nQuarto, "FAZER CHECK-IN", ptrInfoHotel))
					break;

				nIndice = (nAndar - 1) * ptrInfoHotel->Qtde_quarto_andar + (nQuarto - 1);

				if (!LeituraPosicional(fdQuarto, nIndice, &stQuarto)) 
				{
					cout << "Erro de leitura" << endl;
					PAUSA;
					break;
				}

				if (stQuarto.flgOcupado)
				{
					cout << "O quarto está ocupado por " << stQuarto.nome<<endl;
					PAUSA;
					break;
				}

				cin.ignore(1, EOF);

				cout << "Insira o nome: ";
				cin >> stQuarto.nome;

				cout << "Insira o sobrenome: ";
				cin >> stQuarto.sobrenome;
				
				stQuarto.flgOcupado = true;

				if (!GravaPosicional(fdQuarto, nIndice, &stQuarto))
				{
					cout << "Erro de gravação" << endl;
					PAUSA;
					break;
				}

				break;
			
			case FAZER_CHECK_OUT:

				if (!PedirAndarQuarto(&nAndar, &nQuarto, "FAZER CHECK-OUT", ptrInfoHotel))
					break;

				nIndice = (nAndar - 1) * ptrInfoHotel->Qtde_quarto_andar + (nQuarto - 1);

				if (!LeituraPosicional(fdQuarto, nIndice, &stQuarto)) {
					cout << "Erro de leitura" << endl;
					PAUSA;
					break;
				}

				if (stQuarto.flgOcupado == false)
				{
					cout << "O quarto está livre" << endl;
					PAUSA;
					break;
				}
				
				sprintf_s(cWork, sizeof(cWork), "Nome %s\nSobrenome: %s\nValor diária: %2.2f\nTotal diária: %2.2f\nDeseja fazer Check-out ? (S ou N):",
					stQuarto.nome, stQuarto.sobrenome, stQuarto.vlrDiaria, stQuarto.vlrTotalDiaria);

				cout << cWork;
				cin >> cOpcao;

				cOpcao = toupper(cOpcao);
				
				if (cOpcao == 'S')
				{

					stQuarto.flgOcupado = false;
					stQuarto.vlrTotalDiaria = 0.0;
					stQuarto.nome[0] = NULL;
					stQuarto.sobrenome[0] = NULL;
					if (!GravaPosicional(fdQuarto, nIndice, &stQuarto))
					{
						cout << "Erro de gravação" << endl;
						PAUSA;
						break;
					}

				}
				else
					break;

				cout << "Quarto desocupado, retornando ao menu inicial" << endl;
				PAUSA;

				break;

			case LANCAR_DIARIA:

				cout << "Data: " << stTime.wDay << "/" << stTime.wMonth << "/" << stTime.wYear << " - Hora: " << stTime.wHour << ":" << stTime.wMinute << endl
					<< "Deseja lançar diária ? (S ou N):";

				cin >> cOpcao;

				cOpcao = toupper(cOpcao);

				if (cOpcao == 'S')
				{

					for (i = 0; i < ptrInfoHotel->Qtde_andar * ptrInfoHotel->Qtde_quarto_andar; i++)
					{
					
						if (!LeituraPosicional(fdQuarto, i, &stQuarto))
						{
							cout << "Erro de leitura" << endl;
							PAUSA;
							break;
						}

						if (stQuarto.flgOcupado)
						{
						
							//Verificando a quantidade de parentes
							nQtdeParentes = VerificarParentes(stQuarto.sobrenome, ptrInfoHotel->Qtde_andar * ptrInfoHotel->Qtde_quarto_andar, fdQuarto);
							
							//Calculando o valor da diária com desconto
							vlrDiaria = stQuarto.vlrDiaria - (stQuarto.vlrDiaria / 100) * ((nQtdeParentes - 1)* DESCONTO_POR_PARENTE);
							stQuarto.vlrTotalDiaria += vlrDiaria;

							if (!GravaPosicional(fdQuarto, i, &stQuarto))
							{
								cout << "Erro de gravação" << endl;
								PAUSA;
								break;
							}


						}//If
						
					}//For i

				}
				else {

				break;


					cout << "Ação cancelada. Voltando ao menu" << endl;
					PAUSA;

				}
				break;
			case LISTAR_QUARTO:

				if (!PedirAndarQuarto(&nAndar, &nQuarto, "LISTAR UM QUARTO", ptrInfoHotel))
					break;

				nIndice = (nAndar - 1) * ptrInfoHotel->Qtde_quarto_andar + (nQuarto - 1);

				if (!LeituraPosicional(fdQuarto, nIndice, &stQuarto)) {
					cout << "Erro de leitura" << endl;
					PAUSA;
					break;
				}

				if (stQuarto.flgOcupado == false)
				{
					cout << "O quarto está livre" << endl;
					PAUSA;
					break;
				}

				sprintf_s(cWork, sizeof(cWork), "Nome %s\nSobrenome: %s\nValor diária: %2.2f\nTotal diária: %2.2f",
					stQuarto.nome, stQuarto.sobrenome, stQuarto.vlrDiaria, stQuarto.vlrTotalDiaria);
		
				cout << cWork << endl;
				PAUSA;
				
				break;

			case LISTAR_ANDAR:
				
				vlrTotal = 0;

				if (!PedirAndar(&nAndar, "LISTAR UM ANDAR", ptrInfoHotel))
					break;

				sprintf_s(cWork, sizeof(cWork), "Quarto		Nome		Sobrenome	Valor diária	Total Diária\n");
				cout << cWork << endl;

				for (i = (nAndar - 1)*ptrInfoHotel->Qtde_quarto_andar, flgTemGente = false; i < nAndar * ptrInfoHotel->Qtde_quarto_andar; i++)
				{

					if (!LeituraPosicional(fdQuarto, i, &stQuarto))
					{
						cout << "Erro de Leitura";
						PAUSA;
						break;
					}
					
					if (stQuarto.flgOcupado)
					{
						flgTemGente = true;
						sprintf_s(cWork, sizeof(cWork), "%-15d %-15s %-15s %5.2f %15.2f",
							(i + 1) - (nAndar - 1) * ptrInfoHotel->Qtde_quarto_andar, stQuarto.nome, stQuarto.sobrenome, stQuarto.vlrDiaria, stQuarto.vlrTotalDiaria);
						cout << cWork << endl;
						vlrTotal += stQuarto.vlrTotalDiaria;

						//(i + 1) - ((nAndar * ptrInfoHotel->Qtde_quarto_andar) - 1)
					}
				}

				sprintf_s(cWork, sizeof(cWork), "\n						Lucro obtido: %6.2f", vlrTotal);
				cout << cWork << endl;
				PAUSA;
				break;

			case SAIR_PROGRAMA:
				cout << "Tem certeza ? (S ou N): ";
				cin >> cOpcao;
				cOpcao = toupper(cOpcao);

				if (cOpcao == 'S')
				{
					fclose(fdInfoHotel);
					fclose(fdQuarto);
					return;	//Retorna ao S.O
				}

				break;
				
		default:
			cout << "Opção Inválida" << endl;
			PAUSA;
			break;
		}//Switch

	}//While

}//Main