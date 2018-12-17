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


def make_apply_on_dirichlet_intersections(boundaryinfo, *args, **kwargs):
    for factory in [globals()[s] for s in globals().keys() if s.startswith('make_apply_on_dirichlet_intersections_')]:
        try:
            return factory(boundaryinfo, *args, **kwargs)
        except:
            continue
    raise TypeError('no matching make_apply_on_dirichlet_intersections for boundaryinfo {}'.format(boundaryinfo.__class__))