/*****************************************************************************
  UTFGames LittleCousinCenter Library
  
	This file is part of LittleCousin.
	
  LittleCousin is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.
  
  LittleCousin is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  
  You should have received a copy of the GNU General Public License
  along with LittleCousin.  If not, see <http://www.gnu.org/licenses/>.

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

/*--LittleCousinCente
