import json
import os
import re
import subprocess
import sys

if len(sys.argv) < 7:
    sys.stderr.write("Specify <cmake_to_generate> <bin_root> <repo_root> <module_dir> <clang-scan-dep> <compiler_flags...>\n")
    sys.exit(1)

cmake_to_generate = sys.argv[1]
bin_root = sys.argv[2]
repo_root = sys.argv[3]
module_dir = sys.argv[4]
scandep = sys.argv[5]
compiler_arg = ' ' + ' '.join(sys.argv[6:]) + ' '

while True:
    n=list(range(0,9))
    compiler_arg,n[0] = re.subn(r'\$<SEMICOLON>', ' ', compiler_arg)
    compiler_arg,n[1] = re.subn(r'\$<TARGET_PROPERTY:LLVM_USE_PREBUILT_MODULES>', 'FALSE', compiler_arg)
    compiler_arg,n[2] = re.subn(r'\$<TARGET_PROPERTY:[^$,:<>]+>', '', compiler_arg)
    compiler_arg,n[3] = re.subn(r'\$<BOOL:(OFF|FALSE)?>', '0', compiler_arg)
    compiler_arg,n[4] = re.subn(r'\$<BOOL:[^$,<>]+>', '1', compiler_arg)
    compiler_arg,n[5] = re.subn(r'\$<(COMPILE_LANGUAGE:CXX|NOT:0|AND:1,1)>', '1', compiler_arg)
    compiler_arg,n[6] = re.subn(r'\$<NOT:1>', '0', compiler_arg)
    compiler_arg,n[7] = re.subn(r'\$<IF:1,([^$,:<>]+),([^$,:<>]+)>', r'\1', compiler_arg)
    compiler_arg,n[7] = re.subn(r'\$<IF:0,([^$,:<>]+),([^$,:<>]+)>', r'\2', compiler_arg)
    compiler_arg,n[7] = re.subn(r'\$<1:([^$,:<>]+)>', r'\1', compiler_arg)
    compiler_arg,n[8] = re.subn(r'\$<0:([^$,:<>]+)>', '', compiler_arg)
    if sum(n)==0:
        break

compiler_arg = re.sub(r' -fmodule-file-deps ', ' ', compiler_arg)

with open("m.json", "w") as fcdb:
    cdb = [
        {
            #"command": "/home/chapuni/llvm/install/2libcxx/bin/clang++ -o /dev/null -c /tmp/foo.cc " + ' '.join(compiler_args),
            #"command": "/home/chapuni/llvm/install/2libcxx/bin/clang-scan-deps -o /dev/null -c /tmp/foo.cc " + ' '.join(compiler_args),
            "command": scandep + " -o /dev/null -c /tmp/foo.cc " + compiler_arg,
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

map_names = set()
mods_by_maps = {}

hash_seen = None
for (h,d) in outs["hashes"].items():
    hash_seen = h
    for (mod,recs) in outs["modules"].items():
        modmap = os.path.normpath(recs["modulemap"])
        modmapr = os.path.relpath(modmap, bin_root)
        if not modmapr.startswith(".."):
            modmap = modmapr
        else:
            modmapr = os.path.relpath(modmap, repo_root)
            if not modmapr.startswith(".."):
                modmap = modmapr
        if modmap not in mods_by_maps:
            mods_by_maps[modmap] = {}
        mods_by_maps[modmap][mod] = recs["filename"]

with open(cmake_to_generate, "w") as cmake:

    cmake.write("""# Generated file

add_custom_target(module.cache)
set_target_properties(module.cache PROPERTIES EXCLUDE_FROM_DEFAULT_BUILD ON)

set(moddir ${CMAKE_BINARY_DIR}/%s/%s)
""" % (os.path.relpath(module_dir, bin_root), hash_seen))

    mi = 1
    for modmap in sorted(mods_by_maps.keys()):
        mods = mods_by_maps[modmap]
        def fn(x):
            return "%s.cpp" % x

        ms = re.sub(r'[^-+._0-9A-Za-z]', '-', modmap)
        ms = re.sub(r'^-', '', ms)
        if ms in map_names:
            ms = "%s_%d" % (ms, mi)
            mi += 1
        map_names.add(ms)

        mn = ms

        cmake.write("""
# (%d files) %s
llvm_add_library(%s STATIC EXCLUDE_FROM_ALL
  %s
  )
set_target_properties(%s PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR} ADDITIONAL_CLEAN_FILES ${moddir})
""" % (
    len(mods), modmap,
    mn, "\n  ".join(map(fn, mods.keys())),
    mn,
    ))
        for (mod,pcm) in mods.items():
            cfn = fn(mod)
            line = "#pragma clang module import %s\n" % mod
            if os.path.exists(cfn):
                with open(cfn) as f:
                    if line==f.read():
                        line = ""
            if line != "":
                with open(cfn, "w") as f:
                    f.write(line)
            cmake.write("set_source_files_properties(%s PROPERTIES OBJECT_OUTPUTS ${moddir}/%s)\n" % (cfn, pcm))
        cmake.write("add_dependencies(%s anchor_all)\n" % mn)
        cmake.write("add_dependencies(module.cache %s)\n" % mn)

    cmake.write("\n#EOF\n")

#EOF
