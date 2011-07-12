dnl -*- autoconf -*-
dnl
dnl The neurospaces project : modeling tools for computational
dnl neuroscience.
dnl

dnl ##########################################################################
dnl 
dnl The neurospaces project
dnl 
dnl Copyright (C) 2007-2008 Hugo Cornelis
dnl 
dnl Hugo Cornelis, hugo.cornelis@gmail.com
dnl 
dnl ##########################################################################

# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.59)

# $Format: "AC_INIT(${package}, ${major}.${minor}.${micro}-${label}, ${email})"$
AC_INIT(chemesis3, 0.0.0-alpha, hugo.cornelis@gmail.com)

dnl Obtain operating system information.
AC_CANONICAL_TARGET

AC_CONFIG_SRCDIR([solver.c])
AC_CONFIG_HEADER([chemesis3/config.h])

dnl dnl all subdirs

dnl AC_CONFIG_SUBDIRS(tests/code glue)

# $Format: "AM_INIT_AUTOMAKE(${package}, ${major}.${minor}.${micro}-${label})"$
AM_INIT_AUTOMAKE(chemesis3, 0.0.0-alpha)


AC_MSG_CHECKING(whether we build universal binaries.)
AC_ARG_WITH(universal,
[AS_HELP_STRING([--with-universal],
              [Build universal binaries on Mac OS X.])],
[ case "$val" in
  no)

    AC_MSG_RESULT(no)
    OSX_UNIVERSAL="no"

    ;;
  *)

    AC_MSG_RESULT(yes)
    OSX_UNIVERSAL="yes"

    CFLAGS="$CFLAGS -arch x86_64 -arch i386 -arch ppc"
    AC_SUBST(CFLAGS)

    ;;
  esac ],
  AC_MSG_RESULT(no)
  OSX_UNIVERSAL="no"
)
AC_SUBST(OSX_UNIVERSAL)


# Checks for programs.
AC_PROG_CC
AC_PROG_RANLIB

AC_PATH_PROGS(DOXYGEN,doxygen)
AC_PATH_PROGS(DOT,dot)
AC_PATH_PROGS(SOURCE_HIGHLIGHT,source-highlight)


dnl Check for Python and it's headers
AM_PATH_PYTHON(,[],[
   echo "Python is not installed."
   exit -1
])

AC_MSG_CHECKING([Python prefix is ])
  AC_MSG_RESULT(['$PYTHON_PREFIX'])

dnl
dnl This is a forced fix to make sure a mac installation gets the proper
dnl python executable. Unless the macpython installer was run, the autotools
dnl python macro won't look for python in the proper path. 
dnl 
case "$host_os" in
  darwin*)

    PYTHON_PREFIX='/Library/Frameworks/Python.framework/Versions/Current'
    AC_SUBST(PYTHON_PREFIX)
    
    PYTHON=$PYTHON_PREFIX/bin/python
    AC_SUBST(PYTHON)

    AC_CHECK_PROG(HAVE_PYTHON_CONFIG, python-config, "yes", "no",[$PYTHON_PREFIX/bin])
    AC_MSG_CHECKING([python-config present])
    AC_MSG_RESULT([$HAVE_PYTHON_CONFIG])
  ;;
  *)

    AC_CHECK_PROG(HAVE_PYTHON_CONFIG, python-config, "yes", "no")
    AC_MSG_CHECKING([python-config present])
    AC_MSG_RESULT([$HAVE_PYTHON_CONFIG])

  ;;
esac


