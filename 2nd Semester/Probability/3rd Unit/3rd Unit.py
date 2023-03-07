import numpy as np
import scipy.stats as st

# Definir la muestra
np.random.seed(0)
datos = np.random.randint(8, 35, 40)

# Crear un intervalo de confianza del 95 porciento
intervalo = st.norm.interval(confidence=0.95, loc=np.mean(datos), scale=st.sem(datos))
print(intervalo)
