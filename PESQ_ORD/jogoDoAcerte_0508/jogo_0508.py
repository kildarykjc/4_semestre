import random 

computador = round(random.randint(0, 100)) 
print('Estou pensando em um número de 0 a 100') 
print('Vamos começar ... ') 
acertou = False 
tentativas = 0 
while not acertou: 
    jogador = int(input('Em que número estou pensando? ')) 
    tentativas += 1 
    if jogador == computador: 
        acertou = True 
    else: 
        if jogador < computador: 
            print('É Maior... Continue.') 
        elif jogador > computador: 
            print('É menor... Continue.') 
print('Parabéns, acertou com {} tentativas. '.format(tentativas)) 

