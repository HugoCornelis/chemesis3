#! /usr/bin/env python
"""
This test checks for the for the Heccer modules 
to be present and importable.
"""
import os
import sys
import pdb

from test_library import add_package_path

add_package_path("chemesis3")

from chemesis3.components import Pool
from chemesis3.components import Reaction

reactions = [0]

soma_ca_flags = [0]

soma_cabuf_flags = [1]

somabuf_flags = [-1]

somabuf_pools = [1]

somabuf_pools_flags = [0]

