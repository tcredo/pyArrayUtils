from distutils.core import setup, Extension
import os

NUMPY_INCLUDE_PATH = '/usr/lib/python3/dist-packages/numpy/core/include/numpy/'

pyArrayUtils = Extension('pyArrayUtils.exampleIndices',
                         sources = ['lib/exampleIndices.c'],
                         include_dirs = [NUMPY_INCLUDE_PATH],
                         extra_compile_args = ["-std=c99"])

setup(name='pyArrayUtils',
      version = '0.0',
      description = 'Array processing utilities.',
      author = 'Tim Credo',
      package_dir = {'pyArrayUtils': 'lib'},
      packages = ['pyArrayUtils'],
      ext_modules = [pyArrayUtils],
      requires = ['numpy'])

