from distutils.core import setup, Extension

setup(name="epycs.aes", version="0.1",
      packages = ['epycs'],
      ext_modules=[
         Extension("epycs.aes", 
             sources=[
		"epycs/rijndael.c",
		"epycs/aesmodule.c",
	     ]
         ),
         ])
