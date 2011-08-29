import imp
import os
import pdb
import sys
from commands import getoutput

from distutils import log
from distutils.core import setup, Extension
from distutils.command.bdist_rpm import bdist_rpm
from distutils.command.install_data import install_data

#from setuptools import setup, find_packages

# import the cbi module. We use this since the check
# for the compiled swig nmc_base gives an error
# if we import from nmc.__cbi__
cbi = imp.load_source('__cbi__', os.path.join('neurospaces', 'chemesis3', '__cbi__.py'))

_package_info = cbi.PackageInfo()

#-------------------------------------------------------------------------------

#
# This is borrowed from django's setup tools
# taken from here http://code.djangoproject.com/browser/django/trunk/setup.py
#
class osx_install_data(install_data):
    # On MacOS, the platform-specific lib dir is /System/Library/Framework/Python/.../
    # which is wrong. Python 2.5 supplied with MacOS 10.5 has an Apple-specific fix
    # for this in distutils.command.install_data#306. It fixes install_lib but not
    # install_data, which is why we roll our own install_data class.
	
    def finalize_options(self):
        # By the time finalize_options is called, install.install_lib is set to the
        # fixed directory, so we set the installdir to install_lib. The
        # install_data class uses ('install_data', 'install_dir') instead.
        self.set_undefined_options('install', ('install_lib', 'install_dir'))
        install_data.finalize_options(self)


#-------------------------------------------------------------------------------

"""
Function for reading in a file and outputting it as a string. 
"""
def read(fname):
    return open(os.path.join(os.path.dirname(__file__), fname)).read()

#-------------------------------------------------------------------------------

# borrowed from Pysco's setup.py

class ProcessorAutodetectError(Exception):
     pass
def autodetect():
     platform = sys.platform.lower()
     if platform.startswith('win'):   # assume an Intel Windows
         return 'i386'
     # assume we have 'uname'
     mach = os.popen('uname -m', 'r').read().strip()
     if not mach:
         raise ProcessorAutodetectError, "cannot run 'uname -m'"
     try:
         return {'i386': 'i386',
                 'i486': 'i386',
                 'i586': 'i386',
                 'i686': 'i386',
                 'i86pc': 'i386',    # Solaris/Intel
                 'x86':   'i386',    # Apple
                 }[mach]
     except KeyError:
         raise ProcessorAutodetectError, "unsupported processor '%s'" % mach
     
#-------------------------------------------------------------------------------


# This is borrowed from django's setup tools
def fullsplit(path, result=None):
    """
    Split a pathname into components (the opposite of os.path.join) in a
    platform-neutral way.
    """
    if result is None:
        result = []
    head, tail = os.path.split(path)
    if head == '':
        return [tail] + result
    if head == path:
        return result
    return fullsplit(head, [tail] + result)

#-------------------------------------------------------------------------------


"""
Returns a list of all files matching the given file types.
"""
_file_types = ['.py']

def find_files(root_directory, file_types=_file_types):

    package_files = []

    for path, directories, files in os.walk( root_directory ):
        
        for f in files:
            
            path_parts = fullsplit( os.path.join(path, f) )

            path_parts.pop(0)

            this_file = '/'.join(path_parts)

            basename, extension = os.path.splitext( this_file )
            
            if extension in file_types:

                package_files.append(this_file)

    return package_files


#-------------------------------------------------------------------------------
class Chemesis3Module(Extension):
    """
    A class that abstracts methods that detect flags and paths
    for the target machine in a machine independent way. 
    """
    def __init__(self, library_files=None, library_paths=None,
                include_files=None, include_paths=None,
                 ):


        if sys.platform == "darwin":

            arch = autodetect()
            
            if arch == 'i386':

                os.environ['ARCHFLAGS'] = "-arch i386"
                
        self._library_files = library_files
        self._library_paths = library_paths

        self._include_files = include_files
        self._include_paths = include_paths

        self.name = "neurospaces.chemesis3._chemesis3_base"
        self.sources = ["chemesis3.i"]
        self.swig_opts = self.get_swig_opts()
        self.extra_compile_args = self.get_extra_compile_args()
        self.libraries = self.get_libraries()
        
        Extension.__init__(self,
                           self.name,
                           sources=self.sources,
                           swig_opts=self.get_swig_opts(),
                           extra_compile_args=self.get_extra_compile_args(),
                           library_dirs=self.get_library_dirs(),
                           include_dirs=self.get_include_dirs(),
                           libraries=self.get_libraries()
                           )
        
    def get_extra_compile_args(self):

        return []

    def get_swig_opts(self):


        dirs = self.get_include_dirs()

        include_args = []
        
        if len(dirs) > 0:

            include_args = [ '-I%s' % dirs[0],]        

        out_args = ['-outdir', os.path.join('neurospaces', 'chemesis3')]

        swig_opts = []

        swig_opts.extend(include_args)
        swig_opts.extend(out_args)

        return swig_opts

    def get_library_dirs(self):

        library_dirs = []

        for lib_file in self._library_files:

            this_path = self._get_path(self._library_paths, lib_file)

            if this_path is None:

                raise Exception("Can't find library path for %s, can't build extension\n" % lib_file)

            else:

                if not this_path in library_dirs:

                    library_dirs.append(this_path)

                    
        return library_dirs


    def get_include_dirs(self):

        include_dirs = []

        for inc_file in self._include_files:

            this_path = self._get_path(self._include_paths, inc_file)

            if this_path is None:

                raise Exception("Can't find path to headers for %s, can't build extension\n", inc_file)

            else:

                if not this_path in include_dirs:

                    include_dirs.append(this_path)

        return include_dirs


    def _get_path(self, dirs, file):
        """
        helper method, picks which path the given file is in and returns it.
        None if not found. 
        """
        
        for d in dirs:

            full_path = os.path.join(d, file)
            
            if os.path.isfile(full_path):

                return d

        return None

    
    def _in_path(self, dirs, file):

        for d in dirs:

            full_path = os.path.join(d, file)
            
            if os.path.isfile(full_path):

                return True

        return False


    def get_libraries(self):

        return ["chemesis3", "event_algorithms", "symbol_algorithms",
                "cneurospaces", "ncurses", "readline", "heccer", "neurospacesread"]

    def get_mac_architectures(self, file):
        """
        Returns string identifiers for the architecures present in the
        given file.

        """
        lipo_output = getoutput("lipo -info %s" % file)

        if re.search("can't figure out the architecture type of", lipo_output) or re.search("can't open input file", lipo_output):
            
            return None

        else:
            
            arches = lipo_output.split(':')[-1]

            return arches.split()


