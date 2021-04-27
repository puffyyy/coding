import numpy as np
a = np.array([[1, 1], [0, 1]])
b = np.arange(4).reshape((2, 2))
print(a)
print(b)
print(b.dot(a))
print(np.dot(a, b))
