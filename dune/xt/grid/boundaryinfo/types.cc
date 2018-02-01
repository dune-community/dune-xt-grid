// This file is part of the dune-xt-grid project:
//   https://github.com/dune-community/dune-xt-grid
// Copyright 2009-2018 dune-xt-grid developers and contributors. All rights reserved.
// License: Dual licensed as BSD 2-Clause License (http://opensource.org/licenses/BSD-2-Clause)
//      or  GPL-2.0+ (http://opensource.org/licenses/gpl-license)
//          with "runtime exception" (http://www.dune-project.org/license.html)
// Authors:
//   Felix Schindler (2018)

#include <config.h>

#include "types.hh"

namespace Dune {
namespace XT {
namespace Grid {


BoundaryType* make_boundary_type(const std::string& id)
{
  if (id == NoBoundary().id())
    return new NoBoundary();
  else if (id == UnknownBoundary().id())
    return new UnknownBoundary();
  else if (id == DirichletBoundary().id())
    return new DirichletBoundary();
  else if (id == NeumannBoundary().id())
    return new NeumannBoundary();
  else if (id == RobinBoundary().id())
    return new RobinBoundary();
  else if (id == ReflectingBoundary().id())
    return new ReflectingBoundary();
  else if (id == InflowBoundary().id())
    return new InflowBoundary();
  else if (id == OutflowBoundary().id())
    return new OutflowBoundary();
  else if (id == InflowBoundary().id())
    return new InflowBoundary();
  else if (id == InflowOutflowBoundary().id())
    return new InflowOutflowBoundary();
  else if (id == ImpermeableBoundary().id())
    return new ImpermeableBoundary();
  else {
    DUNE_THROW(Exceptions::boundary_type_error, "id: " << id);
    return new UnknownBoundary();
  }
} // ... make_boundary_type(...)


} // namespace Grid
} // namespace XT
} // namespace Dune
