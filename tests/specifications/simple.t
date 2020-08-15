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
						   read => (join '', `cat $::global_config->{core_directory}/tests/specifications/strings/cal1.txt`),
						   wait => 1,
						  },
						 ],
				comment => 'based on the G-2 cal1.g script',
				description => "the cal1 model",
			       },
			       {
				arguments => [
					     ],
				command => 'tests/code/cal2',
				command_tests => [
						  {
						   description => "Do we find the expected output (cal2) ?",
						   read => (join '', `cat $::global_config->{core_directory}/tests/specifications/strings/cal2.txt`),
						   wait => 1,
						  },
						 ],
				comment => 'based on the G-2 cal2.g script',
				description => "the cal2 model",
			       },
			      ],
       description => "simple chemesis3 models",
       name => 'simple.t',
      };


return $test;


