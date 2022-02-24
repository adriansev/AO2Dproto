//usr/bin/env -S root.exe -b -q -l -e ".x ${0}" ; exit $?
#include <iostream>
#include <fstream>
#include <algorithm>
#include "TString.h"
#include "load_selectors.C"
#include "ao2d_tools.C"

int gen_ttree_selectors() {
auto cwd = gSystem->GetWorkingDirectory();
TString selector_dir = "o2data_ttree_selector";
gSystem->cd(selector_dir.Data());
TFile tfile("AO2D.root");
if (tfile.IsZombie()) { return 1; }
vector<string> df_list = get_df_list(tfile);
vector<string> tree_list = get_df_trees(tfile, df_list[0]);

/*
tree_list.erase(std::remove_if(tree_list.begin(), tree_list.end(), [](string s){ return (s == "O2track" || s == "O2trackcov" || s == "O2trackextra") ;}), tree_list.end());
std::string o2track_path = df_list[0] + string("/") + string("O2track");
std::string o2trackcov_path = df_list[0] + string("/") + string("O2trackcov");
std::string o2trackextra_path = df_list[0] + string("/") + string("O2trackextra");
TTree* tt_o2track = dynamic_cast<TTree*>(tfile.Get(o2track_path.c_str()));
TTree* tt_o2trackcov = dynamic_cast<TTree*>(tfile.Get(o2trackcov_path.c_str()));
TTree* tt_o2trackextra = dynamic_cast<TTree*>(tfile.Get(o2trackextra_path.c_str()));
tt_o2track->AddFriend(tt_o2trackcov);
tt_o2track->AddFriend(tt_o2trackextra);
tt_o2track->MakeSelector(0, "");
*/

for (auto tname: tree_list) {
    cout << tname << endl;
    std::string ttree_path_track = df_list[0] + string("/") + tname;
    TTree* tt = dynamic_cast<TTree*>(tfile.Get(ttree_path_track.c_str()));
    tt->MakeSelector(0, "");
    }

gSystem->cd(cwd.c_str());
std::vector<TString> file_list = ListFiles(selector_dir, "h");
ofstream selector_includes("ttree_selectors.h");
for (auto& f: file_list) { selector_includes << "#include \"" << f.ReplaceAll("./", "") << "\"" << std::endl ; }
selector_includes.close();

return 0;
}

