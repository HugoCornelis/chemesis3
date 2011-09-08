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


from chemesis3.components import Pool

my_pool = Pool()

my_pool.SetReactions([1, 2, 3])

print "First item is %d" % my_pool.GetReaction(0)
print "Second item is %d" % my_pool.GetReaction(1)
print "Third item is %d" % my_pool.GetReaction(2)

print "Number of items is %s" % my_pool.NumReactions()

print "Done!"

