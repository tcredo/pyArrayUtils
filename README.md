# pyArrayUtils
Python utilities implemented in C for performance gains.

The current version has been built and tested with Python 3. You will need to install the Python dev files before building.

For Ubuntu you can run:
```
sudo apt-get install python3-dev python3-numpy
```

Depending on your system you may also need to adjust the NUMPY_INCLUDE_PATH variable in setup.py.

Once the environment is ready you can build the module:
```
python3 setup.py build
```

How to use:
```python
import numpy, pyArrayUtils
array = numpy.array([[1, 2, 3], [4, 5, 6]])
print(pyArrayUtils.exampleIndices(array))
# {1: [0, 0], 2: [0, 1], 3: [0, 2], 4: [1, 0], 5: [1, 1], 6: [1, 2]}
```
