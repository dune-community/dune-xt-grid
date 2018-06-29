// This file is part of the dune-xt-grid project:
//   https://github.com/dune-community/dune-xt-grid
// Copyright 2009-2018 dune-xt-grid developers and contributors. All rights reserved.
// License: Dual licensed as BSD 2-Clause License (http://opensource.org/licenses/BSD-2-Clause)
//      or  GPL-2.0+ (http://opensource.org/licenses/gpl-license)
//          with "runtime exception" (http://www.dune-project.org/license.html)
// Authors:
//   Felix Schindler (2017)
//   Rene Milk       (2018)

#include "config.h"

#include <string>
#include <vector>

#include <dune/common/parallel/mpihelper.hh>

#include <dune/pybindxi/pybind11.h>
#include <dune/pybindxi/stl.h>

#include <python/dune/xt/common/exceptions.bindings.hh>


#include <python/dune/xt/common/bindings.hh>
#include <python/dune/xt/grid/boundaryinfo.bindings.hh>


PYBIND11_MODULE(_boundaryinfo, m)
{
  namespace py = pybind11;
  using namespace pybind11::literals;

  DUNE_XT_GRID_BOUNDARYINFO_BIND(m);
}

DUNE_XT_GRID_BOUNDARYINFO_BIND_LIB(template);