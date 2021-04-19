#!/usr/bin/env python3

import json
import re
import sys

ddi = {
    "version": 0,
    "rules": [
        {
            "work-directory": ".",
            "inputs": [
                "iii/i0",
                "iii/i1",
            ],
            "outputs": [
                "ooo/o1",
                "ooo/o2",
            ],
            "depends": [
                "ddd/foo",
                "ddd/bar",
            ],
            "future-compile": {
                "outputs": [
                    "aaa/ooof",
                    "bbb/ooob",
                ],
                "provides": [
                    {
                        "logical-name": "pln",
                        "compiled-module-path": "p/cmp",
                    },
                ],
                "requires": [
                    {
                        "logical-name": "r/ln1",
                    },
                    {
                        "logical-name": "r/ln2",
                        "source-path": "r/sp2",
                    },
                ],
            },
        },
    ],
}

with open(sys.argv[1]) as f:
    ds = re.sub(r'\\\n', '', ''.join(f.read())).split()

m = re.match(r'^\s*(.*/(\w[^/]*)\.cpp\.o):\s*$', ds.pop(0))
target = m.group(1)
stem = m.group(2)

ddi["rules"][0]["future-compile"]["outputs"][0] = target
provides = [];
ddi["rules"][0]["future-compile"]["provides"] = provides
requires = []
ddi["rules"][0]["future-compile"]["requires"] = requires

for d in ds:
    if not d.startswith(sys.argv[2]):
        continue
    m = re.match(r'.*/(\w[^/]*)\.pcm$', d)
    if not m:
        continue
    if m.group(1)==stem:
        provides.append({
            "logical-name":stem,
            "compiled-module-path": d,
        })
    else:
        requires.append({
            "logical-name":m.group(1),
            "compiled-module-path": d,
        })

with open(sys.argv[3], 'w') as f:
    f.write(json.dumps(ddi, indent=2))

#EOF
