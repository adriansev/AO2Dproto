//usr/bin/env -S root.exe -b -q -l -e ".x ${0}" ; exit $?
#include "../ao2d_process.C"

int ttree_schema_class () {
TFile tfile("AO2D.root");
if (tfile.IsZombie()) { return 1; }
vector<string> df_list = get_df_list(tfile);
vector<string> tree_list = get_df_trees(tfile, df_list[0]);

for (auto tname: tree_list) {
    cout << tname << endl;
    std::string ttree_path_track = df_list[0] + string("/") + tname;
    TTree* tt = dynamic_cast<TTree*>(tfile.Get(ttree_path_track.c_str()));
    tt->MakeClass(0, "");
    }

return 0;
}

