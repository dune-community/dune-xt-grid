//
// Created by r_milk01 on 11/13/18.
//

#ifndef DUNE_XT_GRID_REPARTITION_HH
#define DUNE_XT_GRID_REPARTITION_HH

#include <array>
#include <memory>
#include <sstream>
#include <type_traits>
#include <vector>
#include <limits>

#include <dune/xt/grid/grids.hh>
#include <dune/xt/grid/type_traits.hh>
#include <dune/xt/grid/output/entity_visualization.hh>

namespace Dune {
namespace XT {
namespace Grid {

//! no-op class for non alugrids
template <class Grid>
class RepartitionHandle
{
  using Element = extract_entity_t<Grid>;

public:
  RepartitionHandle(Grid&, const std::function<size_t(const Element&)>&) {}
  bool repartition()
  {
    return false;
  }
  void visualize(std::string) const {}
};


#if HAVE_DUNE_ALUGRID
template <int dim, int dimworld, ALUGridElementType elType, ALUGridRefinementType refineType, class Comm>
class RepartitionHandle<ALUGrid<dim, dimworld, elType, refineType, Comm>>
{
  using GridType = ALUGrid<dim, dimworld, elType, refineType, Comm>;
  using Element = extract_entity_t<GridType>;
  using IdToSubdomainMap = std::map<ALUMacroKey, size_t>;
  using GlobalIdSet = typename GridType::GlobalIdSet;

public:
  RepartitionHandle(GridType& grid, const std::function<size_t(const Element&)>& key_functor)
    : grid_(grid)
    , global_id_set_(grid_.globalIdSet())
    , id_map_()
    , max_rank_(grid.comm().size())
  {
    // walk the grid
    const auto view = grid.levelGridView(0);
    auto entity_it_end = view.template end<0, All_Partition>();
    for (auto entity_it = view.template begin<0, All_Partition>(); entity_it != entity_it_end; ++entity_it) {
      // add entity to subdomain
      const ALUMacroKey key = global_id_set_.id(*entity_it).getKey();
      id_map_[key] = key_functor(*entity_it);
    } // walk the grid
  }

  //! returns the rank to which the element is to be moved.
  int operator()(const Element& element) const
  {
    const auto key = global_id_set_.id(element).getKey();
    const size_t subdomain = id_map_.at(key);
    return subdomain % max_rank_;
  }

  /** This method can simply return false, in which case ALUGrid
      will internally compute the required information through
      some global communication. To avoid this overhead the user
      can provide the ranks of particians from which elements will
      be moved to the calling partitian. */
  bool importRanks(std::set<int>&) const
  {
    return false;
  }

  bool repartition()
  {
    return grid_.repartition(*this);
  }

  GridType& grid_;
  const GlobalIdSet& global_id_set_;
  IdToSubdomainMap id_map_;
  size_t max_rank_;
};

#endif

//! return true if grid has changed
template <class Grid>
bool do_repartition(Grid& grid, const std::function<size_t(const extract_entity_t<Grid>&)>& func)
{
  RepartitionHandle<Grid> rph(grid, func);
  visualize_index_per_level(grid, "grid_pre_");
  const bool changed{rph.repartition()};
  visualize_index_per_level(grid, "grid_post_");
  return changed;
}


} // namespace Grid
} // namespace XT
} // namespace Dune

#endif // DUNE_XT_GRID_REPARTITION_HH
