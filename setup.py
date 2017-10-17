from distutils.core import setup, Extension
import os

NUMPY_INCLUDE_PATH = '/usr/lib/python2.7/dist-packages/numpy/core/include/numpy/'

pyArrayUtils = Extension('pyArrayUtils.exampleIndices',
                         sources = ['lib/exampleIndices.c'],
                         include_dirs = [NUMPY_INCLUDE_PATH])

setup(name='pyArrayUtils',
      version = '0.0',
      description = 'Array processing utilities.',
      author = 'Tim Credo',
      package_dir = {'pyArrayUtils': 'lib'},
      packages = ['pyArrayUtils'],
      ext_modules = [pyArrayUtils],
      requires = ['numpy'])

