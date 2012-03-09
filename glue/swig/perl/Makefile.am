

SUBDIRS = 


#t the following rules are crap complete, would be good if a auto
#t expert takes a look at it.

dist-hook:
	cp $(srcdir)/chemesis3_test.pm $(distdir)

swigdir = $(prefix)/glue/swig

perldir = @PMDIR@

EXTRA_DIST = chemesis3.i 

perl_HEADERS = Chemesis3.pm

perl_DATA = chemesis3_test.pm SwiggableChemesis3.pm SwiggableChemesis3.$(PERLLIB_EXTENSION)

BUILT_SOURCES = \
	SwiggableChemesis3.pm \
	swiggable_chemesis3_wrap.c

#t the configuration should say if this depends on neurospaces or not

SwiggableChemesis3.pm swiggable_chemesis3_wrap.c: $(swig_DATA)
	$(SWIG) -I/usr/local/neurospaces/instrumentor -I$(srcdir)/../../.. -I$(top_builddir) -perl5 -makedefault -module SwiggableChemesis3 -o swiggable_chemesis3_wrap.c $(srcdir)/chemesis3.i

#t the configuration should say if this depends on neurospaces or not

swiggable_chemesis3_wrap.o: swiggable_chemesis3_wrap.c
	$(SWIGCOMPILECOMMAND_PERL)


SwiggableChemesis3.$(PERLLIB_EXTENSION): swiggable_chemesis3_wrap.o
	$(SWIGLINKCOMMAND_PERL)





all: SwiggableChemesis3.$(PERLLIB_EXTENSION)

CLEANFILES = \
	SwiggableChemesis3.pm \
	swiggable_chemesis3_wrap.c \
	swiggable_chemesis3_wrap.o \
	SwiggableChemesis3.$(PERLLIB_EXTENSION)

TESTS = chemesis3_test.pm

test: check

## following http://www.geocities.com/foetsch/python/swig_linux.htm

#BUILT_SOURCES = $(srcdir)/swiggable_chemesis3_wrap.c
#SWIG_SOURCES = chemesis3.i

## other sources
##
## http://sourceware.org/ml/automake/2001-03/msg00395.html
## http://autoconf-archive.cryp.to/macros-by-category.html
## http://sources.redhat.com/ml/automake/2005-02/msg00058.html
## https://www.desy.de/~salvaire/root_wrapper.html

