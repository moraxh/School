from modules.sets import *

A = [2, 4, 5, 6, 1, 10]
B = [3, 9, 1, 2, 4, 6]

S = union(A, B)

# Remake insersection
print("(A ∩ B): ")
print(intersection(A, B))

print("(A ∪ B): ")
print(union(A, B))

print("(~A ∩ B): ")
print(intersection(complement(A, S), B))

print("(~A ∪ ~B): ")
print(union(complement(A, S), complement(B, S)))
