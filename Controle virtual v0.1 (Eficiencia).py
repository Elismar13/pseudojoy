"""
===========================================================================================
    Desenvolvido por: Elismar Silva Pereira
    Data: 10/08/2019
    Versão: 0.1a
"""

#Bibliotecas
import pyvjoy as Vjoy
import serial as sp
import time

control = Vjoy.VJoyDevice(1)  # Assumo o controle 1 para o Vjoy
arduino = sp.Serial("COM3", 115200, timeout=1, write_timeout=1000)  #Inicio minha comunicação serial à 115200Kbps
arduino.flushInput()

while 1:
    time.sleep(0.001)
    message = arduino.readline().decode()
    update = False
    
    if(message != ''):
        data = message[1:-2].split(',')
        if(message[0] == 'A'):
            control.data.wAxisX = int(data[6])*250
            control.data.wAxisY = int(data[1])*32
            control.data.wAxisZ = int(data[2])*32
            control.data.wAxisVX = int(data[3])*32
            control.data.wAxisVY = int(data[4])*32
            control.data.wAxisVZ = int(data[5])*32

            control.update()
        
        elif(message[0] == 'B'):
            buttonCount = 0
            buttonValueToUpdate = 0
            for button in data:
                if(button == '1'):
                    buttonValueToUpdate += 2**buttonCount
                buttonValueToUpdate += 1
            control.data.lButtons = buttonValueToUpdate
            control.update()

    
    # if(arduino.):
    #   #-digitais
    #     botao = 0
    #     for BotaoDigital in BotoesDigitais:
    #         if(BotaoDigital == '1'):
    #             AtualizarBotao += 2**botao
    #         botao += 1

    #     Controle.data
    #     Controle.data.lButtons = AtualizarBotao

    #   #-analogicos
    #     try:
    #         ValorEixo = int(BotaoDigital)
    #     except:
    #         ValorEixo = 512
    #         continue
    #     Controle.data.wAxisX = int(Analogicos[0])*32
    #     print(int(Analogicos[0]))
    #     print(int(Analogicos[0])*64)
    #     Controle.update()
    # atualizar = False

arduino.close()
control.__del__()
