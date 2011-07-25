#!/usr/bin/perl -w
#

use strict;


my $test
    = {
       command_definitions => [
			       {
				arguments => [
					     ],
				command => 'tests/python/import_test.py',
				command_tests => [
						  {
						   description => "Can we import the chemesis3 module and it's base class ?",
						   disabled => "under development",
						   read => 'Importing chemesis3_base
Importing chemesis3
Done!
',
						  },
						 ],
				description => "a simple application that imports the built chemesis3 python modules",
			       },

			       {
				arguments => [
					     ],
				command => 'tests/python/import_test_1.py',
				command_tests => [
						  {
						   description => "Can we import the chemesis3 module and it's base class from the installed location ?",
						   read => 'Importing chemesis3_base
Importing Chemesis3
Done!
',
						  },
						 ],
				description => "A simple application that imports the built chemesis3 python modules from /usr/local/glue/swig/python",
			       },

			      ],
       description => "Simple python functionality tests",
       name => 'python/import.t',
      };


return $test;


