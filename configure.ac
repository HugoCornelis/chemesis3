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


# see https://metacpan.org/source/ASPIERS/Stow-v2.1.2/configure.ac

dnl Check for perl on our system.
dnl Call to AC_SUBST(PERL) is implicit
AC_PATH_PROGS([PERL], [perl] [perl5], [false])
if test "x$PERL" = xfalse
then
  AC_MSG_ERROR([Perl not found; check your \$PATH.])
fi
 
# N.B. ${var#pattern} will not work with some shells, such as
# Solaris 10's /bin/sh :-(
#
#   http://www.gnu.org/software/autoconf/manual/autoconf.html#Portable-Shell
#
#   eval `$PERL -V:siteprefix -V:installsitelib`
#   pmdir_relative_path="${installsitelib#$siteprefix/}"
#
# This will work:
#
#   pmdir_relative_path=`echo "${installsitelib}" | sed -e "s!^$siteprefix/!!"`
#
# but this is cleaner:
pmdir_relative_path=`\
  $PERL -MConfig \
        -wle '($_ = $Config{installsitelib})
              =~ s!^\Q$Config{siteprefix}/!!; \
              print'`
 
AC_ARG_WITH(
    [pmdir],
    AS_HELP_STRING(
      [--with-pmdir=DIR],
      [Install Perl modules in DIR]),
    [PMDIR=${withval}],
    [PMDIR='${prefix}'/"$pmdir_relative_path"])
AC_CONFIG_COMMANDS_POST([[
  eval pmdir="$PMDIR"
  cat <<EOF
 
# Perl modules will be installed to $PMDIR
EOF
  if [ "$pmdir" != "$PMDIR" ]; then
    cat <<EOF
# which will expand to
#
#   $pmdir
#
# unless you override the value of prefix at make-time.
EOF
    echo
  fi
]])
AC_SUBST([PMDIR])




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


    dnl Going to restrict the search for perl to use the mac standard location
    AC_CHECK_PROGS(PERL, perl, [NULL], [/usr/bin])

    dnl AC_MSG_CHECKING([Checking the perl installation])
    case $PERL in
      NULL*)
        echo ""
        echo "Error, the standard version of perl for Mac OSX is not found."
        echo "Non standard versions of perl are known to cause problems."
        AC_ERROR([Perl for Mac OSX is not found.])
        ;;
        *)
        dnl Ensure that ONLY the standard mac perl is used throughout.
	PERL='/usr/bin/perl'
        AC_SUBST(PERL)
        ;;
dnl       *)

dnl         AC_MSG_RESULT([ $PERL ])

