/*  FUNÇÃO QUE ENVIA TODOS OS DADOS NO BUFFER SERIAL
 *   
 *   Sequência da mensagem:
 *      >Analogicos + Direcão: 
 *        CaractereInicio -> ValorPedais -> ValorDirecao
 *       "A1023,1023,1023,1023,1023,1023,32100,\n"
 *      >Marchas + Botoes
 *        CaractereInicio -> Valor Marcha -> botoes
 *       "M5,0,1,0,1,1"
*/

void sendAnalogState() {
    if(Serial) {
      int bufferCount = sprintf(bufferToSend, "A");

      for(byte analogPin = 14; analogPin < 20; analogPin++) {
        bufferCount += sprintf(bufferToSend + bufferCount, "%d,", analogPin);
      }
      
      //Leio o valor do encoder
      int16_t valorEncoder = gerenciaDirecao();
      bufferCount += sprintf(bufferToSend + bufferCount, "%d,\n", valorEncoder);

      //Envio todos os dados
      Serial.write(bufferToSend, bufferCount);
    }
}

void sendButtonsState() {
  if(Serial) {
    int bufferCount = 1;
    short buttonCount = 12;

    bufferToSend[0] = 'B';
    bufferToSend[10] = '\0';

    for(buttonCount; buttonCount > 3; buttonCount--) {
      bufferToSend[buttonCount - 3] = digitalRead(buttonCount) ? '0' : '1';
    }

    Serial.println(bufferToSend);
  }
}

//Vetor de interrupção
ISR(TIMER2_OVF_vect) {
    TimerAnalogicos++;
    TimerBotoes++;    


    if(TimerAnalogicos > FREQUENCIAATUALIZACAO) {
     sendAnalogState();
      TimerAnalogicos = 0;
    }

    if(TimerBotoes > FREQUENCIABOTOES) {
      sendButtonsState();
      TimerBotoes = 0;
    }
    
   TCNT2 = 130;           //Reseta o timer para 130
   TIFR2 = 0x00;          //Timer2 INT Flag Reg: Clear Timer Overflow Flag
}

void configuraTimer2() {
  /* (125 ciclos) * (128 prescaler) / (16MHz clock speed) = 1ms
   *  
   */
  //Setup Timer2 to fire every 1ms
  TCCR2B = 0x00;        //Disbale Timer2 while we set it up
  TCNT2  = 130;         //Reset Timer Count to 130 out of 255
  TIFR2  = 0x00;        //Timer2 INT Flag Reg: Clear Timer Overflow Flag
  TIMSK2 = 0x01;        //Timer2 INT Reg: Timer2 Overflow Interrupt Enable
  TCCR2A = 0x00;        //Timer2 Control Reg A: Wave Gen Mode normal
  TCCR2B = 0x05;        //Timer2 Control Reg B: Timer Prescaler set to 128
}


