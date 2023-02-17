import random

# En un juego una persona lanza un dado las veces que quiera,
# y las reglas del juego son las siguientes: si el dado cae
# en la cara 1, 2, 3 o 4, entonces la persona pierde 5 dólares,
# pero, si el dado cae en los lados 5 o 6, entonces la persona
# gana 10 dólares. Calcular la esperanza matemática de este juego

vueltas = 100000

total = 0
ganado = 0

for i in range(vueltas):
    total += ganado
    ganado = 0

    for j in range(10):
        num = random.randint(1, 6)

        if num > 0 and num < 5:
            ganado = ganado - 5
        else:
            ganado = ganado + 10

print(f"En promedio se gano { total / vueltas }")
