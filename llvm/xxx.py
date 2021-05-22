import os
import re
import subprocess
import sys

# name, [fn_suf]
targets = {}
src_set = set()

for arg in sys.argv[3:]:
    m = re.match(r'^(.+)=(.+)$', arg)
    assert m
    m_name = m.group(1)

    items = set()
    for fn in m.group(2).split(','):
        items.add(fn)
        src_set.add(fn)

    targets[m_name] = items

objfns = {}

# fn,set(sym)
defs = {}

# fn,set(sym)
undefs = {}

# fn.set(fn)
deffns = {}

defsyms = set()
undefsyms = set()

# sym,set(fn)
xdefs = {}
xundefs = {}

for objfn in sys.argv[2].split(','):
    if objfn.endswith('/TableGen.cpp.o'):
        continue
    with subprocess.Popen(
            #["/home/chapuni/llvm/install/1/bin/llvm-nm", "-g", objfn],
            #["nm", "-g", "--demangle", objfn],
            ["nm", "-g", objfn],
            stdout=subprocess.PIPE,
            text=True,
    ) as p:
        # Expects "foo.cpp" in "dir/foo.cpp.o"
        fn = os.path.basename(objfn)
        for src in src_set:
            if "/"+src in objfn:
                fn = src
                break
        objfns[os.path.basename(objfn)] = fn
        deffns[fn] = set()

        for line in p.stdout:
            m = re.match(r'^(\s+[Uw]|[0-9A-Fa-f]+\s+[Wu])\s+(?P<sym>\S.*\S)', line)
            if m:
                undefs.setdefault(fn,set()).add(m.group("sym"))
                undefsyms.add(m.group("sym"))
                xundefs.setdefault(m.group("sym"),set()).add(fn)
                continue
            m = re.match(r'^[0-9A-Fa-f]+\s+[A-Z]\s+(?P<sym>\S.*\S)', line)
            if m:
                defs.setdefault(fn,set()).add(m.group("sym"))
                defsyms.add(m.group("sym"))
                xdefs.setdefault(m.group("sym"),set()).add(fn)
                continue
            sys.stderr.write("Unknown line: <%s>\n" % line.rstrip())

extdefsyms = undefsyms - defsyms;
print(objfns.keys())

# fn,int
costs = {}

# .ninja_log
basedir = os.path.relpath(os.path.join(sys.argv[1], ".."))
ninja_log = "all.ninja_log"
if os.path.exists(ninja_log):
    with open(ninja_log) as f:
        for line in f:
            m = re.match(r'^(?P<s>\d+)\s+(?P<e>\d+)\s+\d+\s+(?P<o>\S+)', line)
            if not m:
                continue
            objfn = m.group("o")
            if not objfn.startswith(basedir):
                continue
            objfn = os.path.basename(objfn)
            if objfn not in objfns:
                continue
            t = int(m.group("e")) - int(m.group("s"))
            #print("%8d:%s" % (t, objfns[objfn]))
            costs[objfns[objfn]] = t

for fn,fnset_ in defs.items():
    if fn not in undefs:
        continue
    fnset = fnset_.copy()
    undefs_ = undefs[fn].copy()
    undefs_ -= extdefsyms
    while undefs_:
        undefs_cur = set()
        for sym in undefs_:
            for def_fn in xdefs[sym]:
                deffns[fn].add(def_fn)
                fnset |= defs[def_fn]
                if def_fn in undefs:
                    undefs_cur |= undefs[def_fn]
        undefs_cur -= extdefsyms
        undefs_ |= undefs_cur
        undefs_ -= fnset

def sum_costs(fns):
    return sum(map(lambda x:costs[x], fns))

mod_mods = {}
mod_fns = {}
mod_deps = {}
mod_costs = {}

for name,fns in targets.items():
    print("%s:" % name)
    mod_mods[name] = set()
    mod_deps[name] = set()
    for fn in fns:
        mod_deps[name] |= deffns[fn]
    mod_fns[name] = fns - mod_deps[name]
    mod_costs[name] = sum_costs(mod_fns[name])
    print("\t%s\t%8d" % (str(mod_fns[name]), sum_costs(mod_fns[name])))
    print("\t%s\t%8d" % (str(mod_deps[name]), sum_costs(mod_deps[name])))

mods = []
mod_outputs = {}
mod_refcnt = {}

while mod_costs:
    min_name = None
    min_cost = None
    for name,mod_cost in mod_costs.items():
        cost = mod_cost + sum_costs(mod_deps[name])
        if min_name is None or cost < min_cost:
            min_name = name
            min_cost = cost

    mods.append(min_name)
    mod_refcnt[min_name] = 0
    print("%s %d<%s>%s<%s>" % (min_name, min_cost, str(mod_mods[min_name]), str(mod_fns[min_name]), str(mod_deps[min_name])))
    min_mods = mod_fns[min_name] | mod_deps[min_name]
    mod_outputs[min_name] = "\nMODULE %s\n%s\n" % (min_name, "\n".join(sorted(list(min_mods))))
    if mod_mods[min_name]:
        mod_outputs[min_name] += "DEPENDS %s\n" % " ".join(sorted(list(mod_mods[min_name])))

    for name,mod_cost in mod_costs.items():
        if name!=min_name and not mod_deps[name].isdisjoint(min_mods):
            mod_deps[name] -= min_mods
            #mod_fns[name] |= min_mods
            mod_mods[name] -= mod_mods[min_name]
            mod_mods[name].add(min_name)
            mod_refcnt[min_name] += 1
    del mod_costs[min_name]

for name in mods:
    sys.stdout.write(mod_outputs[name])
    if mod_refcnt[name] > 0:
        print("SHARED")

sys.exit(1)
