#define RESETADIRECAO  4
#define NUMMARCHAS     8
#define PINDADOSMARCHA 5

byte gerenciaMarcha() {
  for(byte i = 0; i < NUMMARCHAS; i++) {
    switch(i) {
      case 0:
        digitalWrite(2, 0);
        digitalWrite(3, 0);
        digitalWrite(4, 0);
        break; 
      case 1:
        digitalWrite(2, 1);
        digitalWrite(3, 0);
        digitalWrite(4, 0);
        break; 
      case 2:
        digitalWrite(2, 0);
        digitalWrite(3, 1);
        digitalWrite(4, 0);
        break; 
      case 3:
        digitalWrite(2, 1);
        digitalWrite(3, 1);
        digitalWrite(4, 0);
        break; 
      case 4:
        digitalWrite(2, 0);
        digitalWrite(3, 0);
        digitalWrite(4, 1);
        break;
      case 5:
        digitalWrite(2, 1);
        digitalWrite(3, 0);
        digitalWrite(4, 1);
        break; 
      case 6:
        digitalWrite(2, 0);
        digitalWrite(3, 1);
        digitalWrite(4, 1);   
        break; 
      case 7:
        digitalWrite(2, 1);
        digitalWrite(3, 1);
        digitalWrite(4, 1);   
        break; 
    }
  
    if(!digitalRead(PINDADOSMARCHA)) return i+1;  //Marcha ativada
    delayMicroseconds(500);
  }
  return 0;     //Se nada for ativado, então o cambio se encontra no neutro
}

int16_t gerenciaDirecao() {
  if(!digitalRead(RESETADIRECAO)) {
    Direcao.write(0);
    return 0;
  }
  else return Direcao.read();
}

int16_t gerenciaPedais(byte PinoPedal) {
  return analogRead(PinoPedal);
}
