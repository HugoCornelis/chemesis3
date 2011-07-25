#! /usr/bin/env python
"""

"""
import os
import sys
import pdb

from test_library import add_package_path

add_package_path("chemesis3")

from neurospaces.chemesis3.components import CreateIntArray


reactions = CreateIntArray([0,])

soma_ca_flags = CreateIntArray([0,])

soma_cabuf_flags = CreateIntArray([1,])

soma_buf_flags = CreateIntArray([-1,])

soma_buf_pools = CreateIntArray([1,])

somabuf_pools_flags = CreateIntArray([0,])




