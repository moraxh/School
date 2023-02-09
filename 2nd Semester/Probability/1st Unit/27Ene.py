import random

# Se tiene una baraja inglesa y se saca una carta al azar. Sea los eventos:
# Nota: en la baraja inglesa hay 52 cartas, la mitad son rojas y la mitad negras. Con 4 palos (c,d,p,t).
#
# A: sacar un as
# B: sacar una carta roja
#
# Resultados de ejercicios
# P(A)      = 4/52  = 7.69%
# P(B)      = 36/52 = 50%
# P(A ∩ B)  = 1/26  = 3.8%
#
# En este codigo se intentara ejecutar una serie de eventos para ver si estas posibilidades son ciertas
# 1 <= As Rojo <= 2
# 1 <= Rojo <= 36
# 37 <= As Negro <= 39
# 37 <= Negro <= 52

vueltas = 1000000
carta   = 0

as_rojo  = 0
rojo     = 0
as_negro = 0
negro    = 0

for i in range(vueltas):
    carta = random.randrange(53)

    if carta % 2 == 0:
        rojo+=1

        if 2 == carta or carta == 4:
            as_rojo+=1
    else:
        negro+=1

        if 3 == carta or carta == 5:
            as_negro+=1
    print(f"\n{(i / vueltas) * 100}%")

print(f"\nLas probabilidades que sea rojo: {rojo / vueltas} ")
print(f"\nLas probabilidades que sea un as rojo: {as_rojo / vueltas} ")
print(f"\nLas probabilidades que sea negro: {negro / vueltas} ")
print(f"\nLas probabilidades que sea un as negro: {as_negro / vueltas} ")
