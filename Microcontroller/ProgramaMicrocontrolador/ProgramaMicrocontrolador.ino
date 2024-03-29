#include <avr/interrupt.h>
#include <avr/io.h>
#include <Encoder.h>

#define FREQUENCIAATUALIZACAO 30  //Envio dados a cada 16.6ms
#define FREQUENCIABOTOES      200   //Envio dados a cada 200ms

//Objeto encoder com os pinos 2 e 3 (interrupções 0 e 1, respectivamente)
Encoder Direcao(2, 3);    

//Variáveis de tempo
byte TimerAnalogicos = 0;
byte TimerBotoes     = 0;

char bufferToSend[100];

//Função setup
void setup() {
  //Iniciando comunicação serial a 115200 baud-rate
  Serial.begin(115200);   
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);

  //Configurando timer2 para envio de dados Serial
  configuraTimer2();      
  
  //Colocando os pinos digitais (DESLIGADOS) e analógicos como entradas
  for(byte i = 4; i < 21; i++) {
    (i < 14) ? pinMode(i, INPUT_PULLUP) : pinMode(i, INPUT);
    digitalWrite(i, HIGH);
  }
}

//Loop infinito
void loop() {
  
}