if test "$HAVE_PYTHON_CONFIG" == "yes"; then

  # This is to set the proper python-config for getting the 
  # proper flags and prefixes

  
  AC_MSG_CHECKING([Python config location])
  PYTHON_CONFIG=$PYTHON-config
  AC_SUBST(PYTHON_CONFIG)
  AC_MSG_RESULT([$PYTHON_CONFIG])


  AC_MSG_CHECKING([Python prefix is])
  PYTHON_PREFIX=`$PYTHON_CONFIG --prefix`
  AC_SUBST(PYTHON_PREFIX)
  AC_MSG_RESULT([$PYTHON_PREFIX])


  AC_MSG_CHECKING([Python includes are])
  PYTHON_INCLUDE=`$PYTHON_CONFIG --include`
  AC_SUBST(PYTHON_INCLUDE)
  AC_MSG_RESULT([$PYTHON_INCLUDE])


  AC_MSG_CHECKING([Python libs are])
  PYTHON_LIBS=`$PYTHON_CONFIG --libs`
  AC_SUBST(PYTHON_LIBS)
  AC_MSG_RESULT([$PYTHON_LIBS])


  AC_MSG_CHECKING([Python cflags are])
  PYTHON_CFLAGS=`$PYTHON_CONFIG --cflags`
  AC_SUBST(PYTHON_CFLAGS)
  AC_MSG_RESULT([$PYTHON_CFLAGS])


  AC_MSG_CHECKING([Python ldflags are])
  PYTHON_LDFLAGS=`$PYTHON_CONFIG --ldflags`
  AC_SUBST(PYTHON_LDFLAGS)
  AC_MSG_RESULT([$PYTHON_LDFLAGS])

  AC_MSG_CHECKING([Python executable is])
  PYTHON_EXE=$PYTHON_PREFIX/bin/python
  AC_SUBST(PYTHON_EXE)
  AC_MSG_RESULT([$PYTHON_EXE])


else

  # This is legacy to make sure that systems with python
  # that do not have python-config can get the python info
  # This has always been a bit error prone, particularly if the 
  # user has more than one python version installed.

  PYTHON_PREFIX=`echo $PYTHON | sed -e "s,[[^/]]*$,,;s,/$,,;s,^$,.,"`
  PYTHON_PREFIX=`echo $PYTHON_PREFIX | sed -e "s,[[^/]]*$,,;s,/$,,;s,^$,.,"`
  AC_SUBST(PYTHON_PREFIX)

  AC_MSG_CHECKING([Python prefix is])
  AC_MSG_RESULT([$PYTHON_PREFIX])

  PYTHON_HEADERS='$(PYTHON_PREFIX)/include/python$(PYTHON_VERSION)'
  AC_SUBST(PYTHON_HEADERS)

  AC_MSG_CHECKING([Python includes are])
  PYTHON_INCLUDE='-I$(PYTHON_HEADERS)'
  AC_SUBST(PYTHON_INCLUDE)
  AC_MSG_RESULT([$PYTHON_INCLUDE])

  AC_MSG_CHECKING([Python ldflags are])
  PYTHON_LIBS='-L$(pyexecdir)/../config'
  AC_SUBST(PYTHON_LIBS)
  AC_MSG_RESULT([$PYTHON_LIBS])
				
  PYTHON_EXE='$(PYTHON_PREFIX)/bin/python'
  AC_SUBST(PYTHON_EXE)
fi


PERL_MODULES=`(cd perl && find . -name "*.pm" | perl -pe 's/\n/ /g')`
AC_SUBST(PERL_MODULES)

PERL_DATA=`(cd perl && find . -name "numbers-7x11.txt" | perl -pe 's/\n/ /g')`
AC_SUBST(PERL_DATA)

# Checks for programs.

#   check for packaging programs for debian and red hat.
#   no need to bail out if these are missing since they're optional. 
AC_CHECK_PROGS([DPKG_BUILDPACKAGE],dpkg-buildpackage,[NULL])
AC_CHECK_PROGS([DH],dh,[NULL])
AC_CHECK_PROGS([RPMBUILD],rpmbuild,[NULL])

dnl Check for Python and it's headers
AM_PATH_PYTHON(,[],[
   echo "Python is not installed."
   exit -1
])

AC_MSG_CHECKING([Python prefix is ])
  AC_MSG_RESULT(['$PYTHON_PREFIX'])

dnl
dnl This is a forced fix to make sure a mac installation gets the proper
dnl python executable. Unless the macpython installer was run, the autotools
dnl python macro won't look for python in the proper path. 
dnl 
case "$host_os" in
  darwin*)

    PYTHON_PREFIX='/Library/Frameworks/Python.framework/Versions/Current'
    AC_SUBST(PYTHON_PREFIX)
    
    PYTHON=$PYTHON_PREFIX/bin/python
    AC_SUBST(PYTHON)

    AC_CHECK_PROG(HAVE_PYTHON_CONFIG, python-config, "yes", "no",[$PYTHON_PREFIX/bin])
    AC_MSG_CHECKING([python-config present])
    AC_MSG_RESULT([$HAVE_PYTHON_CONFIG])
  ;;
  *)

    AC_CHECK_PROG(HAVE_PYTHON_CONFIG, python-config, "yes", "no")
    AC_MSG_CHECKING([python-config present])
    AC_MSG_RESULT([$HAVE_PYTHON_CONFIG])

  ;;
