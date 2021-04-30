#! /usr/bin/env python3

import os
import pathlib
import re
import sys

includes = [
    '/home/chapuni/llvm/llvm-project/clang/include',
    'tools/clang/include',
    'include',
    '/home/chapuni/llvm/llvm-project/llvm/include',
    '/home/chapuni/llvm/install/2libcxx/bin/../include/c++/v1',
    '/home/chapuni/llvm/install/2libcxx/lib/clang/12.0.0/include',
    ]

re_toks = re.compile(r'''
  \s*
  (
   "([^"]*)"
  |\[(\w+)\]
  |(\w+(\.\w+)*)
  |(\S)
  )\s*
''', re.DOTALL | re.VERBOSE)

def parse_ext_module(toks):
    assert len(toks) >= 3
    t = toks.pop(0)[0]
    assert t == 'module'
    t = toks.pop(0)[0]
    return {"name": t, "modmap": toks.pop(0)[1]}

def parse_module(toks):
    mod = {
        "attrs": [],
        "exports": [],
        "extern": [],
        "mods": [],
        "exc": [],
        "header": [],
        "text": [],
        "reqnot": [],
        "requires": [],
    }
    assert len(toks) >= 3
    mod["name"] = toks.pop(0)[0]
    while toks[0][0].startswith('['):
        mod["attrs"].append(toks.pop(0)[2])
    t = toks.pop(0)[0]
    assert t == '{', str(toks)
    while True:
        assert toks
        t = toks.pop(0)[0]
        if t == '}':
            break
        if t == 'requires':
            while True:
                assert len(toks) >= 1
                t = toks.pop(0)[0]
                if t == '!':
                    assert len(toks) >= 1
                    t = toks.pop(0)[0]
                    mod["reqnot"].append(t)
                else:
                    mod["requires"].append(t)
                if len(toks) >= 2 and toks[0][0] == ',':
                    toks.pop(0)
                    continue
                break
            continue
        if t == 'exclude':
            assert len(toks) >= 2
            t = toks.pop(0)[0]
            assert t == 'header'
            mod["exc"].append(toks.pop(0)[1])
            continue
        if t == 'header':
            assert len(toks) >= 1
            mod["header"].append(toks.pop(0)[1])
            continue
        if t == 'textual':
            assert len(toks) >= 2
            t = toks.pop(0)[0]
            assert t == 'header'
            mod["text"].append(toks.pop(0)[1])
            continue
        if t == 'umbrella':
            assert len(toks) >= 1
            assert "umbrella" not in mod
            mod["umbrella"] = toks.pop(0)[1]
            continue
        if t == 'explicit':
            assert len(toks) >= 2
            t = toks.pop(0)[0]
            assert t == 'module'
            xmod = parse_module(toks)
            xmod["explicit"] = True
            mod["mods"].append(xmod)
            continue
        if t == 'module':
            mod["mods"].append(parse_module(toks))
            continue
        if t == 'export':
            assert len(toks) >= 2
            mod["exports"].append(toks.pop(0))
            continue
        if t == 'extern':
            mod["extern"].append(parse_ext_module(toks))
            continue
        assert False, "<%s>%s" % (t, str(toks))

    return mod

def parse_decls(toks):
    mods = []
    while toks:
        t = toks.pop(0)[0]
        if t == 'explicit':
            t = toks.pop(0)[0]
            assert t == 'module'
            mod = parse_module(toks)
            mod["explicit"] = True
            mods.append(mod)
            continue
        if t == 'module':
            mods.append(parse_module(toks))
            continue
        if t == 'extern':
            mods.append(parse_ext_module(toks))
            continue
        assert False, "<%s>%s" % (t, str(toks))

    return mods

# from SO #241327
def comment_remover(text):
    def replacer(match):
        s = match.group(0)
        if s.startswith('/'):
            return " " # note: a space and not an empty string
        else:
            return s

    pattern = re.compile(
        r'//.*?$|/\*.*?\*/|\'(?:\\.|[^\\\'])*\'|"(?:\\.|[^\\"])*"',
        re.DOTALL | re.MULTILINE
    )
    return re.sub(pattern, replacer, text)

def parse_modulemap(fn):
    with open(fn) as f:
        s = f.read()
        s = comment_remover(s)
        toks = re_toks.findall(s)
        mods = parse_decls(toks)

for d in includes:
    if not os.path.isdir(d):
        continue
    for fn in pathlib.Path(d).glob('**/module.modulemap'):
        print("Found <%s>" % fn)
        parse_modulemap(fn)
        #sys.exit(0)

#EOF
