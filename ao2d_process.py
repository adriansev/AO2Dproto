#!/usr/bin/env python3

import os
import sys
from rich.pretty import pprint
import fileinput as fi
import math
import time

try:
    import ROOT
except Exception:
    print("This script requires the python module of ROOT", file=sys.stderr, flush = True)
    sys.exit(1)

#ROOT.EnableImplicitMT()

_DEBUG = False

file_list = []
with fi.input(files=['file_list']) as f:
    for line in f: file_list.extend(line.strip().split())

file_list = [ f for f in file_list if not (f.startswith('#') and f)]

MAIN_TREE = "O2track"
tree_list = []  # list of all trees find in a DF_ directory

chain = ROOT.TChain(MAIN_TREE)

tree_list_filled = False
for f in file_list:
    try:
        tfile = ROOT.TFile(f)
    except Exception:
        continue
    for tdir in tfile.GetListOfKeys():  # get the directory(ies)
        if not tdir.IsFolder(): continue
        tree_name = f'{f}?query#{tdir.GetName()}/{MAIN_TREE}'  # https://root.cern.ch/doc/master/classTChain.html#a4d491db32262125e6cb77a8f7a6bfd93
        if _DEBUG: print(tree_name)
        chain.AddFile(tree_name)

        for t in tfile.Get(tdir.GetName()).GetListOfKeys():  # get the name of the other trees from the same TDir
            if t.GetClassName() != 'TTree': continue
            if not tree_list_filled: tree_list.append(t.GetName())
        tree_list_filled = True

if MAIN_TREE in tree_list: tree_list.remove(MAIN_TREE)  # remove the tree that we used for the main chain

if _DEBUG: print("\n\n\n")

friend_chain_list = []  # keep a list of chains to be added as friends

# create friends chains
for t_name in tree_list:
    friend_chain = ROOT.TChain()
    for f in file_list:
        try:
            tfile = ROOT.TFile(f)
        except Exception:
            continue
        for tdir in tfile.GetListOfKeys():
            if not tdir.IsFolder(): continue
            friend_tree_name = f'{f}?query#{tdir.GetName()}/{t_name}'
            if _DEBUG: print(friend_tree_name)
            friend_chain.Add(friend_tree_name)
    #friend_chain.Print("*")
    friend_chain_list.append(friend_chain)
    ##chain.AddFriend(friend_chain)

for fc in friend_chain_list:
    # fc.Print("*")  # VALID OUTPUT
    chain.AddFriend(fc)

#chain.Print("all")
#chain.Print()
#chain.Scan("*")

for friend in chain.GetListOfFriends():
    name = friend.GetName().strip()
    if name: print(name)

sys.exit()

df = ROOT.RDataFrame(chain);

##https://github.com/AliceO2Group/AliceO2/blob/dev/Common/MathUtils/include/MathUtils/Utils.h
##https://github.com/AliceO2Group/AliceO2/blob/dev/Framework/Core/include/Framework/AnalysisDataModel.h#L115
def get_pt(x): return fabs(1./float(x) )

#filter_data = df.Define("pt", "abs(1./fSigned1Pt)")

h_pt = df.Histo1D("fSigned1Pt") ## , "Title pt;p_{T};Tracks", 200, 0, 200)


c1 = ROOT.TCanvas("c1", "c1", 600, 600)

h_pt.Draw()

time.sleep(30)














