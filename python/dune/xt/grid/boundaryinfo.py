try:
    from dune.xt._boundaryinfo import *
except ImportError as e:
    import os
    import logging
    if os.environ.get('DXT_PYTHON_DEBUG', False):
        raise e
    logging.error('dune-xt-grid bindings not available')


def _meta_boundary(name, grid_provider, config):
    for factory in [globals()[s] for s in globals().keys() if s.startswith(name)]:
        try:
            return factory(grid_provider, config)
        except:
            continue
    raise TypeError('no matching {} for boundaryinfo {}'.format(name, grid_provider.__class__))


def make_boundary_info_on_dd_subdomain_boundary_layer(grid_provider, config):
    return _meta_boundary('make_boundary_info_on_dd_subdomain_boundary_layer', grid_provider, config)

def make_boundary_info_on_dd_subdomain_layer(grid_provider, config):
    return _meta_boundary('make_boundary_info_on_dd_subdomain_layer', grid_provider, config)

def make_boundary_info_on_leaf_layer(grid_provider, config):
    return _meta_boundary('make_boundary_info_on_leaf_layer', grid_provider, config)