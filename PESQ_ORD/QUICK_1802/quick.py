import matplotlib as mpl
import matplotlib.pyplot as plt
import random 
import timeit
import sys
sys.setrecursionlimit(10**8)
def desenhaGrafico(x,y,y2,xl = "Entradas", yl = "Saídas"):
    fig = plt.figure(figsize=(10, 8))
    ax = fig.add_subplot(111)
    ax.plot(x,y, label = "Lista Aleatória")
    ax.plot(x,y2, label = "Lista Invertida")
    ax.legend(bbox_to_anchor=(1, 1),bbox_transform=plt.gcf().transFigure)
    plt.ylabel(yl)
    plt.xlabel(xl)
    fig.savefig('Grafico_quick.png')

def geraAleatorio(tam):
    x = list(range(tam))
    #random.shuffle(x)
    return x

def sort(lista):
    menor = []
    igual = []
    maior = []

    if len(lista) > 1:
        pivot = lista[0]
        for x in lista:
            if x < pivot:
                menor.append(x)
            elif x == pivot:
                igual.append(x)
            elif x > pivot:
                maior.append(x)
                # Don't forget to return something!
        
        return sort(menor)+igual+sort(maior)  # Just use the + operator to join lists
            # Note that you want equal ^^^^^ not pivot
    else:  # You need to handle the part at the end of the recursion - when you only have one element in your array, just return the array.
        return lista


x = [1000, 20000, 30000, 60000]
#x = [100, 200, 300, 600]
y_aleatorio = []
y_reverso = []
tempo_aleatorio = []
tempo_reverso = []

for i in range(len(x)):
    y_aleatorio.append(geraAleatorio(x[i]))
    lista_reversa = list(range(1, x[i]))
    lista_reversa = lista_reversa[::-1]
    y_reverso.append(lista_reversa)

for i in range(len(x)):
    tempo_aleatorio.append(timeit.timeit("sort({})".format(y_aleatorio[i]), setup="from __main__ import sort", number=1))
    tempo_reverso.append(timeit.timeit("sort({})".format(y_reverso[i]), setup="from __main__ import sort", number=1))
print(sys.getrecursionlimit())

desenhaGrafico(x,tempo_aleatorio,tempo_reverso)