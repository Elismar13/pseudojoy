#define NUMMARCHAS   8
#define PINDADOSMARCHA 5

byte gerenciaMarcha(Cambio cambio) {
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
        safas
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
  return 0;     //Se nada for ativado, então ta no neutro
}

//Zero o conteudo do encoder
if(!digitalRead(4)) Direcao.readAndReset();
