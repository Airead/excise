from distutils.core import setup, Extension

withargs_extension = Extension(
    "withargs",
    sources = ["withargs.c"],
    extra_compile_args = ['-std=c99', '-fno-strict-aliasing', '-fcommon',
                          '-fPIC', '-Wall', '-Wextra', '-Wno-unused-parameter',
                          '-Wno-missing-field-initializers', '-g']
)

setup(
    name = "withargs",
    author = "Airead Fan",
    author_email = "fgh1987168@gmail.com",
    license = 'GPL',
    url = '',
    description = "A simple Python C extension",
    version = "0.0.1",
    ext_modules = [withargs_extension]
)
