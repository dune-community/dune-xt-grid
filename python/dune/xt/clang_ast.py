import re
from pprint import pprint

import subprocess

try:
    from clang import cindex
except Exception as e:
    from dune.xt.clang import cindex




def get_diag_info(diag):
    return { 'severity' : diag.severity,
             'location' : diag.location,
             'spelling' : diag.spelling,
             'ranges' : diag.ranges,
             'fixits' : diag.fixits }


class Function(object):
    def __init__(self, cursor):
        self.name = cursor.spelling
        self.access = cursor.access_specifier
        self.parameters = [cursor.get_template_argument_type(i) for i in range(cursor.get_num_template_arguments())] + list(cursor.get_arguments())
        parameter_dec = [c for c in cursor.get_children() if c.kind == cindex.CursorKind.PARM_DECL]
        self.parameters = [p.spelling or p.displayname for p in parameter_dec]
        self.declaration = ''
        for token in cursor.translation_unit.get_tokens(extent=cursor.extent):
            if '{' in token.spelling:
                break
            self.declaration += ' '+token.spelling


class Class(object):
    def __init__(self, cursor):
        self.name = cursor.spelling
        self.functions = []

        for c in cursor.get_children():
            if c.access_specifier != cindex.AccessSpecifier.PUBLIC:
                continue
            if (c.kind == cindex.CursorKind.CXX_METHOD) or \
                    (c.kind == cindex.CursorKind.FUNCTION_TEMPLATE):
                self.functions.append(Function(c))


def build_classes(cursor, include=lambda _: False):
    result = []
    for c in cursor.get_children():
        if c.kind == cindex.CursorKind.CLASS_DECL or c.kind == cindex.CursorKind.CLASS_TEMPLATE:
            a_class = Class(c)
            if include(a_class):
                result.append(a_class)
        elif c.kind == cindex.CursorKind.NAMESPACE:
            child_classes = build_classes(c, include)
            result.extend(child_classes)

    return result


def dump_ast(cursor):
    import asciitree
    def node_children(node):
        return [c for c in node.get_children() ]

    def print_node(node):
        text = node.spelling or node.displayname
        kind = str(node.kind)[str(node.kind).index('.')+1:]
        return '{} {}'.format(kind, text)

    asciitree.draw_tree(cursor, node_children, print_node)


def _get_system_includes():
    process_out = subprocess.check_output(['clang', '-v', '-E', '-x', 'c++', '-'],
                                          stderr=subprocess.STDOUT,
                                          universal_newlines=True)
    begin = '#include <...> search starts here:'
    end = 'End of search list'
    begin = process_out.index(begin) + len(begin)
    end = process_out.index(end)
    res = []
    for inc in process_out[begin:end].split():
        res.append('-isystem')
        res.append(inc)
    return(res)


def parse_source(source_file, build_dir):
    index = cindex.Index.create()
    db = cindex.CompilationDatabase.fromDirectory(build_dir)
    sys_includes = _get_system_includes()
    sys_includes.append('-I{}'.format(build_dir))
    file_args = [g for g in db.getCompileCommands(source_file)]

    tu = index.parse(path='', args=list(file_args[0].arguments)+sys_includes)
    for d in tu.diagnostics:
        if d.severity > 2:
            pprint(get_diag_info(d))
            raise RuntimeError(get_diag_info(d))
    return tu
