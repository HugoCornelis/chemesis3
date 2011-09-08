#! /usr/bin/env python
"""
This test checks for the for the chemesis3 modules 
to be present and importable.
"""
import os
import sys
import pdb

from test_library import add_package_path

add_package_path("chemesis3")

print "Importing chemesis3_base"
import chemesis3.chemesis3_base

print "Importing chemesis3"
import chemesis3

print "Done!"
