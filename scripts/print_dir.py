from pathlib import Path

def iterdir(path, depth=0, blacklist=[], make_include=False):
    skip = any(b in str(path) for b in blacklist)
    # print(str(path), blacklist, skip)
    tabs = "".join(["\t"] * depth)
    if skip:
        # print(f"{tabs}| {path} skipped")
        return ""
    dir_contents = []
    for d in path.iterdir():
        if d.is_dir():
            subdir_contents = iterdir(d,depth+1,blacklist=blacklist,make_include=make_include)
            # dir_contents.append(d / (d.stem + ".hpp"))
            if make_include and subdir_contents:
                subdir_include_file = str(d) + ".hpp"
                with open(subdir_include_file,"w+") as f:
                    f.write("#pragma once\n")
                    f.write(subdir_contents)
        else:
            dir_contents.append(d)
        # print(f"{tabs}| {d}")
    fn = lambda x: f"#include \"{str(x).replace('include/','')}\""
    return "\n".join(map(fn,dir_contents))

rootdir = Path("include/nmtools")
rootdir_contents = iterdir(rootdir, blacklist=["testing","meta","platform","utl","stl","ref","utility","evaluator","impl","core"], make_include=True)
print(rootdir_contents)