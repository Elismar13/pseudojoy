#include <avr/interrupt.h>
#include <avr/io.h>
#include <Encoder.h>

#define FREQUENCIAATUALIZACAO 30

Encoder Direcao(2, 3);    //Objeto encoder com os pinos 2 e # (interrupções 0 e 1, respectivamente)
int16_t ValorEncoder = 0;
bool envia = false;
byte Timer = 0;

//Função setup
void setup() {
  Serial.begin(115200);  //Iniciando comunicação serial à 115200 baud-rate
  configuraTimer2();      //Configurando timer2 para envio de dados Serial
  
  //Colocando os pinos digitais (DESLIGADOS) e analógicos como entradas
  for(byte i = 4; i < 21; i++) {
    if(i < 14) pinMode(i, INPUT_PULLUP);
    pinMode(i, INPUT);
    digitalWrite(i, HIGH);
  }
}

//Loop infinito
void loop() {
  enviaDados();
}
