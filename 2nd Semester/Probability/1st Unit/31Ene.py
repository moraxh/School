import random
# De una urna con diez pelotas blancas y cinco pelotas negras,
# se extraen sucesivamente y sin reemplazo (sin regresar
# pelotas a la urna), dos pelotas al azar.
#
# ¿Cuál es la probabilidad de que ambas pelotas sean negras?
#
# A: la primera pelota extraída es negra
# B: la segunda pelota extraída es negra

def rellenar_urna ():
    _urna = []
    blancas = 10
    negras = 5

    for i in range(15):
        if random.randint(0, 1) == 0:
            if negras > 0:
                negras-=1
                _urna.append(0);
            else:
                blancas-=1
                _urna.append(1)
        else:
            if blancas > 0:
                blancas-=1
                _urna.append(1)
            else:
                negras-=1
                _urna.append(0)

    return _urna


urna = rellenar_urna()

vueltas = 100000
dos_negras = 0

for i in range(vueltas):
    bola = random.randrange(0, len(urna))
    if urna[bola] == 0:
        urna.pop(bola)

        bola = random.randrange(0, len(urna))
        if urna[bola] == 0:
            dos_negras += 1

    urna.clear()
    urna = rellenar_urna()

print(f"Las probabilidades de que las dos bolas sean negras(A ∩ B) es de: { (dos_negras / vueltas)*100 }%")
