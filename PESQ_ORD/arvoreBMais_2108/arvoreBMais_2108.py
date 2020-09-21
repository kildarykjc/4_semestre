class No(object): 
    def __init__(self, ordem): 
        self.ordem = ordem 
        self.chaves = [] 
        self.valores = [] 
        self.folha = True 

    def split(self): 
        esquerdo = No(self.ordem) 
        direito = No(self.ordem) 
        meio = self.ordem // 2 
        esquerdo.chaves = self.chaves[:meio] 
        esquerdo.valores = self.valores[:meio] 
        direito.chaves = self.chaves[meio:] 
        direito.valores = self.valores[meio:] 
        self.chaves = [direito.chaves[0]] 
        self.valores = [esquerdo, direito] 
        self.folha = False 

    def cheio(self): 
        return len(self.chaves) == self.ordem 

    def adicionar(self, chave, valor): 
        if not self.chaves: 
            self.chaves.append(chave) 
            self.valores.append([valor]) 
            return None 
        for i, item in enumerate(self.chaves): 
            if chave == item: 
                self.valores[i].append(valor) 
                break 
            elif chave < item: 
                self.chaves = self.chaves[:i] + [chave] + self.chaves[i:] 
                self.valores = self.valores[:i] + [[valor]] + self.valores[i:] 
                break 
            elif i + 1 == len(self.chaves): 
                self.chaves.append(chave) 
                self.valores.append([valor]) 
    

    def mostrar(self, counter=0): 
        print(counter, str(self.chaves)) 
        if not self.folha: 
            for item in self.valores: 
                item.mostrar(counter + 1) 

class ArvoreBMais(object): 
    def __init__(self, ordem=8): 
        self.root = No(ordem) 

    def inserir(self, chave, valor): 
        parent = None 
        child = self.root 
        while not child.folha: 
            parent = child 
            child, index = self._encontrar(child, chave)
        child.adicionar(chave, valor) 
        if child.cheio(): 
            child.split() 
            if parent and not parent.cheio(): 
                self._juntar(parent, child, index) 

    def _encontrar(self, no, chave): 
        for i, item in enumerate(no.chaves): 
            if chave < item: 
                return no.valores[i], i 
        return no.valores[i + 1], i + 1 

    def _juntar(self, parent, child, index): 
        parent.valores.pop(index) 
        pivot = child.chaves[0] 
        for i, item in enumerate(parent.chaves): 
            if pivot < item: 
                parent.chaves = parent.chaves[:i] + [pivot] + parent.chaves[i:]
                parent.valores = parent.valores[:i] + child.valores + parent.valores[i:] 
                break 
            elif i + 1 == len(parent.chaves): 
                parent.chaves += [pivot] 
                parent.valores += child.valores 
                break 

    
    def mostrar(self): 
        self.root.mostrar() 
                
    def recuperar(self, chave): 
        child = self.root 
        while not child.folha: 
            child, index = self._encontrar(child, chave) 
        for i, item in enumerate(child.chaves): 
            if chave == item: 
                return child.valores[i] 
        return None 

    

def teste(): 
    print('Iniciando ´Arvore B+...') 
    arvore = ArvoreBMais(ordem=4) 
    print('\n´Arvore B+ com 1 item...') 
    arvore.inserir('a', 'agua') 
    arvore.mostrar() 
    print('\n´Arvore B+ com 2 items...') 
    arvore.inserir('b', 'bicicleta') 
    arvore.mostrar() 
    print('\n´Arvore B+ com 3 items...') 
    arvore.inserir('c', 'carro') 
    arvore.mostrar() 
    print('\n´Arvore B+ com 4 items...') 
    arvore.inserir('d', 'dado') 
    arvore.mostrar() 
    print('\n´Arvore B+ com 5 items...') 
    arvore.inserir('e', 'escola') 
    arvore.mostrar() 
    print('\n´Arvore B+ com 6 items...') 
    arvore.inserir('f', 'faca') 
    arvore.mostrar() 
    print('\nRetornando valor da chave a...') 
    print(arvore.recuperar('a')) 
    print('\nRetornando valor da chave c...') 
    print(arvore.recuperar('c')) 
if __name__ == '__main__': 
    print('\n') 
    teste() 