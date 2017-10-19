from exampleIndices import indices1D, indices1Dshort
import numpy, random

def findExampleIndices(array):
  """This function returns a dictionary containing all the values in
     the given integer array as keys, with values that each correspond
     to an example index where the array's value is the key."""
  flattenedArray = array.astype("int32").flatten()
  indices = {}
  for k, v in indices1D(flattenedArray).items():
    indices[k] = unflattenIndex(v, array.shape)
  return indices

def findExampleIndicesShort(array):
  """An alternate version of the above that tries to make some optimizations
     for speed. The array's type is restricted to an unsigned short (two bytes)
     and the underlying C code uses an array instead of working directly with
     a Python dictionary."""
  flattenedArray = array.astype("uint16").flatten()
  maxValue = array.max() + 1
  indices = {}
  for i, index in enumerate(indices1Dshort(flattenedArray, maxValue)):
    if index >= 0:
      indices[i] = unflattenIndex(index, array.shape)
  return indices

def unflattenIndex(index, shape):
  """Converts an index into a flattened array into a multidimensional index
     into the original array. Relies on arrays being flattened in 'C-style'
     order, which is default for numpy."""
  indices = []
  i = index
  for d in shape[::-1]:
    i, remainder = i//d, i%d
    indices.append(remainder)
  assert i==0
  return indices[::-1]

def test():
  result = findExampleIndicesShort(numpy.array([10000*[i] for i in range(10000)]))
  assert len(result)==10000 # Check that we have all the items.
  for k, index in result.items():
    assert index[0]==k # Check that the row is correct.
    assert index[1]==0 # Check that we take the first value in the row.

if __name__=="__main__":
  test()
