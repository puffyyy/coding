class boolmatrix(object):
    def __init__(self, n):
        self.matrix = [[0] * (n) for i in range(n)]
        self.lenth = n

    def deepcopy(self):
        n = self.lenth
        ret = boolmatrix(n)
        for i in range(n):
            for j in range(n):
                ret.matrix[i][j] = self.matrix[i][j]
        return ret

    def muli(self, x):
        n = self.lenth
        temp = boolmatrix(self.lenth)
        for i in range(n):
            for j in range(n):
                # temp.matrix[i][j] = 0
                for k in range(n):
                    temp.matrix[i][j] |= self.matrix[i][k] & x.matrix[k][j]
        return temp

    def union(self, x):
        n = self.lenth
        for i in range(n):
            for j in range(n):
                self.matrix[i][j] = self.matrix[i][j] | x.matrix[i][j]
        return self


'''
    def pow(self, n):
        res = boolmatrix(self.lenth)
        while n:
            if n & 1:
                res = res.muli(self)
            res = res.ownmul()
            n >>= 1
        return res
'''


class ralation(object):
    def __init__(self, n):
        self.R_matrix = boolmatrix(n)
        self.T_Rmatrix = None
        self.pre_i_matrix = None
        self.cnt = 0

    def update_ralation(self, row, col):
        if (not self.R_matrix.matrix[row - 1][col - 1]):
            self.cnt += 1
        self.R_matrix.matrix[row - 1][col - 1] = 1

    '''
        def insert_matrix(self):
            n = input()
            n = int(n)
            for i in range(n):
                x = int(input())
                y = int(input())
                self.update_ralation(x, y)
    '''

    def read_matrix(self):
        f = []
        n = self.R_matrix.lenth
        for i in range(n):
            f = input().split(" ")
            for j in range(n):
                if int(f[j]):
                    self.update_ralation(i + 1, j + 1)

    def general_union(self):
        self.pre_i_matrix = self.R_matrix.deepcopy()
        self.T_Rmatrix = self.R_matrix.deepcopy()
        for i in range(self.cnt):
            self.T_Rmatrix.union(self.pre_i_matrix)
            self.pre_i_matrix = self.pre_i_matrix.muli(self.R_matrix)
        return self.T_Rmatrix

    def print_mat(self):
        n = self.R_matrix.lenth
        for i in range(n):
            for j in range(n):
                print(self.T_Rmatrix.matrix[i][j], end=" ")
            print()


if __name__ == "__main__":
    size = input()
    size = int(size)
    R = ralation(size)
    R.read_matrix()
    R.general_union()
    R.print_mat()