esac


if test "$HAVE_PYTHON_CONFIG" == "yes"; then

  # This is to set the proper python-config for getting the 
  # proper flags and prefixes

  
  AC_MSG_CHECKING([Python config location])
  PYTHON_CONFIG=$PYTHON-config
  AC_SUBST(PYTHON_CONFIG)
  AC_MSG_RESULT([$PYTHON_CONFIG])


  AC_MSG_CHECKING([Python prefix is])
  PYTHON_PREFIX=`$PYTHON_CONFIG --prefix`
  AC_SUBST(PYTHON_PREFIX)
  AC_MSG_RESULT([$PYTHON_PREFIX])


  AC_MSG_CHECKING([Python includes are])
  PYTHON_INCLUDE=`$PYTHON_CONFIG --include`
  AC_SUBST(PYTHON_INCLUDE)
  AC_MSG_RESULT([$PYTHON_INCLUDE])


  AC_MSG_CHECKING([Python libs are])
  PYTHON_LIBS=`$PYTHON_CONFIG --libs`
  AC_SUBST(PYTHON_LIBS)
  AC_MSG_RESULT([$PYTHON_LIBS])


  AC_MSG_CHECKING([Python cflags are])
  PYTHON_CFLAGS=`$PYTHON_CONFIG --cflags`
  AC_SUBST(PYTHON_CFLAGS)
  AC_MSG_RESULT([$PYTHON_CFLAGS])


  AC_MSG_CHECKING([Python ldflags are])
  PYTHON_LDFLAGS=`$PYTHON_CONFIG --ldflags`
  AC_SUBST(PYTHON_LDFLAGS)
  AC_MSG_RESULT([$PYTHON_LDFLAGS])

  AC_MSG_CHECKING([Python executable is])
  PYTHON_EXE=$PYTHON_PREFIX/bin/python
  AC_SUBST(PYTHON_EXE)
  AC_MSG_RESULT([$PYTHON_EXE])


else

  # This is legacy to make sure that systems with python
  # that do not have python-config can get the python info
  # This has always been a bit error prone, particularly if the 
  # user has more than one python version installed.

  PYTHON_PREFIX=`echo $PYTHON | sed -e "s,[[^/]]*$,,;s,/$,,;s,^$,.,"`
  PYTHON_PREFIX=`echo $PYTHON_PREFIX | sed -e "s,[[^/]]*$,,;s,/$,,;s,^$,.,"`
  AC_SUBST(PYTHON_PREFIX)

  AC_MSG_CHECKING([Python prefix is])
  AC_MSG_RESULT([$PYTHON_PREFIX])

  PYTHON_HEADERS='$(PYTHON_PREFIX)/include/python$(PYTHON_VERSION)'
  AC_SUBST(PYTHON_HEADERS)

  AC_MSG_CHECKING([Python includes are])
  PYTHON_INCLUDE='-I$(PYTHON_HEADERS)'
  AC_SUBST(PYTHON_INCLUDE)
  AC_MSG_RESULT([$PYTHON_INCLUDE])

  AC_MSG_CHECKING([Python ldflags are])
  PYTHON_LIBS='-L$(pyexecdir)/../config'
  AC_SUBST(PYTHON_LIBS)
  AC_MSG_RESULT([$PYTHON_LIBS])
				
  PYTHON_EXE='$(PYTHON_PREFIX)/bin/python'
  AC_SUBST(PYTHON_EXE)
fi


# integrators: integrate with model-container of neurospaces ?

