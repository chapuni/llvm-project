import json
import os
import subprocess
import sys

if len(sys.argv) < 6:
    sys.stderr.write("Specify <cmake_to_generate> <bin_root> <module_dir> <clang-scan-dep> <compiler_flags...>\n")
    sys.exit(1)

cmake_to_generate = sys.argv[1]
bin_root = sys.argv[2]
module_dir = sys.argv[3]
scandep = sys.argv[4]
compiler_args = sys.argv[5:]

with open("m.json", "w") as fcdb:
    cdb = [
        {
            "command": "/home/chapuni/llvm/install/2libcxx/bin/clang++ -o /dev/null -c /tmp/foo.cc " + ' '.join(compiler_args),
            "directory": bin_root,
            "file": "/tmp/foo.cc",
        },
    ]
    fcdb.write(json.dumps(cdb, indent=2))

with subprocess.Popen(
    [
        scandep,
        "--compilation-database", "m.json",
        "--enum-modules",
    ],
    stdout=subprocess.PIPE,
) as p:

    outs = json.load(p.stdout)

    result = p.wait()
    #assert result == 0

mods_by_maps = {}

hash_seen = None
for (h,d) in outs["hashes"].items():
    hash_seen = h
    for (mod,recs) in outs["modules"].items():
        modmap = os.path.normpath(recs["modulemap"])
        modmapr = os.path.relpath(modmap, bin_root)
        if not modmapr.startswith(".."):
            modmap = modmapr
        if modmap not in mods_by_maps:
            mods_by_maps[modmap] = {}
        mods_by_maps[modmap][mod] = recs["filename"]

with open(cmake_to_generate, "w") as cmake:

    cmake.write("""# Generated file

set(moddir ${CMAKE_BINARY_DIR}/%s/%s)
""" % (os.path.relpath(module_dir, bin_root), hash_seen))

    mi = 0
    for modmap in sorted(mods_by_maps.keys()):
        mods = mods_by_maps[modmap]
        def fn(x):
            return "%s.cpp" % x

        mn = "mod_%d" % mi
        mi += 1

        cmake.write("""
# (%d files) %s
llvm_add_library(%s STATIC EXCLUDE_FROM_ALL
  %s
  )
set_target_properties(%s PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
""" % (
    len(mods), modmap,
    mn, "\n  ".join(map(fn, mods.keys())),
    mn,
    ))
        for (mod,pcm) in mods.items():
            cfn = fn(mod)
            with open("%s" % cfn, "w") as f:
                f.write("#pragma clang module import %s\n" % mod)
            cmake.write("set_source_files_properties(%s PROPERTIES OBJECT_OUTPUTS ${moddir}/%s)\n" % (cfn, pcm))
        cmake.write("add_dependencies(%s anchor_all)\n" % mn)

    cmake.write("\n#EOF\n")

#EOF