#-------------------------------------------------------------------------------
NAME = _package_info.GetName()
VERSION = _package_info.GetVersion()
AUTHOR = cbi.__author__
AUTHOR_EMAIL = cbi.__email__
LICENSE = cbi.__license__
URL = cbi.__url__
DOWNLOAD_URL = cbi.__download_url__
DESCRIPTION="Chemesis3 is a fast compartmental solver, that is based on hsolve of the GENESIS simulator."
LONG_DESCRIPTION=cbi.__description__

KEYWORDS="neuroscience neurosimulator simulator modeling GENESIS"

# Get strings from http://pypi.python.org/pypi?%3Aaction=list_classifiers
CLASSIFIERS = [
    'Development Status :: 0 - Alpha',
    'Environment :: Console',
    'Environment :: Desktop Application',
    'Intended Audience :: End Users/Desktop',
    'Intended Audience :: Developers',
    'Intended Audience :: Research',
    'Intended Audience :: Science',        
    'License :: OSI Approved :: GPL License',
    'Operating System :: MacOS :: MacOS X',
    'Operating System :: POSIX',
    'Programming Language :: Python',
    'Topic :: Research :: Neuroscience',
]

PACKAGE_FILES=find_files(os.path.join('neurospaces', 'chemesis3'))

OPTIONS={
    'sdist': {
        'formats': ['gztar','zip'],
        'force_manifest': True,
        },
    'bdist_mpkg': {
        'zipdist': True,

        }
    }

PLATFORMS=["Unix", "Lunix", "MacOS X"]

PY_MODULES=['neurospaces.chemesis3']


CMDCLASS = {
#    'build_ext': build_ext,
    'bdist_rpm': bdist_rpm,
#    'bdist_mpkg': bdist_mpkg,
#    'test': test,
    }

if sys.platform == "darwin": 
    CMDCLASS = {'install_data': osx_install_data} 
else: 
    CMDCLASS = {'install_data': install_data}


#-------------------------------------------------------------------------------


home_dir = os.getenv('USERPROFILE') or os.getenv('HOME')

_chemesis3_dir = os.path.join(home_dir,
                             'neurospaces_project',
                             'chemesis3',
                             'source',
                             'snapshots',
                             '0'
                             )

_model_container_dir = os.path.join(home_dir,
                                    'neurospaces_project',
                                    'model-container',
                                    'source',
                                    'snapshots',
                                    '0'
                                    )
_heccer_dir = os.path.join(home_dir,
                           'neurospaces_project',
                           'heccer',
                           'source',
                           'snapshots',
                           '0'
                           )


_library_files = ["libchemesis3.a", "libheccer.a", "libneurospacesread.a", "libcneurospaces.a",
                  "libsymbol_algorithms.a" , "libevent_algorithms.a"]
_library_paths = [_chemesis3_dir,
                  os.path.join(_chemesis3_dir, "integrators"),
                  _heccer_dir,
                  _model_container_dir,
                  os.path.join(_model_container_dir, 'algorithms', 'symbol'),
                  os.path.join(_model_container_dir, 'algorithms', 'event'),
                  "../../..",
                  "/usr/local/lib/", ]

_include_files = ["chemesis3/chemesis3.h", "heccer/des.h", "hierarchy/output/symbols/type_defines.h"]
_include_paths = ["../../..",
                  "/usr/local/include",
                  _model_container_dir,
                  _heccer_dir,
                  ]

try:
    chemesis3_module=Chemesis3Module(library_paths=_library_paths,
                                     library_files=_library_files,
                                     include_paths=_include_paths,
                                     include_files=_include_files)
except Exception, e:

    print "Error: %s" % e
    sys.exit(0)
    
EXT_MODULES=[
    chemesis3_module,
    ]

#-------------------------------------------------------------------------------

setup(
    name=NAME,
    version=VERSION,
    author=AUTHOR,
    author_email=AUTHOR_EMAIL,
    cmdclass=CMDCLASS,
#    data_files=DATA_FILES,
    description=DESCRIPTION,
    long_description=LONG_DESCRIPTION,
    ext_modules=EXT_MODULES,
    license=LICENSE,
    keywords=KEYWORDS,
    url=URL,
    packages=['neurospaces', 'neurospaces.chemesis3'],
    package_data={'neurospaces' : [os.path.join('neurospaces','__init__.py')],
                  'neurospaces.chemesis3' : PACKAGE_FILES},
#     package_dir={'' : ''},
    classifiers=CLASSIFIERS,
    options=OPTIONS,
    platforms=PLATFORMS,
)

