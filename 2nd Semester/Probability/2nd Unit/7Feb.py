import numpy
# Supongamos que las calificaciones obtenidas en los examenes
# de 100 estudiantes, la media es de 70 y DE = 5. Cuantos alumnos
# obtuvieron una calificacion entre 60 y 80?

# Generar un arreglo donde la media sea 70 y tenga una desviacion estandar de 5

def prom(nums):
    prom = 0
    for i in range(len(nums)):
        prom += nums[i]

    print(f"Su promedio es de { prom / len(nums) }")
    return prom / len(nums)

def desviacion_estandar(nums, prom):
    suma = 0
    for i in range(len(nums)):
        x = nums[i] - int(prom)
        suma += numpy.power(x ,2)

    de = numpy.sqrt(suma / (len(nums)))

    print(f"Tiene una desviacion estandar de {de}")

x = numpy.random.logistic(loc=70, scale = 2.5, size = 100)
desviacion_estandar(x, prom(x))

# Cuantos alumnos tienen una calificacion entre 60 y 80
entra_rango = 0
for i in range(len(x)):
    if x[i] >= 60 and x[i] <= 80:
        entra_rango += 1

print(f"Los alumnos que tienen entre 60 y 80 son { entra_rango } osea el { entra_rango / len(x)}")
