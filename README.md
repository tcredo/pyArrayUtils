# pyArrayUtils
Python utilities implemented in C for performance gains.

How to build:
```
python setup.py build
```

How to use:
```python
import numpy, pyArrayUtils
array = numpy.array([[1, 2, 3], [4, 5, 6]])
print pyArrayUtils.exampleIndices(array)
# {1: [0, 0], 2: [0, 1], 3: [0, 2], 4: [1, 0], 5: [1, 1], 6: [1, 2]}
```
