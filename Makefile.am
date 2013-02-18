##
## The neurospaces project : modeling tools for computational
## neuroscience.
##

##############################################################################
##'
##' The neurospaces project
##'
##' Copyright (C) 2007-2008 Hugo Cornelis
##'
##' Hugo Cornelis, hugo.cornelis@gmail.com
##'
##############################################################################

# note: order makes sure that the library is build before the tests are.

SUBDIRS = \
	. \
	@CHEMESIS3_INTEGRATORS@ \
	glue \
	tests

# fill in the scripts that should go with the distribution:

dist_bin_SCRIPTS = \
	bin/chemesis3

#t note the use of builddir without '/' suffixed.

#t the neurospaces prefix should be used for this

AM_CFLAGS=-g3 -fPIC -include chemesis3/config.h -Wmissing-prototypes -Wmissing-declarations -ffloat-store -I/usr/local/neurospaces/instrumentor -I$(srcdir)/.. -I$(builddir).. -include chemesis3/config.h -DPRE_PROTO_TRAVERSAL -D__NO_MATH_INLINES

lib_LIBRARIES = libchemesis3.a

libchemesis3_a_SOURCES = \
	addressing.c \
	solver.c

nobase_include_HEADERS = \
	chemesis3/addressing.h \
	chemesis3/chemesis3.h \
	chemesis3/mathcomponent.h \
	chemesis3/service.h


CLEANFILES = \
	$(top_srcdir)/docs/doxygen.tag

@PACKAGE@testdir=$(prefix)/$(PACKAGE)
nobase_dist_@PACKAGE@test_DATA=@TEST_SPECIFICATION_FILES@

RELEASE_MAJOR=`release-extract --major`
RELEASE_MINOR=`release-extract --minor`
RELEASE_MICRO=`release-extract --micro`

show-release-labels:
	echo "Release information (major-minor-micro): $(RELEASE_MAJOR)-$(RELEASE_MINOR)-$(RELEASE_MICRO)"

dist-keywords:
	release-expand $(PACKAGE) $(RELEASE_MAJOR) $(RELEASE_MINOR) $(RELEASE_MICRO) $(RELEASE_MAJOR).$(RELEASE_MINOR) hugo.cornelis@gmail.com --verbose

# the tests are copied overhere.
#
# The variable EXTRA_DIST could also be used here.

EXTRA_DIST = \
	docs \
	tests \
	license.txt

am__tar = ${AMTAR} chf - --format=posix "$$tardir"


clean-local:
	$(RM) -rf $(top_srcdir)/docs/html
	$(RM) -rf $(top_srcdir)/docs/latex
	$(RM) -rf $(top_srcdir)/docs/rtf
	$(RM) -rf $(top_srcdir)/docs/chemesis3
	$(RM)  -rf $(TMP_DIR)
	$(RM) -rf $(top_srcdir)/*.deb
	$(RM) -f $(top_srcdir)/*.changes
	$(RM) -f $(top_srcdir)/*.dsc
	$(RM) -f $(top_srcdir)/build_*.log
	$(RM) -rf $(top_srcdir)/*_BUILD/
	$(RM) $(top_srcdir)/$(PACKAGE)-*.tar.gz
	$(RM) -rf $(top_srcdir)/$(PACKAGE)-*

dist-hook: 
	if test -n "$$NEUROSPACES_RELEASE" ; then cd $(srcdir) && if test -n "`mtn ls changed `" ; then false ; else true ; fi ; else true ; fi
	cp $(srcdir)/license.txt $(distdir)
	cp -R $(srcdir)/docs $(distdir)
	rm -rf $(distdir)/docs/html
	rm -rf $(distdir)/docs/latex
	rm -rf $(distdir)/docs/man
	rm -rf $(distdir)/docs/html
	rm -rf $(distdir)/docs/rtf
#	cp -pR $(srcdir)/tests.config $(distdir)
	$(srcdir)/install-sh -d $(distdir)/tests
	$(srcdir)/install-sh -d $(distdir)/tests/html
#	( cd $(distdir)/tests && chmod -R u+w . && neurospaces_harness_2_html --introduction introduction.html )

test: check


html-upload-prepare:
	rm -fr html/htdocs/neurospaces_project/$(PACKAGE)
	mkdir -p html/htdocs/neurospaces_project/$(PACKAGE)
# $Format: "	( cd tests && neurospaces_harness_2_html --header '<img src=\"ns-main-logo-dark2-notext-32x32.jpg\" alt=\"Main Neurospaces logo\"> ${package}, ${label}, ${email} <hr>' --introduction introduction.html )" $
	( cd tests && neurospaces_harness_2_html --header '<img src="ns-main-logo-dark2-notext-32x32.jpg" alt="Main Neurospaces logo"> neurospaces 0.1675 Thu, 27 Dec 2007 15:58:18 -0600 hugo<hr>' --introduction introduction.html )

#t perhaps also add a target to check the syntax of all the html ?

#TESTS = /usr/local/bin/neurospaces_harness

html-upload: html-upload-prepare
	scp -pr html/htdocs/* hcornelis,neurospaces@web.sourceforge.net:/home/groups/n/ne/neurospaces/htdocs/

doxygen: doxygen.cfg
	$(DOXYGEN) doxygen.cfg

docs-level1:

docs-level2:

docs-level3: html-upload-prepare
	echo "Converted the regression tests to HTML"

docs-level4:

docs-level5:

docs-level6: doxygen
	echo "Doxygenized source code"

docs-level7:

docs: docs-level1 docs-level2 docs-level3 docs-level4 docs-level5 docs-level6 docs-level7

APP_NAME=neurospaces$(PACKAGE)

# the pkg-src target must create pkg/$(APP_NAME)-$(VERSION).tar.gz
pkg-src: dist
	mkdir -p pkg
	cp $(PACKAGE)-$(VERSION).tar.gz pkg/$(PACKAGE)-$(VERSION).tar.gz


# Create a deb package
pkg-deb: dist
	nspkg-deb $(PACKAGE) $(VERSION)

pkg-rpm: dist
	nspkg-rpm $(PACKAGE) $(VERSION)

pkg-osx: 
	nspkg-osx 

