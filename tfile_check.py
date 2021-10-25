#!/usr/bin/env python3

import sys
import os
import ROOT


def mk_range_list(start: (None, int), end: (None, int) = None, step: (None, int) = None) -> list:
    if start is None: return []
    if end is None:
        r = range(start)
    else:
        r = range(start, end, step) if step else range(start,end)
    l = [*r]
    if end:
        l.append(end)
    else:
        l.append(start)
    return l


def tfile_check(filestr: str, rejectRecovered: bool = False, parseEntries: bool = False, entries_range: (None, str) = None) -> int:
    if not filestr: return 1
    if not os.path.exists(filestr): return 2  # ENOENT
    if not os.path.isfile(filestr): return 2  # ENOENT
    try:
        tfile = ROOT.TFile(filestr)
    except Exception as e:
        print(e)
        sys.exit(2)

    if tfile.IsZombie(): return 71  # EPROTO
    if rejectRecovered and tfile.TestBit(ROOT.TFile.kRecovered): return 52  # EBADE
    if not parseEntries: return 0  # everything good so far

    file_tree_list = []  # make a list of directories and the trees within
    for tdir in tfile.GetListOfKeys():
        if not tdir.IsFolder(): continue
        for tr in tfile.Get(tdir.GetName()).GetListOfKeys():
            if tr.GetClassName() != 'TTree': continue
            file_tree_list.append(f'{tdir.GetName()}/{tr.GetName()}')

    for tree_name in file_tree_list:  # for each tree found
        tree = tfile.Get(tree_name)
        nent = tree.GetEntries()
        parsing_step = None
        if entries_range and entries_range.isdigit(): parsing_step = int(entries_range)
        for en in mk_range_list(0, nent, parsing_step):
            rez = tree.GetEntry(en, 1)
            if rez < 0:
                print(f'{tree_name}::Entry({en}) -> result: {rez}', flush = True)
                return 5  # EIO  I/O error

    return 0  # at this point everything is ok


def main():
    ROOT.EnableImplicitMT()

    if len(sys.argv) < 2:
        print("command [norecovered] [parse] [step entries_step/int]")
        sys.exit(1)

    def get_arg(target: list, item) -> bool:
        """Remove inplace all instances of item from list and return True if found"""
        len_begin = len(target)
        target[:] = [x for x in target if x != item]
        len_end = len(target)
        return len_begin != len_end

    def get_arg_value(target: list, item):
        val = None
        for x in target:
            if x == item:
                val = target.pop(target.index(x) + 1)
                target.pop(target.index(x))
        return val

    skipRecovered = get_arg(sys.argv, "norecovered")
    parse = get_arg(sys.argv, "parse")
    step = get_arg_value(sys.argv, "step")
    rez = tfile_check(sys.argv[1], skipRecovered, parse, step)
    sys.exit(rez)


if __name__ == '__main__':
    main()

