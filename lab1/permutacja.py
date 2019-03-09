# # Permutacja
# def permute(xs, low=0): 
#     if low + 1 >= len(xs):
#         yield xs
#     else:
#         for p in permute(xs, low + 1):
#             yield p        
#         for i in range(low + 1, len(xs)):        
#             xs[low], xs[i] = xs[i], xs[low]
#             for p in permute(xs, low + 1):
#                 yield p        
#             xs[low], xs[i] = xs[i], xs[low]

# for p in permute([1, 2, 3, 4 ]):
#     print (p) 

SIZE = 1        # zmienna przechowujaca rozmiar tablizy kombinacji

# Obliczanie silini
def strong(n):
    if (n <= 0): 
        return 0
    if (n == 1):
        return 1
    n = n * strong(n-1)
    return n

# sprawdzenie czy dana wartosc pojawila sie wczesniej
def check(c, i):                
    for j in range(0, SIZE):
        if (i == c[j]):
            return True
    return False

# przestawie wartosci we wszystkie mosliwe kombinacje
def possibles(array, deep = 0, c = [None] * SIZE):
    cont = [None] * SIZE                   # tablica znakow, ktore zostaly juz uzyte
    for i in range(0, SIZE):
        if ((deep > 0) and (i < deep)):   # wartosci z wyzszej rekurencji
            cont[i] = c[i]
        else:
            cont[i] = -1
    # if (deep == 2):
    #     print('\n')

    for i in range(0, SIZE):
        if (check(cont, i)):    # kazda wartosc bedzie rozwazana tylko raz
            continue            
        cont[deep] = i          # zabezpiecza 'i' przed powtorzeniem
        
        if (deep == SIZE - 1):          # wyswietlenie calej linii z przetasowanymi wartosciami kiedy jestesmy na koncu rekurencji
            for i in range(0, SIZE):
                print(array[cont[i]]),  # w array nie przestawiam wartosci, tablica 'cont' przechowuje jakby indeksy dla 'array', te indeksy sa przetasowane
            print(' ')
            break
        possibles(array, deep+1, cont)
    return

def display(array):             # wyswietlanie wszystkich kombinacji
    possibles(array, 0)


# main
SIZE = input("Podaj liczbe zadan: ")
array = [None] * SIZE
for i in range(0, SIZE):
    array[i] = i+1

display(array)
print('\n')


