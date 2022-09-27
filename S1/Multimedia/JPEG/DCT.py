import math
import numpy

N = 8


def alpha(a):
    if(a == 0):
        return 1/math.sqrt(2)
    else:
        return 1


def Quantization(mat, coff=5):
    matQuality = [[(coff*(1+i+j)+1) for j in range(N)] for i in range(N)]
    return numpy.divide(numpy.array(mat), numpy.array(matQuality)).astype(int).tolist()


def DeQuantization(mat, coff=5):
    matQuality = [[(coff*(1+i+j)+1) for j in range(N)] for i in range(N)]
    return numpy.multiply(numpy.array(mat), numpy.array(matQuality)).astype(int).tolist()


def IdctTransform(mat):
    lenU = len(mat)
    lenV = len(mat[0])
    dct = [[0 for j in range(lenV)] for i in range(lenU)]
    for u in range(lenU):
        for v in range(lenV):
            sum = 0
            for x in range(N):
                for y in range(N):
                    cosNu = math.cos((2 * u + 1) * x * math.pi / (2 * N))
                    cosNv = math.cos((2 * v + 1) * y * math.pi / (2 * N))
                    sum += mat[x][y] * cosNu * cosNv * alpha(x) * alpha(y)
            dct[u][v] = int(round((2/N) * sum, 0))
    return dct


def dctTransform(mat):
    lenU = len(mat)
    lenV = len(mat[0])
    dct = [[0 for j in range(lenV)] for i in range(lenU)]
    for u in range(lenU):
        for v in range(lenV):
            sum = 0
            for x in range(N):
                for y in range(N):
                    cosNu = math.cos((2 * x + 1) * u * math.pi / (2 * N))
                    cosNv = math.cos((2 * y + 1) * v * math.pi / (2 * N))
                    sum += mat[x][y] * cosNu * cosNv
            dct[u][v] = int(round((2/N) * alpha(u) * alpha(v) * sum, 0))
    return dct


def zigZagFashion(matrix):
    solution = [[] for i in range(2*N-1)]
    for i in range(N):
        for j in range(N):
            sum = i+j
            if(sum % 2 == 0):
                solution[sum].insert(0, matrix[i][j])
            else:
                solution[sum].append(matrix[i][j])
    l = []
    for i in solution:
        for j in i:
            l.append(j)
    return l
