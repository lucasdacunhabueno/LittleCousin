/*****************************************************************************
UTFGames LittleCousinCenter Library
*****************************************************************************/

//---------------------------------------------------------------------------
#ifndef LittleCousinCenter_H
#define _LittleCousinCenter_H
//---------------------------------------------------------------------------
#include <Arduino.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <RF24_config.h>
/*--LittleCousinCenter-DEF_BEGIN--*/

//Pinos do eixo X
uint_8 x[4] = {2, 3, 4, 5};
//Pinos do eixo y
uint_8 y[4] = {8, 9, 10, 11};
//Pino para o botao iniciar
uint_8 pinoComecar = 6;
//Pino de leitura
uint_8 pinoLeitura = 7;

//Valor de leitura para ir para frente
int frente = 100;
//Valor de leitura para ir para esquerda
int esquerda = 200;
//Valor de leitura para ir para direita
int direita = 300;
//Valor de leitura para executar a funcao
int funcao = 400;
//vetor com os movimentos a serem executados
int movimento[16];

//Prepara os pinos para iniciar
void prepararPinos(){
	pinMode(pinoComecar, 0);
	pinMode(pinoLeitura, 0);
	for(int i = 0; i < 4; i++){
		pinMode(x[i], 1);
		pinMode(y[i], 1);
		digitalWrite(x[i],0);
		digitalWrite(y[j],0);
	}
}

//Ler entradas
int leituraDasEntradas(){
	int rodadas = 0;
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			digitalWrite(x[i],1);
			digitalWrite(y[j],1);
			movimento[rodadas] = analogRead(pinoLeitura);
			rodadas++;
			digitalWrite(x[i],0);
			digitalWrite(y[j],0);
		}
	}
}






/*--LittleCousinCenter-DEF_END--*/

#endif
