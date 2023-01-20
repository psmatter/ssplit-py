from distutils.core import setup, Extension, Distribution
from distutils.command.build import build 
from distutils.errors import DistutilsExecError
import sysconfig

#Install_Dir=sysconfig.get_paths()["purelib"]
Install_Dir=sysconfig.get_paths()["platlib"] + "/splitter"
print("Install dir:",Install_Dir)

factorial_module = Extension('splitter',
                 define_macros      = [('MAJOR_VERSION', '0'),
                                       ('MINOR_VERSION', '5')],
                 sources            = ['src/ssplit_py_api.cpp',
                                       'src/ssplit.cpp',
                                       'src/regex.cpp',       ],
                 libraries          = ['pcre2-8'],
                 library_dirs       = ['/usr/local/lib',
                                       '/usr/lib',
                                       '/usr/lib/arm-linux-gnueabihf/',
                                      ],
                 include_dirs       = ['./src/'],
                 extra_compile_args = ['-std=c++17'],
                            )

class splitter_build(build):

    def run(self):
        print('Spawning make')
        try:
            self.spawn(['/usr/bin/make', 'pymodule'])
        except DistutilsExecError:
            self.warn('Building splitter module failed.')
        build.run(self)


setup(name='splitter',
             version     ='0.5',
             author      ='psmatter@github.com, ugermann@github.com',
             author_email='psmatter@github.com',
             url         ='https://www.github.com/psmatter/ssplit-py/',
             description ='Python c++ module to split a text into sentences.',
             license     ='Apache 2.0, parts LGPL2',
             #ext_modules = [factorial_module],
             data_files  =([Install_Dir,('./lib/__init__.py',
                            'lib/splitter.so',),], 
                           ),
             package_dir ={'splitter': './'},
             packages    =['splitter'],
             cmdclass    ={'build': splitter_build, },
             classifiers =['Development Status :: 4 - Beta',
                           'Environment :: Web Environment',
                           'Description :: Python c++ module to split a text into sentences.',
                           'Intended Audience :: Developers',
                           'Operating System :: POSIX',
                           'Programming Language :: Python',
                           'Topic :: NLP/Experimental',
                           'Topic :: Software Development :: Bug Tracking',
                          ],
             )

