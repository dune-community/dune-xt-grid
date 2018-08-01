# ~~~
# This file is part of the dune-xt-grid project:
#   https://github.com/dune-community/dune-xt-grid
# Copyright 2009-2018 dune-xt-grid developers and contributors. All rights reserved.
# License: Dual licensed as BSD 2-Clause License (http://opensource.org/licenses/BSD-2-Clause)
# Authors:
#   Rene Milk (2018)
# ~~~

import pytest
from dune.xt.common.test import load_all_submodule
from dune.xt.grid import types

def test_load_all():
    import dune.xt.grid as xtc
    load_all_submodule(xtc)


def test_types():
    cache = {}
    rt = types.all_types(cache=cache, dims=(2,3))
    assert len(rt) == 0
