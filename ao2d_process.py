#!/usr/bin/env python3

import os
import sys
from rich.pretty import pprint
from rich.table import Table
from rich.console import Console
import fileinput as fi
import math
import time

try:
    import ROOT
except Exception:
    print("This script requires the python module of ROOT", file = sys.stderr, flush = True)
    sys.exit(1)

ROOT.EnableImplicitMT()

_DEBUG = False
_PRINT_DATA_STRUCTURE = True

def get_arg(target: list, item) -> bool:
    """Remove inplace all instances of item from list and return True if found"""
    len_begin = len(target)
    target[:] = [x for x in target if x != item]
    len_end = len(target)
    return len_begin != len_end


exec_name = sys.argv.pop(0)
_PRINT_DATA_STRUCTURE = get_arg(sys.argv, "showdata")
SHOW_HELP = (get_arg(sys.argv, "-h") or get_arg(sys.argv, "--h") or get_arg(sys.argv, "-help") or get_arg(sys.argv, "--help"))
BATCH = (get_arg(sys.argv, "batch") or get_arg(sys.argv, "-b"))

if SHOW_HELP:
    print('showdata : it will print a table with data structure without continuing to processing\n'
          '-b | batch : it will not stop at the end for canvas inspection'
          )
    sys.exit()


file_list = []
with fi.input(files=['file_list']) as f:
    for line in f: file_list.extend(line.strip().split())
file_list = [ f for f in file_list if not (f.startswith('#') and f)]


MAIN_TREE = "O2track"
tree_list = []  # list of all trees find in a DF_ directory

chain = ROOT.TChain(MAIN_TREE)  # main chain to be processed

tree_list_filled = False  # fill the list of trees only for first read file/first directory
for f in file_list:
    try:
        tfile = ROOT.TFile(f)
    except Exception:
        continue
    for tdir in tfile.GetListOfKeys():  # for each directory
        if not tdir.IsFolder(): continue
        tree_name = f'{f}?query#{tdir.GetName()}/{MAIN_TREE}'  # https://root.cern.ch/doc/master/classTChain.html#a4d491db32262125e6cb77a8f7a6bfd93
        if _DEBUG: print(tree_name)
        chain.AddFile(tree_name)

        if not tree_list_filled:
            for t in tfile.Get(tdir.GetName()).GetListOfKeys():  # get the name of the other trees from the same TDir
                if t.GetClassName() != 'TTree': continue
                if not tree_list_filled: tree_list.append(t.GetName())
            tree_list_filled = True

if MAIN_TREE in tree_list: tree_list.remove(MAIN_TREE)  # remove the tree that we used for the main chain

chain_list = []  # keep a list of chains to be used

# create chains for the other trees
for t_name in tree_list:
    chain_other = ROOT.TChain(t_name)
    for f in file_list:
        try:
            tfile = ROOT.TFile(f)
        except Exception:
            continue
        for tdir in tfile.GetListOfKeys():
            if not tdir.IsFolder(): continue
            tree_name = f'{f}?query#{tdir.GetName()}/{t_name}'
            if _DEBUG: print(tree_name)
            chain_other.AddFile(tree_name)
    chain_list.append(chain_other)

## add friends to the main chain; the list is manual
friends_names_list = ['O2mctracklabel', 'O2trackcov', 'O2trackextra' ]
#for frd in friends_names_list:
#    for ch in chain_list:
#        if ch.GetName() == frd: chain.AddFriend(ch)


if _PRINT_DATA_STRUCTURE:
    table = Table(title = None)
    table.add_column("Chain/Tree name", justify="left")
    table.add_column("Entries", justify="right")
    table.add_column("Branches", justify="left")

    table.add_row(f'{chain.GetName()}',f'{chain.GetEntries()}', ' '.join( [br.GetName() for br in chain.GetListOfBranches()] ))
    [table.add_row(f'{ch.GetName()}',f'{ch.GetEntries()}', ' '.join( [br.GetName() for br in ch.GetListOfBranches()] )) for ch in chain_list]

    console = Console()
    console.print(table)

    # Print friends already added to the main chain
    print(f'\nMain chain have these friends:\n{[fr.GetName().strip() for fr in chain.GetListOfFriends()]}\n')
    sys.exit()

###########################################
##   DATA CRUNCHING
###########################################

ROOT.gROOT.LoadMacro('alice_DataModel.C+')  # compiled form of data definitions

df = ROOT.RDataFrame(chain)

pt_node = df.Define('pt', 'alice_o2::define_pt(fSigned1Pt)')

h_pt = pt_node.Histo1D(("pt", "p_{T};p_{T};n_{Tracks}", 150, 0, 150), 'pt')

c1 = ROOT.TCanvas("c1", "c1", 1500, 1000)
c1.cd()
c1.SetLogy()
h_pt.Draw()
c1.SaveAs("pt.png")












if not BATCH: input('Please press enter to continue.')