dnl         ;;
    esac




    #-- Here we determine the install path for perl modules --
    AC_MSG_CHECKING([Checking the perl module installation path])	
    pmdir_relative_path=`\
      $PERL -MConfig \
        -wle '($_ = $Config{installsitelib})
              =~ s!^\Q$Config{siteprefix}/!!; \
              print'`
 
    AC_ARG_WITH(
      [pmdir],
    AS_HELP_STRING(
      [--with-pmdir=DIR],
      [Install Perl modules in DIR]),
      [PMDIR=${withval}],
      [PMDIR="$pmdir_relative_path"])

    AC_SUBST([PMDIR])
    AC_MSG_RESULT([ $PMDIR ])
    # --- End perl module directory selection --------------



    # This is to get rid of the annoying error that occurs when
    # you use two arch flags.occur By default these commands produce a -arch for both
    # architectures. If now differentiates between OSX lion, which rejects the -fstack-protector
    # flag on the standard build environment.

    echo "This is host_os: $host_os"

    case "$host_os" in

	darwin11*|darwin12*|darwin13*|darwin14*|darwin15*) dnl This is Max OSX lion or OSX mountain lion

          if test "$OSX_UNIVERSAL" == "yes"; then

	    dnl No PPC support in Lion and above so we only pass intel archs
	    dnl CFLAGS="$CFLAGS -arch x86_64 -arch i386"
            dnl AC_SUBST(CFLAGS)	

            PERL_CCOPTS=`$PERL -MExtUtils::Embed -e ccopts | perl -pe 's/\-fstack\-protector//g'`
      
            PERL_LDADD=`$PERL -MExtUtils::Embed -e ldopts | perl -pe 's/\-fstack\-protector//g'`

            # When using libtool, you can't use arch arguments.
            PERL_LDFLAGS=`$PERL -MExtUtils::Embed -e ldopts | perl -pe 's/\-arch\s\S+\s//g' | perl -pe 's/\-fstack\-protector//g'`

          else

            PERL_CCOPTS=`$PERL -MExtUtils::Embed -e ccopts | perl -pe 's/\-arch\s\S+\s//g' | perl -pe 's/\-fstack\-protector//g'`
    
            PERL_LDADD=`$PERL -MExtUtils::Embed -e ldopts | perl -pe 's/\-arch\s\S+\s//g' | perl -pe 's/\-fstack\-protector//g'`

            PERL_LDFLAGS=`$PERL -MExtUtils::Embed -e ldopts | perl -pe 's/\-arch\s\S+\s//g' | perl -pe 's/\-fstack\-protector//g'`

          fi
        ;;
	
	*) dnl all other Mac OSX versions

          if test "$OSX_UNIVERSAL" == "yes"; then

            dnl CFLAGS="$CFLAGS -arch x86_64 -arch i386 -arch ppc"
            dnl AC_SUBST(CFLAGS)

            PERL_CCOPTS=`$PERL -MExtUtils::Embed -e ccopts`
      
            PERL_LDADD=`$PERL -MExtUtils::Embed -e ldopts`

            # When using libtool, you can't use arch arguments.
            PERL_LDFLAGS=`$PERL -MExtUtils::Embed -e ldopts | perl -pe 's/\-arch\s\S+\s//g'`

          else

            PERL_CCOPTS=`$PERL -MExtUtils::Embed -e ccopts | perl -pe 's/\-arch\s\S+\s//g'`
    
            PERL_LDADD=`$PERL -MExtUtils::Embed -e ldopts | perl -pe 's/\-arch\s\S+\s//g'`

            PERL_LDFLAGS=`$PERL -MExtUtils::Embed -e ldopts | perl -pe 's/\-arch\s\S+\s//g'`

          fi
        ;;

    esac

    AC_SUBST(PERL_CCOPTS)
    AC_SUBST(PERL_LDADD)
    AC_SUBST(PERL_LDFLAGS)



    AC_CHECK_PROGS(SWIG, swig, [NULL], [/usr/bin /usr/local/bin])

    dnl AC_MSG_CHECKING([Checking for swig])
    case $SWIG in
      NULL*)
        echo ""
        echo "Error, the standard version of swig for Mac OSX is not found."
        echo "Non standard versions of swig are known to cause problems."
        AC_ERROR([Swig for Mac OSX is not found.])
        ;;
