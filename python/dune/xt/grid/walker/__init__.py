try:
    from dune.xt._walker import *
except ImportError as e:
    import os
    import logging
    if os.environ.get('DXT_PYTHON_DEBUG', False):
        raise e
    logging.error('dune-xt-grid bindings not available')


def make_walker(gridprovider, level = 0):
    for factory in [globals()[s] for s in globals().keys() if s.startswith('make_walker_on_')]:
        try:
            return factory(gridprovider, level)
        except:
            continue
    raise TypeError('no matching walker for gridview {}'.format(gridprovider.__class__))


def make_apply_on_dirichlet_intersections(boundaryinfo, grid, layer='leaf_view', *args, **kwargs):
    factory = globals()['make_apply_on_dirichlet_intersections_{}_{}'.format(layer,grid.grid_type)]
    return factory(boundaryinfo, *args, **kwargs)
