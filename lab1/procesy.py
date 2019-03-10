import permutacja       # umozliwia dostep do funkcji znajdujacych sie w pliku "permutacja.py"

# SIZE = input("Podaj liczbe zadan: ")
# array = [None] * SIZE
# for i in range(0, SIZE):
#     array[i] = i+1

# permutacja.display(array)

#  klasa "zadanie" przechowujaca informacje o danm zadaniu
class Zadanie:
    def __init__(self, nrZadania, nrMaszyny=0, wykonywane=False, skonczone=False, czasStart = 0):
        self.nrZadania  = int(nrZadania)
        self.czas       = []                # tablica przechowujaca czasy wykonania zadania
        self.nrMaszyny  = int(nrMaszyny)
        self.wykonywane = wykonywane                # przechowuje informacje czy zaadanie jest wykonywanie na ktorejs z maszyn
        self.skonczone  = []                # przechowuje informacje czy zadanie jest skonczone dla kazdej z maszyn osobno
        self.czasStart  = []         # czas rozpoczecia pracy maszyny

    def dodajCzas(self, czas):          self.czas.append(czas)
    def dodajSkonczone(self, skoncz):   self.skonczone.append(skoncz)
    def dodajCzasStart(self, start):   self.czasStart.append(start)

    def setWykonywanie(self, w):    self.wykonywane = w
    def setSkonczone(self, s, i):      
        self.skonczone[i] = s

    def getCzas(self):          return self.czas
    def getWykonywanie(self):   return self.wykonywane
    def getSkonczone(self):     return self.skonczone
    def getCzasStart(self):     return self.czasStart

Cmax = 0
l_maszyn = 1
l_zadan = input("Podaj liczbe zadan: ")
zadanie = [None] * l_zadan      # tablica przechowujaca zadania
for i in range(0, l_zadan):
    zadanie[i] = Zadanie(i)     # utworzenie nowego obiektu
    for j in range(0, l_maszyn):
        print("Podaj czas wykonania zadania ", i+1, "dla maszyny", j+1)
        t = input()
        zadanie[i].dodajCzas(t)             # dodanie czasu do tablicy w klasie
        zadanie[i].dodajSkonczone(False)    # status ukonczenia zadania

print('Podane czasy:')
for i in range(0, l_zadan):
    print(zadanie[i].getCzas())

# wykonywanie zadania
for nr_zad in range(0, l_zadan):
    koniec = False
    while not koniec:       # cykl wykonywania zadan na maszynach
        Cmax = Cmax + 1     # czas wykonania
        for maszyna in range(0, l_maszyn):
            # przypadek kiedy zadanie sie dopiero rozpoczyna
            if not zadanie[nr_zad].getWykonywanie() and not zadanie[nr_zad].getSkonczone()[maszyna]:     
                zadanie[nr_zad].setWykonywanie(True)    # ustawia zadanie jako wykonywane
                a = Cmax-1
                zadanie[nr_zad].dodajCzasStart(a)       # ustawia czas rozpoczecia zadania

            if zadanie[i].getCzas()[maszyna] == Cmax - zadanie[nr_zad].getCzasStart()[maszyna]:       # sprawdza czy maszyna sie wykonala
                zadanie[nr_zad].setWykonywanie(False)
                zadanie[nr_zad].setSkonczone(True, maszyna)
                koniec = True
            if not koniec: break

                # potrzebna funkcja ktora bedzie sprawdzac tez poprzednie zadania na kolejnych maszynach

print("Czasz wykonania to:", Cmax)




