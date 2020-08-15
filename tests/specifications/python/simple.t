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

							    expected_output_file => "$::global_config->{core_directory}/tests/specifications/strings/cal1.txt",
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
				command => 'tests/python/cal1_api.py',
				command_tests => [
						  {
						   description => "Check for cal1.py script completion",
						   read => 'Done!',
						   timeout => 5,
						  },
						  {
						   description => "Do we find the expected output (cal1 api) in python ?",
						   read => {

							    expected_output_file => "$::global_config->{core_directory}/tests/specifications/strings/cal1.txt",
							    application_output_file => "/tmp/output_cal1",

							   }
						  },
						 ],
				comment => 'based on the G-2 cal1.g script, all via low level api',
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
				command => 'tests/python/cal1_ndf.py',
				command_tests => [
						  {
						   description => "Check for cal1.py script completion",
						   read => 'Done!',
						   timeout => 5,
						  },
						  {
						   description => "Do we find the expected output (cal1 ndf) in python ?",
						   read => {

							    expected_output_file => "$::global_config->{core_directory}/tests/specifications/strings/cal1.txt",
							    application_output_file => "/tmp/output_cal1",

							   }
						  },
						 ],
				comment => 'Uses the model container as a service for chemesis3',
				description => "Uses the model container as a service for chemesis3",
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

							    expected_output_file => "$::global_config->{core_directory}/tests/specifications/strings/cal2.txt",
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
       disabled => "the python modules have been disabled",
       name => 'python/simple.t',
      };


return $test;


