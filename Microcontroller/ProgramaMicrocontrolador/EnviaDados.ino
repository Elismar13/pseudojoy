
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

//Vetor de interrupção
ISR(TIMER2_OVF_vect) {
    TimerAnalogicos++;
    TimerBotoes++;
    
    if(TimerAnalogicos > FREQUENCIAATUALIZACAO) {
      enviaDados('A');     
      TimerAnalogicos = 0;
    }
    if(TimerBotoes > FREQUENCIABOTOES) {
      enviaDados('B');
      TimerBotoes   = 0;
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

void enviaDados( char opcao ) {
  //Se a conexão Serial for estabelecida
  if(Serial) {

    switch(opcao){
      case('A'):
        String Analogicos = "";   //String contendo o valor de todos botões analogicos
  
        //Leio o estado de todos botões analógicos 
        for(byte BotaoAnalogico = 14; BotaoAnalogico < 20; BotaoAnalogico++) {
          Analogicos += String(analogRead(BotaoAnalogico));
          Analogicos += ',';
        }
      
        //Leio o valor do encoder
        ValorEncoder = gerenciaDirecao();
  
        //Envio todos os dados
        Serial.print('A');
        Serial.print(Analogicos);
        Serial.println(ValorEncoder);

      Analogicos = "";
      break;
      
      case('B'):
        String Botoes = "";

        for(byte i = 4; i < 21; i++) {
          Botoes += i;
        }
        Serial.print('B');
        Serial.println(Botoes);
        break;
    }
  }
}
