"""
===========================================================================================
    Desenvolvido por: Elismar Silva Pereira
    Data: 10/08/2019
    Versão: 0.1a
"""

#Bibliotecas
import pyvjoy as Vjoy
import serial as sp

#Objetos
Controle = Vjoy.VJoyDevice(1)  # Assumo o controle 1 para o Vjoy
arduino = sp.Serial("COM3", 115200, timeout=1, write_timeout=1000)  #Inicio minha comunicação serial à 115200Kbps
arduino.flushInput()

#Variáveis
botao = 1
receber = False
Atualizar = False
mensagem = ""

#loop infinito
while 1:
    recebido = arduino.read(1)
    AtualizarBotao = 0
    ValorEixo = 0

    #Crio uma string com o valor de todos botões, separadas com uma vírgula
    #E em seguida separo-as
    if (recebido == 'A'.encode()):
        receber = True
        continue

    elif (recebido == '\n'.encode()):
        PinosArduino = mensagem.split(',')
        BotoesDigitais = PinosArduino[:12]
        Analogicos = PinosArduino[12:18]
        receber = False

        #print("Digitais: ", BotoesDigitais)
        #print("Analogicos: ", Analogicos)

        mensagem = ""
        Atualizar = True
        
    if (receber):
        mensagem += recebido.decode()


    #Quando eu receber tudo, atualizo os valores do botoes digitais e analogicos
    if(Atualizar):
      #-digitais
        botao = 0
        for BotaoDigital in BotoesDigitais:
            if(BotaoDigital == '1'):
                AtualizarBotao += 2**botao
            botao += 1

        Controle.data
        Controle.data.lButtons = AtualizarBotao

      #-analogicos
        try:
            ValorEixo = int(BotaoDigital)
        except:
            ValorEixo = 512
            continue
        Controle.data.wAxisX = int(Analogicos[0])*32
        #print(int(Analogicos[0]))
        #print(int(Analogicos[0])*64)
        Controle.update()
    atualizar = False

arduino.close()
Controle.__del__()
