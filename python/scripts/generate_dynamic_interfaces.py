#!/usr/bin/env python

import sys
import os
from jinja2 import Template
from pprint import pprint

try:
    from clang import cindex
except Exception as e:
    from dune.xt.clang import cindex


from dune.xt.clang_ast import parse_source, build_classes, dump_ast

if len(sys.argv) != 3:
    print("Usage: generate_dynamic_interfaces.py <builddir> <sourcedir>")
    sys.exit()

builddir = sys.argv[1]
sourcedir = sys.argv[2]
outfile = os.path.join(builddir, 'dynamic_interfaces.hh')

clang_so = os.environ.get('DXT_LIBCLANG_SO', '/usr/lib/libclang.so')
cindex.Config.set_library_file(clang_so)

source = os.path.join(sourcedir, 'dynamic_interfaces.dummy.cc')
translation_unit = parse_source(source_file=source,
                                build_dir=builddir)
try:
    for inc in translation_unit.get_includes():
        pass
except AttributeError:
    pass


def add_class(a_class):
    n = a_class.name.lower()
    return 'view' in n

classes = build_classes(translation_unit.cursor, add_class)
tpl = Template(open(os.path.join(sourcedir, 'dynamic_interfaces.tpl'), 'rt').read())
rendered = tpl.render(classes=classes)

with open(os.path.join(builddir, 'dynamic_interfaces.hh'), 'wt') as f:
    f.write(rendered)
pprint([c.name for c in classes])

#print(dump_ast(translation_unit.cursor))
