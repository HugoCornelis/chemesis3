#!/usr/bin/perl -w
#

use strict;


my $test
    = {
       command_definitions => [
			       {
				arguments => [
					     ],
				command => 'tests/python/cal1.py',
				command_tests => [
						  {
						   description => "Check for cal1.py script completion",
						   read => 'Done!',
						   timeout => 5,
						  },
						  {
						   description => "Do we find the expected output (cal1) in python ?",
						   read => {

							    expected_output_file => "$::config->{core_directory}/tests/specifications/strings/cal1.txt",
							    application_output_file => "/tmp/output_cal1",

							   }
						  },
						 ],
				comment => 'based on the G-2 cal1.g script',
				description => "the cal1 model",
				preparation => {
						description => "Clean out any previous files",
						preparer =>
						sub
						{
						    `rm -f /tmp/output_cal1`;
						},
					       },
				reparation => {
					       description => "Remove the generated output files",
					       reparer =>
					       sub
					       {
 						   `rm -f /tmp/output_cal1`;
					       },
					      },
			       },




			       {
				arguments => [
					     ],
				command => 'tests/python/cal2.py',

				command_tests => [
						  {
						   description => "Check for cal2.py script completion",
						   read => 'Done!',
						   timeout => 5,
						  },
						  {
						   description =>  "Do we find the expected output in python (cal2) ?",
						   read => {

							    expected_output_file => "$::config->{core_directory}/tests/specifications/strings/cal2.txt",
							    application_output_file => "/tmp/output_cal2",

							   }
						  },
						 ],
				comment => 'based on the G-2 cal2.g script',
				description => "the cal2 model",
				preparation => {
						description => "Clean out any previous files",
						preparer =>
						sub
						{
						    `rm -f /tmp/output_cal2`;
						},
					       },
				reparation => {
					       description => "Remove the generated output files",
					       reparer =>
					       sub
					       {
 						   `rm -f /tmp/output_cal2`;
					       },
					      },
			       },


			      ],
       description => "simple chemesis3 models",
       name => 'simple.t',
      };


return $test;


