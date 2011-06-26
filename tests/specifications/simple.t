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
				description => "check version information",
			       },
			      ],
       description => "run-time versioning",
       name => 'version.t',
      };


return $test;


