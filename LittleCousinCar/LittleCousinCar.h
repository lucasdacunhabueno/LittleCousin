/*****************************************************************************
UTFGames LittleCousinCar Library
*****************************************************************************/

//---------------------------------------------------------------------------
#ifndef _LittleCousinCar_H
#define _LittleCousinCar_H
#define FRENTE 1 //Movimento da roda
#define TRAS -1  //Movimento da roda
#define PARAR 0  //Movimento da roda
#define ladoDireito 0  //Lado da roda
#define ladoEsquerdo 1 //Lado da roda
//---------------------------------------------------------------------------

#include <Arduino.h>

/*--LittleCousinCar-DEF_BEGIN--*/
//Pino sensor otico direito
uint_8 pinoSensorDireito = 12;
//Pino sensor otico esquerdo
uint_8 pinoSensorEsquerdo = 13;
uint_8 enableM1 = 5;
uint_8 enableM2 = 6;
uint_8 pin1A = 7;
uint_8 pin3A = 8;


void prepararPinos();
int leRoda(int lado);
void motorDireita(int direcao);
void motorEsquerda(int direcao);

void prepararPinos(){
	pinMode(pinoSensorDireito,0);
	pinMode(pinoSensorEsquerdo,0);
	pinMode(enableM1,1);
	pinMode(enableM2,1);
	digitalWrite(enableM1,0);
	digitalWrite(enableM2,0);
}
void motorDireita(int direcao){
	if(direcao == 1){ //MOVER PARA FRENTE
		digitalWrite(enableM2,1); //ATIVA O MOTOR DA DIREITA
		digitalWrite(pin1A,0);    // ATERRA O PINO 1A
	}
	else
		if(direcao == -1){ //MOVER PARA TRÁS
			digitalWrite(enableM2,1); //ATIVA O MOTOR
			digitalWrite(pin1A,1);    // +5V NO PINO 1A
		}
		else{
			digitalWrite(enableM2,0); //DESATIVA O MOTOR
			digitalWrite(pin1A,0);    // ATERRA O PINO 1A
		}
}
void motorEsquerda(int direcao){
	if(direcao == 1){ //MOVER PARA FRENTE
		digitalWrite(enableM1,1); //ATIVA O MOTOR
		digitalWrite(pin3A,0);    // ATERRA O PINO 3A
	}
	else
		if(direcao == -1){ //MOVER PARA TRÁS
			digitalWrite(enableM1,1); //ATIVA O MOTOR
			digitalWrite(pin3A,1);    // +5V NO PINO 3A
		}
		else{
			digitalWrite(enableM1,0); //DESATIVA O MOTOR
			digitalWrite(pin3A,0);    // ATERRA O PINO 3A
		}
}



int leRoda(int lado){
	return lado == 0 ? digitalRead(pinoSensorDireito) : digitalRead(pinoSensorEsquerdo);
}
/*--LittleCousinCar-DEF_END--*/

#end
