#!/usr/bin/perl -w
#

use strict;


my $test
    = {
       command_definitions => [
			       {
				arguments => [
					     ],
				command => 'tests/code/cal1',
				command_tests => [
						  {
						   description => "Do we find the expected output (cal1) ?",
						   read => (join '', `cat $::config->{core_directory}/tests/specifications/strings/cal1.txt`),
						   wait => 1,
						  },
						 ],
				comment => 'based on the G-2 cal1.g script',
				description => "the cal1 model",
			       },
			      ],
       description => "simple chemesis3 models",
       name => 'simple.t',
      };


return $test;


