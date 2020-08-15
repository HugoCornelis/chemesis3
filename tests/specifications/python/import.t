#!/usr/bin/perl -w
#

use strict;


my $test
    = {
       command_definitions => [
			       {
				arguments => [
					     ],
				command => 'tests/python/import_test_1.py',
				command_tests => [
						  {
						   description => "Can we import the chemesis3 module and it's base class ?",
						   read => 'Importing chemesis3_base
Importing chemesis3
Done!
',
						  },
						 ],
				description => "a simple application that imports the built chemesis3 python modules",
			       },


			      ],
       description => "Simple python functionality tests",
       disabled => "the python modules have been disabled",
       name => 'python/import.t',
      };


return $test;


