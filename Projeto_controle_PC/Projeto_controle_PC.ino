#include <Encoder.h>

//Objeto encoder com os pinos 2 e 3 (interrupções 0 e 1, respectivamente)
Encoder Direcao(2, 3);   

String Botoes = "";     //String contendo o estado de todos botões (vou enviar ao python)
String Analogicos = ""; //String contendo o valor de todos botões analogicos

long valorEncoder = 0;

//Função setup
void setup() {
  //Iniciando comunicação serial à 115200 baud-rate
  Serial.begin(115200);

  //Colocando os pinos digitais (DESLIGADOS) e analógicos como entradas
  for(byte i = 4; i < 21; i++) {
    (i < 14) ? pinMode(i, INPUT_PULLUP) : pinMode(i, INPUT);
    digitalWrite(i, HIGH);
  }
}

//Loop infinito
void loop() {
  //Se a conexão Serial for estabelecida
  if(Serial) {
      //Leio o estado de todos os botões digitais 
      for(byte BotaoDigital = 4; BotaoDigital < 14; BotaoDigital++) {
        Botoes += !digitalRead(BotaoDigital);
      }

      //Leio o estado de todos botões analógicos 
      for(byte BotaoAnalogico = 14; BotaoAnalogico < 20; BotaoAnalogico++) {
        Analogicos += String(analogRead(BotaoAnalogico)) + ',';
      }

      //Leio o valor do encoder
      valorEncoder = Direcao.read();

      //Envio todos os dados
      Serial.print('A');
      Serial.print(Botoes);
      Serial.print(Analogicos);
      Serial.println(valorEncoder);

      Botoes = "";
      Analogicos = "";
      delayMicroseconds(30000);
  }
}