dnl       *)
dnl         AC_MSG_RESULT([ yes ])
dnl         ;;
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
      SWIGLDLINKSFORPERL='-dynamic -undefined suppress -flat_namespace -L$(top_builddir) -lchemesis3 -L$(top_builddir)/integrators -lcneurospaces -L/usr/local/lib/model-container -lneurospacesread -lsymbol_algorithms -L$(top_builddir)/../../../../model-container/source/snapshots/0/algorithms/event -lncurses $(PERL_LDFLAGS)'

    else

      SWIGLDLINKSFORPERL='-L../../.. -lchemesis3 -L$(top_builddir)/integrators -lcneurospaces -L/usr/local/lib/model-container -lneurospacesread -lsymbol_algorithms -L$(top_builddir)/../../../../model-container/source/snapshots/0/algorithms/event -lncurses -bundle -undefined suppress -flat_namespace $(PERL_LDFLAGS)'

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

    SWIGCOMPILELINKSFORPYTHON='$(PYTHON_INCLUDE) -I/usr/local/neurospaces/instrumentor -I./../../.. -I.../../../hierarchy/output/symbols 	-I./../../../hierarchy/output/symbols/'
    AC_SUBST(SWIGCOMPILELINKSFORPYTHON)

    SWIGCOMPILECOMMAND_PYTHON='gcc $(SWIGCOMPILELINKSFORPYTHON) -c swiggable_chemesis3_wrap.c'
    AC_SUBST(SWIGCOMPILECOMMAND_PYTHON)

    SWIGLDLINKSFORPYTHON='$(PYTHON_LDFLAGS) -L../../../ -lchemesis3 -L../../../integrators -lcneurospaces -L/usr/local/lib/model-container -lneurospacesread -lsymbol_algorithms -L$(top_builddir)/../../../../model-container/source/snapshots/0/algorithms/event -L$(top_builddir)/../../../../heccer/source/snapshots/0/ -lheccer -lncurses -framework Python -flat_namespace -undefined suppress -bundle 	-bundle_loader $(PYTHON_EXE)'
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


    AC_MSG_RESULT([done setting Mac OSX settings.])
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

    #-- Here we determine the install path for perl modules --
    AC_MSG_CHECKING([Checking the perl module installation path])	
    pmdir_relative_path=`\
      $PERL -MConfig \
        -wle '($_ = $Config{installsitelib})
              =~ s!^\Q$Config{siteprefix}/!!; \
              print'`
 
    AC_ARG_WITH(
      [pmdir],
    AS_HELP_STRING(
      [--with-pmdir=DIR],
      [Install Perl modules in DIR]),
      [PMDIR=${withval}],
      [PMDIR='${prefix}'/"$pmdir_relative_path"])

    AC_SUBST([PMDIR])
    AC_MSG_RESULT([ $PMDIR ])
    # --- End perl module directory selection --------------

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


    SWIGLDLINKSFORPERL='-g -shared swiggable_chemesis3_wrap.o -L../../.. -lchemesis3 -L../../../integrators -lcneurospaces -L/usr/local/lib/model-container -lneurospacesread -lsymbol_algorithms -L$(top_builddir)/../../../../model-container/source/snapshots/0/algorithms/event -lncurses -fPIC'
    AC_SUBST(SWIGLDLINKSFORPERL)

    SWIGLINKCOMMAND_PERL='gcc $(SWIGLDLINKSFORPERL) -o SwiggableChemesis3.$(PERLLIB_EXTENSION)'
    AC_SUBST(SWIGLINKCOMMAND_PERL)


    PYTHONLIB_EXTENSION='so'
    AC_SUBST(PYTHONLIB_EXTENSION)

    SWIGCOMPILELINKSFORPYTHON='-g -DPRE_PROTO_TRAVERSAL $(PYTHON_INCLUDE) -I/usr/local/neurospaces/instrumentor -I$(builddir)../../.. -I$(srcdir)/../../.. -I$(builddir)../../../hierarchy/output/symbols -I$(srcdir)/../../../hierarchy/output/symbols/ -fPIC -Xlinker -export-dynamic'
    AC_SUBST(SWIGCOMPILELINKSFORPYTHON)

   SWIGCOMPILECOMMAND_PYTHON='gcc $(SWIGCOMPILELINKSFORPYTHON) -c swiggable_chemesis3_wrap.c'
   AC_SUBST(SWIGCOMPILECOMMAND_PYTHON)

    SWIGLDLINKSFORPYTHON='-L../../.. -lchemesis3 -L../../../integrators -lcneurospaces -L/usr/local/lib/model-container -lneurospacesread -lsymbol_algorithms -L$(top_builddir)/../../../../model-container/source/snapshots/0/algorithms/event -L$(top_builddir)/../../../../heccer/source/snapshots/0/ -lheccer -lncurses -fPIC -Xlinker -export-dynamic $(PYTHON_LDFLAGS)'
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
		 glue/swig/python/Makefile
		 tests/Makefile
		 tests/code/Makefile])

AC_OUTPUT

