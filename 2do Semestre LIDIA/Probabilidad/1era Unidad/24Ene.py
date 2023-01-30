from modulos import conjuntos as set

A = [2, 4, 5, 6, 1, 10]
B = [3, 9, 1, 2, 4, 6]

S = set.union(A, B)

# Remake insersection
print("(A ∩ B): ")
print(set.interseccion(A, B))

print("(A ∪ B): ")
print(set.union(A, B))

print("(~A ∩ B): ")
print(set.union(set.complemento(A, S), B))

print("(~A ∪ ~B): ")
print(set.union(set.complemento(A, S), set.complemento(B, S)))
