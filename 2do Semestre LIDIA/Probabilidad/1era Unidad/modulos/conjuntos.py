def interseccion(A, B):
    _A = A[:]
    _B = B[:]
    _C = []

    # Append all the repeated elements
    for eA in _A:
        for eB in _B:
            if eA == eB:
                _C.append(eA)

    _C.sort()
    return _C

def union(A, B):
    _A = A[:]
    _B = B[:]
    _C = []
    # Remove all duplicated elements
    for eA in _A:
        for eB in _B:
            if eA == eB:
                _B.remove(eB)

    _C.extend(_A)
    _C.extend(_B)

    _C.sort()
    return _C


def complemento(A, S):
    _A = A[:]
    _S = S[:]

    for eA in _A:
        for eS in _S:
            if eS == eA:
                _S.remove(eS)

    return _S

def diferencia(A, B):
    _A = A[:]
    _B = B[:]

    for eA in _A:
        for eB in _B:
            if eA == eB:
                _A.remove(eA)

    return _A