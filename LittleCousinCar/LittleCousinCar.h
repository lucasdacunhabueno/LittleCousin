/*****************************************************************************
  UTFGames LittleCousinCar Library v0.7 ALPHA
  AUTHOR: LUCAS DA CUNHA BUENO (Don't change this!) 
	
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
#ifndef _LittleCousinCar_H
#define _LittleCousinCar_H
#define FRENTE 1  //Movimento da roda
#define TRAS -1 //Movimento da roda
#define PARAR 0 //Movimento da roda
#define ladoEsquerdo 0  //Lado da roda
#define ladoDireito 1 //Lado da roda
//---------------------------------------------------------------------------

#include <Arduino.h>
#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

/*--LittleCousinCar-DEF_BEGIN--*/
int passoPadrao = 10; //Numero padrão de passos da roda
uint_8 pinoSensorEsquerdo = 12; //Pino sensor otico esquerdo
uint_8 pinoSensorDireito = 13;  //Pino sensor otico direito
uint_8 enableM1 = 5;  //Pino ENABLE do motor 1
uint_8 enableM2 = 6;  //Pino ENABLE do motor 2
uint_8 pin1A = 7; //Pino 1A do motor 1
uint_8 pin3A = 8; //Pino 3A do motor 2
uint_8 pinCE = 9; //Pino CE do nRF24l01
uint_8 pinCNS = 10; //Pino CNS do nRF24l01
uint_8 pinBuzzer = 4; //Pino Buzzer
RF24 radio(9,10); //Pinos do nRF24l01 (CE,CSN) 
const uint64_t pipe = 0xE8E8F0F0E1LL;

void prepararPinos(); //Define os terminais do CI de acordo com suas devidas tarefas (Entrada ou Saida) e freia os motores
int leRoda(int lado); //Realiza a leitura do sensor ótico localizado nas rodas para saber sua posição
void motorDireita(int direcao); //Realiza operações com o motor do lado direito ( Motor 2 )
void motorEsquerda(int direcao);  //Realiza operações com o motor do lado esquerdo ( Motor 1 )
bool movimentaFrente(int passos); //Movimenta o carro para frente um determinado número de passos
bool movimentaTras(int passos); //Movimenta o carro para trás um determinado número de passos
bool rotacionaEsquerda(int passos); //Rotaciona o carro para esquerda um determinado número de passos
bool rotacionaDireita(int passos);  //Rotaciona o carro para direita um determinado número de passos
bool igualaRodas(); //Posiciona as duas rodas no inicio do passo
bool pararRodas();  //Para as duas rodas
bool enviaDados(String texto);  //Envia string via RF
String recebeDados(); //Recebe string via RF

void prepararPinos(){ 
  pinMode(pinoSensorDireito,0);
  pinMode(pinoSensorEsquerdo,0);
  pinMode(enableM1,1);
  pinMode(enableM2,1);
  pinMode(pinBuzzer,1);
  digitalWrite(enableM1,0);
  digitalWrite(enableM2,0);
  tone(pinBuzzer,1500);
  delay(150);
  noTone(pinBuzzer,1500);
  iniciaCom();  
}
bool enviaDados(String texto){
  int msg[1];
  radio.begin();
  radio.openWritingPipe(pipe);
  int messageSize = texto.length();
  for (int i = 0; i < messageSize; i++) {zs
    int charToSend[1];
    charToSend[0] = texto.charAt(i);
    radio.write(charToSend,1);
  }  
  msg[0] = 2; 
  radio.write(msg,1);
  radio.powerDown(); 
  delay(1000);
  radio.powerUp();
  return true;
}
String recebeDados(){
  int msg[1];
  int lastmsg = 1;
  String texto = "";
  radio.begin();
  radio.openReadingPipe(1,pipe);
  radio.startListening();
  if (radio.available()){
    bool done = false;  
    done = radio.read(msg, 1); 
    char theChar = msg[0];
    while(msg[0] != 2)
      theMessage.concat(theChar);
  }
  radio.powerDown(); 
  delay(1000);
  radio.powerUp();
  return texto;
}
void motorEsquerda(int direcao){
  if(direcao == 1){           //MOVER PARA FRENTE
    digitalWrite(enableM1,1); //ATIVA O MOTOR
    digitalWrite(pin1A,1);    // +5V NO PINO 1A
  }
  else
    if(direcao == -1){           //MOVER PARA TRÁS
      digitalWrite(enableM1,1);  //ATIVA O MOTOR
      digitalWrite(pin1A,0);     // ATERRA O PINO 1A
    }
    else
      digitalWrite(enableM1,0); //DESATIVA O MOTOR
}
void motorDireita(int direcao){
  if(direcao == 1){           //MOVER PARA FRENTE
    digitalWrite(enableM2,1); //ATIVA O MOTOR
    digitalWrite(pin3A,1);    // +5V NO PINO 3A
  }
  else
    if(direcao == -1){           //MOVER PARA TRÁS
      digitalWrite(enableM2,1);  //ATIVA O MOTOR
      digitalWrite(pin3A,0);     // ATERRA O PINO 3A
    }
    else
      digitalWrite(enableM1,0); //DESATIVA O MOTOR
}
int leRoda(int lado){
  return lado == 0 ? digitalRead(pinoSensorDireito) : digitalRead(pinoSensorEsquerdo);
}
bool igualaRodas(){
  int i = leRoda(0);  //Le roda direita  
  while(leRoda(0) == i)
    motorDireita(1);
  delay(10);
  motorDireita(0);
  i = leRoda(1);
  while(leRoda(1) == i)
    motorEsquerda(1);
  delay(10);
  pararRodas();
  return true;
}
bool movimentaFrente(int passos){ 
  if(igualaRodas()){
    for(int i = passos; passos > 0; i--){
      int roda = leRoda(0);
      motorDireita(1);
      motorEsquerda(1);
      while( roda == leRoda(0) )
        delay(10);
    }
  }
  pararRodas();
  return true;
}
bool movimentaTras(int passos){ 
  if(igualaRodas()){
    for(int i = passos; passos > 0; i--){
      int roda = leRoda(0);
      motorDireita(-1);
      motorEsquerda(-1);
      while( roda == leRoda(0) )
        delay(10);
    }
  }
  mpararRodas();
  return true;
}
bool rotacionaDireita(int passos){ 
  if(igualaRodas()){
    for(int i = passos; passos > 0; i--){
      int roda = leRoda(0);
      motorDireita(-1);
      motorEsquerda(1);
      while(roda == leRoda(0))
        delay(10);
    }
  }
  pararRodas();
  return true;
}
bool rotacionaEsquerda(int passos){ 
  if(igualaRodas()){
    for(int i = passos; passos > 0; i--){
      int roda = leRoda(0);
      motorDireita(1);
      motorEsquerda(-1);
      while(roda == leRoda(0))
        delay(10);
    }
  }
  pararRodas();
  return true;
}
void pararRodas(){
  motorDireita(0);
  motorEsquerda(0);
}

/*--LittleCousinCar-DEF_END--*/

#end