AC_ARG_ENABLE(neurospaces, AS_HELP_STRING([--without-neurospaces   don't use neurospaces as modeling component]) )

CHEMESIS3_INTEGRATORS=

if test x"$with_neurospaces" == "xno" ; then

    echo "NOT using Neurospaces as modeling component"

else

    echo "Using Neurospaces as modeling component"

    AC_DEFINE(CHEMESIS3_SOURCE_NEUROSPACES, 1, [use neurospaces as modeling component])

    CHEMESIS3_INTEGRATORS="integrators"
fi

AC_SUBST(CHEMESIS3_INTEGRATORS)


# Checks for libraries.

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([float.h limits.h locale.h stdlib.h string.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_CONST

# Checks for library functions.
AC_CHECK_FUNCS([localeconv strchr])

dnl This does macro substitutions for certain operating systems and 
dnl architectures 
AC_MSG_CHECKING([OS specifics...])
AC_MSG_RESULT([Host is running $host_os.])
dnl {{{
case "$host_os" in
  darwin*)
    #
    # These are settings specific to MAC OS X.
    #
    dnl {{{{
    AC_MSG_CHECKING([Using libtool for MAC OS X.])
    AR=libtool
    ARFLAGS='-static -c -o'
    AC_SUBST(AR)
    AC_SUBST(ARFLAGS)
    AC_MSG_RESULT([$AR $ARFLAGS])

    dnl On the MAC we will only look for perl in the standard location for the Apple
    dnl native perl. 
    AC_CHECK_PROG(PERL, perl, NULL, [/usr/bin/perl],[/usr/local/bin/perl /opt/local/bin/perl])
    AC_SUBST(PERL)

    AC_MSG_CHECKING([Checking the perl installation])
    case $PERL in
      NULL*)
        echo ""
        echo "Error, the standard version of perl for Mac OSX is not found."
        echo "Non standard versions of perl are known to cause problems."
        AC_ERROR([Perl for Mac OSX is not found.])
        ;;
      *)
        AC_MSG_RESULT([ $PERL ])
        ;;
    esac

    # determine linker flags for perl embedding
    if test "$OSX_UNIVERSAL" == "yes"; then

      PERL_CCOPTS=`$PERL -MExtUtils::Embed -e ccopts`
      
      PERL_LDADD=`$PERL -MExtUtils::Embed -e ldopts`

      PERL_LDFLAGS=`$PERL -MExtUtils::Embed -e ldopts | perl -pe 's/\-arch\s\S+\s//g'`

    else

      PERL_CCOPTS=`$PERL -MExtUtils::Embed -e ccopts | perl -pe 's/\-arch\s\S+\s//g'`
    
      PERL_LDADD=`$PERL -MExtUtils::Embed -e ldopts | perl -pe 's/\-arch\s\S+\s//g'`

      PERL_LDFLAGS=`$PERL -MExtUtils::Embed -e ldopts | perl -pe 's/\-arch\s\S+\s//g'`

    fi
    
    AC_SUBST(PERL_CCOPTS)
    AC_SUBST(PERL_LDADD)
    AC_SUBST(PERL_LDFLAGS)



    AC_CHECK_PROG(SWIG, swig, NULL, [/usr/bin/swig],[/usr/local/bin/swig /opt/local/bin/swig /sw/bin/perl])
    AC_SUBST(SWIG)

    AC_MSG_CHECKING([Checking for swig])
    case $SWIG in
      NULL*)
        echo ""
        echo "Error, the standard version of swig for Mac OSX is not found."
        echo "Non standard versions of swig are known to cause problems."
        AC_ERROR([Swig for Mac OSX is not found.])
        ;;
      *)
        AC_MSG_RESULT([ $SWIG ])
        ;;
    esac

    PERLLIB_EXTENSION='dylib'
    AC_SUBST(PERLLIB_EXTENSION)

    SWIGCOMPILELINKSFORPERL='-I/usr/local/neurospaces/instrumentor -I$(top_builddir) -include chemesis3/config.h -ffloat-store -g -O0 -dynamic -fPIC $(PERL_CCOPTS)'
    AC_SUBST(SWIGCOMPILELINKSFORPERL)

    SWIGCOMPILECOMMAND_PERL='gcc $(SWIGCOMPILELINKSFORPERL) -c swiggable_chemesis3_wrap.c'
    AC_SUBST(SWIGCOMPILECOMMAND_PERL)


    if test "$OSX_UNIVERSAL" == "yes"; then 

      # Mando: libtool requires all symbols linked against to be defined at link time otherwise
      # running when it inspects the symbol table at runtime it will fail to load. Have to link against
      # event_algorithms (which is not system installed) in the model container so this looks messy.  
      SWIGLDLINKSFORPERL='-dynamic -undefined suppress -flat_namespace -L$(top_builddir) -lchemesis3 -L$(top_builddir)/integrators -lcneurospaces -lncurses -lreadline $(PERL_LDFLAGS)'

    else

      SWIGLDLINKSFORPERL='-L../../.. -lchemesis3 -L$(top_builddir)/integrators -lcneurospaces -lncurses -lreadline -bundle -undefined suppress -flat_namespace $(PERL_LDFLAGS)'

    fi 

    AC_SUBST(SWIGLDLINKSFORPERL)


    case "$host_os" in
	darwin10*)

            if test "$OSX_UNIVERSAL" == "yes"; then

              SWIGLINKCOMMAND_PERL='$(AR) $(SWIGLDLINKSFORPERL) -o SwiggableChemesis3.$(PERLLIB_EXTENSION) swiggable_chemesis3_wrap.o'

            else

              SWIGLINKCOMMAND_PERL='ld 	$(SWIGLDLINKSFORPERL) 	-o SwiggableChemesis3.$(PERLLIB_EXTENSION) /usr/lib/bundle1.o  swiggable_chemesis3_wrap.o'

            fi

            AC_SUBST(SWIGLINKCOMMAND_PERL)


	;;    
	*)
            SWIGLINKCOMMAND_PERL='ld 	$(SWIGLDLINKSFORPERL) 	-o SwiggableChemesis3.$(PERLLIB_EXTENSION) 	swiggable_chemesis3_wrap.o'
            AC_SUBST(SWIGLINKCOMMAND_PERL)
	;;
    esac 





    PYTHONLIB_EXTENSION='so'
    AC_SUBST(PYHONLIB_EXTENSION)

    SWIGCOMPILELINKSFORPYTHON='$(PYTHON_INCLUDE) -I/usr/local/neurospaces/instrumentor -I./../../.. 	-I.../../../hierarchy/output/symbols 	-I./../../../hierarchy/output/symbols/'
    AC_SUBST(SWIGCOMPILELINKSFORPYTHON)

    SWIGCOMPILECOMMAND_PYTHON='gcc $(SWIGCOMPILELINKSFORPYTHON) -c swiggable_chemesis3_wrap.c'
    AC_SUBST(SWIGCOMPILECOMMAND_PYTHON)

    SWIGLDLINKSFORPYTHON='$(PYTHON_LDFLAGS) -L../../../ -lchemesis3 -L../../../integrators -lcneurospaces -lncurses -lreadline -framework Python -flat_namespace -undefined suppress -bundle 	-bundle_loader $(PYTHON_EXE)'
    AC_SUBST(SWIGLDLINKSFORPYTHON)


    case "$host_os" in
	darwin10*)

	    dnl This is snow leopard

            SWIGLINKCOMMAND_PYTHON='ld 	$(SWIGLDLINKSFORPYTHON) -o _SwiggableChemesis3.$(PYTHONLIB_EXTENSION) /usr/lib/bundle1.o swiggable_chemesis3_wrap.o'
            AC_SUBST(SWIGLINKCOMMAND_PYTHON)

	    CHEMESIS3_SWIGLINKCOMMAND_PYTHON='ld $(SWIGLDLINKSFORPYTHON) -o $(srcdir)/neurospaces/chemesis3/_chemesis3_base.so /usr/lib/bundle1.o chemesis3_wrap.o'
	    AC_SUBST(CHEMESIS3_SWIGLINKCOMMAND_PYTHON)

	;;

	*)
            SWIGLINKCOMMAND_PYTHON='ld 	$(SWIGLDLINKSFORPYTHON) -o _SwiggableChemesis3.$(PYTHONLIB_EXTENSION)  swiggable_chemesis3_wrap.o'
            AC_SUBST(SWIGLINKCOMMAND_PYTHON)	

	    CHEMESIS3_SWIGLINKCOMMAND_PYTHON='ld $(SWIGLDLINKSFORPYTHON) -o $(srcdir)/neurospaces/chemesis3/_chemesis3_base.so chemesis3_wrap.o'
            AC_SUBST(CHEMESIS3_SWIGLINKCOMMAND_PYTHON)
        ;;
    esac 


    AC_MSG_RESULT([done.])
    dnl }}} end MAC OS X settings
    ;;




  *)
  
    dnl {{{
    AR='ar'
    ARFLAGS='cru'
    AC_SUBST(AR)
    AC_SUBST(ARFLAGS)
    AC_MSG_CHECKING([ranlib invocation ])
    AC_MSG_RESULT([$AR $ARFLAGS])

    dnl Check for some needed programs.
    AC_CHECK_PROGS(PERL, perl5 perl)
    AC_SUBST(PERL)

    AC_CHECK_PROGS(SWIG, swig)
    AC_SUBST(SWIG)


    PERL_CCOPTS=`$PERL -MExtUtils::Embed -e ccopts`
    AC_SUBST(PERL_CCOPTS)

    PERL_LDADD=`$PERL -MExtUtils::Embed -e ldopts`
    AC_SUBST(PERL_LDADD)

    PERL_LDFLAGS=`$PERL -MExtUtils::Embed -e ldopts`
    AC_SUBST(PERL_LDFLAGS)


    PERLLIB_EXTENSION='so'
    AC_SUBST(PERLLIB_EXTENSION)


    SWIGCOMPILELINKSFORPERL='-I/usr/local/neurospaces/instrumentor -I$(srcdir)/../../.. -I$(top_builddir) -ffloat-store -I../../.. -include chemesis3/config.h -g -O0 -fPIC $(PERL_CCOPTS)'
    AC_SUBST(SWIGCOMPILELINKSFORPERL)

    SWIGCOMPILECOMMAND_PERL='gcc $(SWIGCOMPILELINKSFORPERL) -c swiggable_chemesis3_wrap.c'
    AC_SUBST(SWIGCOMPILECOMMAND_PERL)


    SWIGLDLINKSFORPERL='-g -shared swiggable_chemesis3_wrap.o -L../../.. -lchemesis3 -L../../../integrators -lcneurospaces -lncurses -lreadline -lhistory -fPIC'
    AC_SUBST(SWIGLDLINKSFORPERL)

    SWIGLINKCOMMAND_PERL='gcc $(SWIGLDLINKSFORPERL) -o SwiggableChemesis3.$(PERLLIB_EXTENSION)'
    AC_SUBST(SWIGLINKCOMMAND_PERL)


    PYTHONLIB_EXTENSION='so'
    AC_SUBST(PYTHONLIB_EXTENSION)

    SWIGCOMPILELINKSFORPYTHON='-g -DPRE_PROTO_TRAVERSAL $(PYTHON_INCLUDE) -I/usr/local/neurospaces/instrumentor -I$(builddir)../../.. -I$(srcdir)/../../.. -I$(builddir)../../../hierarchy/output/symbols -I$(srcdir)/../../../hierarchy/output/symbols/ -fPIC -Xlinker -export-dynamic'
    AC_SUBST(SWIGCOMPILELINKSFORPYTHON)

   SWIGCOMPILECOMMAND_PYTHON='gcc $(SWIGCOMPILELINKSFORPYTHON) -c swiggable_chemesis3_wrap.c'
   AC_SUBST(SWIGCOMPILECOMMAND_PYTHON)

    SWIGLDLINKSFORPYTHON='-L../../.. -lchemesis3 -L../../../integrators -lcneurospaces -lncurses -lreadline -lhistory -fPIC -Xlinker -export-dynamic $(PYTHON_LDFLAGS)'
    AC_SUBST(SWIGLDLINKSFORPYTHON)

    SWIGLINKCOMMAND_PYTHON='gcc -shared swiggable_chemesis3_wrap.o $(SWIGLDLINKSFORPYTHON) -o _SwiggableChemesis3.$(PYTHONLIB_EXTENSION)'
    AC_SUBST(SWIGLINKCOMMAND_PYTHON)

    CHEMESIS3_SWIGLINKCOMMAND_PYTHON='gcc -shared chemesis3_wrap.o $(SWIGLDLINKSFORPYTHON) -o $(srcdir)/neurospaces/chemesis3/_chemesis3_base.so'
    AC_SUBST(CHEMESIS3_SWIGLINKCOMMAND_PYTHON)
    dnl }}} End of General Settings

  ;;
esac
dnl }}}




# determine the test library to install

TEST_SPECIFICATION_FILES=`/bin/echo -n "tests/introduction.html " && find tests/specifications -name "*.t" | perl -pe 's/\n/ /g' && find tests/specifications/strings -name "*.txt" | perl -pe 's/\n/ /g' && find tests/data -name "*.yml" | perl -pe 's/\n/ /g'`
AC_SUBST(TEST_SPECIFICATION_FILES)


AC_CONFIG_FILES([Makefile
                 glue/Makefile
		 glue/swig/perl/Makefile
                 integrators/Makefile
		 tests/Makefile
		 tests/code/Makefile])

AC_OUTPUT

