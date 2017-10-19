#include <Python.h>
#include <arrayobject.h>

static PyObject* indices1D(PyObject *self, PyObject *args) {
  /*
  Steps through an array and records the index of the first appearance
  of each possible value in a Python dictionary. The array must be
  one-dimensional, of type 'int32'.
  */
  PyArrayObject *imageDataArray;
  PyObject *indexDictionary;
  if (!PyArg_ParseTuple(args, "O", &imageDataArray))
  {
    PyErr_SetString(PyExc_ValueError,"argument error");
    return NULL;
  }
  indexDictionary = PyDict_New();
  int size = imageDataArray->dimensions[0];
  int i = 0;
  for (; i<size; i++) {
    int arrayItem = *(int *) PyArray_GETPTR1(imageDataArray, i);
    PyObject *pyArrayItem = PyLong_FromLong(arrayItem);
    if (!PyDict_Contains(indexDictionary, pyArrayItem)) {
      // Insert the item in the dictionary.
      // PyDict_SetItem is responsible for maintaining its own references,
      // so we'll need to call Py_DECREF on the keys and values.
      PyObject *index = PyLong_FromLong(i);
      PyDict_SetItem(indexDictionary, pyArrayItem, index);
      Py_DECREF(index);
    }
    Py_DECREF(pyArrayItem);
  }
  return indexDictionary;
}

static PyObject* indices1Dshort(PyObject *self, PyObject *args) {
  /*
  An alternate version of the above function that uses an array to store
  example indices instead of putting them directly in a Python dictionary.
  May be a faster alternative but initial testing didn't show a dramatic
  speed-up.
  */
  PyArrayObject *imageDataArray;
  PyArrayObject *indexMap;
  int maxValue;
  if (!PyArg_ParseTuple(args, "Oi", &imageDataArray, &maxValue))
  {
    PyErr_SetString(PyExc_ValueError,"argument error");
    return NULL;
  }
  int dim[1] = {maxValue};
  indexMap = (PyArrayObject *) PyArray_FromDims(1, dim, PyArray_INT);
  PyArray_FILLWBYTE(indexMap, -1);
  int size = imageDataArray->dimensions[0];
  int i = 0;
  for (; i<size; i++) {
    unsigned short arrayItem = *(unsigned short *) PyArray_GETPTR1(imageDataArray, i);
    if (arrayItem < maxValue) {
      int *mapIndex = (int *) PyArray_GETPTR1(indexMap, arrayItem);
      if (*mapIndex < 0) {
        *mapIndex = i;
      }
    }
  }
  return PyArray_Return(indexMap);
}

static PyMethodDef ExtMethods[] = {
  {"indices1D", indices1D, METH_VARARGS, "indices1D docstring"},
  {"indices1Dshort", indices1Dshort, METH_VARARGS, "indices1Dshort docstring"},
  {NULL,NULL,0,NULL}
};

static struct PyModuleDef exampleIndicesModule = {
  PyModuleDef_HEAD_INIT, "exampleIndices", NULL, -1, ExtMethods, NULL, NULL, NULL, NULL
};

PyMODINIT_FUNC PyInit_exampleIndices(void) {
  PyObject *module;
  module = PyModule_Create(&exampleIndicesModule);
  if (!module) return NULL;
  import_array();
  return module;
}

