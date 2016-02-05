// This file is part of the dune-xt-grid project:
//   https://github.com/dune-community/dune-xt-grid
// The copyright lies with the authors of this file (see below).
// License: Dual licensed as  BSD 2-Clause License (http://opensource.org/licenses/BSD-2-Clause)
//      or  GPL-2.0+ (http://opensource.org/licenses/gpl-license)
//          with "runtime exception" (http://www.dune-project.org/license.html)
// Authors:
//   Felix Schindler (2016)

#ifndef DUNE_XT_GRID_BOUNDARYINFO_FACTORY_HH
#define DUNE_XT_GRID_BOUNDARYINFO_FACTORY_HH

#include "interfaces.hh"
#include "alldirichlet.hh"
#include "allneumann.hh"
#include "normalbased.hh"

namespace Dune {
namespace XT {
namespace Grid {


template <class I>
class BoundaryInfoFactory
{
public:
  static std::vector<std::string> available()
  {
    return {AllDirichletBoundaryInfo<I>::static_id(),
            AllNeumannBoundaryInfo<I>::static_id(),
            NormalBasedBoundaryInfo<I>::static_id()};
  }

  static Common::Configuration default_config(const std::string type)
  {
    if (type == AllDirichletBoundaryInfo<I>::static_id())
      return alldirichlet_boundaryinfo_default_config();
    else if (type == AllNeumannBoundaryInfo<I>::static_id())
      return /**/ Common::Configuration();
    else if (type == NormalBasedBoundaryInfo<I>::static_id())
      return /**/ Common::Configuration();
    else
      DUNE_THROW(Common::Exceptions::wrong_input_given,
                 "'" << type << "' is not a valid " << BoundaryInfo<I>::static_id() << "!");
  } // ... default_config(...)

  static std::unique_ptr<BoundaryInfo<I>> create(const std::string& type = available()[0],
                                                 const Common::Configuration config = Common::Configuration())
  {
    if (type == AllDirichletBoundaryInfo<I>::static_id())
      return make_alldirichlet_boundaryinfo<I>(config);
    else if (type == AllNeumannBoundaryInfo<I>::static_id())
      return make_allneumann_boundaryInfo<I>(config);
    else if (type == NormalBasedBoundaryInfo<I>::static_id())
      return make_normalbased_boundaryInfo<I>(config);
    else
      DUNE_THROW(Common::Exceptions::wrong_input_given,
                 "'" << type << "' is not a valid " << BoundaryInfo<I>::static_id() << "!");
  } // ... create(...)

  static std::unique_ptr<BoundaryInfo<I>> create(const Common::Configuration& config)
  {
    return create(config.get<std::string>("type"), config);
  }

}; // class BoundaryInfoFactory


} // namespace Grid
} // namespace XT
} // namespace Dune

#endif // DUNE_XT_GRID_BOUNDARYINFO_FACTORY_HH