#!/usr/bin/env python3

import os
import sys
import rich
from rich.console import Console
from rich.pretty import pprint
from rich.table import Table
import fileinput as fi
import math
import time
from array import array
import numpy as np


try:
    import ROOT
    from ROOT import addressof
except Exception:
    print("This script requires the python module of ROOT", file = sys.stderr, flush = True)
    sys.exit(1)

ROOT.EnableImplicitMT()

_DEBUG = True
_PRINT_DATA_STRUCTURE = True
ADD_FRIENDS = True

def get_arg(target: list, item) -> bool:
    """Remove inplace all instances of item from list and return True if found"""
    len_begin = len(target)
    target[:] = [x for x in target if x != item]
    len_end = len(target)
    return len_begin != len_end


def get_df_list(tfile: ROOT.TFile) -> list:
    if not tfile: return []
    out_list = []
    for tdir in tfile.GetListOfKeys():  # for each directory
        if not tdir.IsFolder(): continue
        dir_name = tdir.GetName()
        out_list.append(dir_name)
        # tree_name = f'{f}?#{tdir.GetName()}/{tree_name_track}'  # https://root.cern.ch/doc/master/classTChain.html#a4d491db32262125e6cb77a8f7a6bfd93
    return out_list


def get_df_trees(tfile: ROOT.TFile, dir_name):
    if not tfile: return []
    out_list = []
    for t in tfile.Get(dir_name).GetListOfKeys():  # get the name of the other trees from the same TDir
        if t.GetClassName() != 'TTree': continue
        out_list.append(t.GetName())
    return out_list


def dict_add2key(dict_arg: dict, arg1, arg2):
    if arg1 not in dict_arg:dict_arg[arg1] = []
    dict_arg[arg1].append(arg2)


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

if not file_list:
    print('file list is empty')
    sys.exit(1)


tree_list = []  # list of all trees find in a DF_ directory
tree_list_found = False  # fill the list of trees only for first read file/first directory
tree_name_track='O2track'
friends_names_list = ['O2mctracklabel', 'O2trackcov', 'O2trackextra' ]

ROOT.gROOT.LoadMacro('alice_DataModel.C+')  # compiled form of data definitions

##############
## DO NOT USE CHAINS!! Indexes are relative to file
##############

## Precreate histos to be filled later


## parse the files in filelist
for f in file_list:
    tfile = ROOT.TFile(f)
    if tfile.IsZombie():
        print(f'{f} is zombie')
        continue

    df_list = get_df_list(tfile)
    for df in df_list:
        tree_list_in_df = get_df_trees(tfile, df)
        if not tree_list_found: tree_list = tree_list_in_df.copy() # it will be run only for first file

        tree_track = tfile.Get(f'{df}/{tree_name_track}') 

        if ADD_FRIENDS:
            for frd in friends_names_list:
                tfrd = tfile.Get(f'{df}/{frd}')
                if not tfrd: continue
                if tree_track.GetEntries() == tfrd.GetEntries():
                    tree_track.AddFriend(tfrd)
                else:
                    print(f'Different number of entries for: {frd} ; Not adding')

        if _PRINT_DATA_STRUCTURE:
            table = Table(title = None)
            table.add_column("Chain/Tree name", justify="left")
            table.add_column("Entries", justify="right")
            table.add_column("Branches", justify="left")

            for t in tree_list:
                t = tfile.Get(f'{df}/{t}')
                table.add_row(f'{t.GetName()}',f'{t.GetEntries()}', ' '.join( [f'{br.GetName()}' for br in t.GetListOfBranches()] ))

            console = Console()
            console.print(table)

            # Print friends already added to the main chain
            print(f'\nMain chain have these friends:\n{[fr.GetName().strip() for fr in tree_track.GetListOfFriends()]}\n')
            sys.exit()

        ###########################################
        ##   DATA CRUNCHING
        ###########################################
        # tree_coll = tfile.Get(f'{df}/O2collision')
        # tree_coll.SetBranchStatus("*",0);
        # tree_coll.SetBranchStatus("fIndexBCs",1);
        # tree_coll.SetBranchStatus("fNumContrib",1);
        # tree_coll.Scan("fIndexBCs:fNumContrib   ","","lenmax=5")

        # Get map of ttree entries to CollisionId
        # tree_track.SetBranchStatus("*",0);
        # tree_track.SetBranchStatus("fIndexCollisions",1);
        # entries2col = dict()
        # for entry_idx, e in enumerate(tree_track):
            # dict_add2key(entries2col, getattr(e, 'fIndexCollisions'), entry_idx)


        # Get numpy array and according labels of the columns
        rdf_tracks = ROOT.RDataFrame(tree_track)
        # we can do global filter here for tracks: sign, p_{T,x,y,z}
        npy_tracks = rdf_tracks.AsNumpy()



        #pt_node = df.Define('pt', 'alice_o2::define_pt(fSigned1Pt)')
        #h_pt = pt_node.Histo1D(("pt", "p_{T};p_{T};n_{Tracks}", 150, 0, 150), 'pt')
        #c1 = ROOT.TCanvas("c1", "c1", 1500, 1000)
        #c1.cd()
        #c1.SetLogy()
        #h_pt.Draw()
        #c1.SaveAs("pt.png")

        #chain.Scan("fIndexCollisions:fSigned1Pt","fIndexCollisions >= 0","lenmax=5")


        #pprint(entries2col)



#if not BATCH: input('Please press enter to continue.')

