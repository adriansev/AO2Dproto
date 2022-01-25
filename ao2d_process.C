//usr/bin/env -S root.exe -b -q -l -e ".x ${0}" ; exit $?
#include <algorithm>
#include <string>
#include <unordered_map>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <cctype>
#include <cmath>
#include <string_view>

#include <TROOT.h>
#include <TFile.h>
#include <TKey.h>
#include <TTree.h>
#include <ROOT/StringUtils.hxx>

#include "o2data_model/DataTypes.h"
#include "alice_DataModel.C"

using std::cout;
using std::endl;
using std::string;
using std::vector;

typedef std::vector<long long> VecInt;
typedef std::unordered_map<int, VecInt> CollEv;
typedef std::unordered_map<std::string, TTree*> TTreeCol;

bool str_is_space (const std::string& input);
std::vector<std::string> str_split(const std::string& input, char delimiter);
std::vector<std::string> parse_file (std::string file);
std::vector<std::string> get_df_list (const TFile& f);
std::vector<std::string> get_df_trees (TFile& f, const std::string& df_name);
TTree* GetTree(TFile& tfile, std::string directory, std::string tree_name);


//###############################################
int ao2d_process (/*int argc, char* argv[]*/) {
// vector<string> args(argv + 1, argv + argc);    // put all args in a vector // TODO process args
// gROOT->LoadMacro("alice_DataModel.C+");

string input_file = "file_list";
vector<string> input_file_list = parse_file(input_file);

for (auto f: input_file_list) {  // parsing files in list
    TFile tfile(f.c_str());
    if (tfile.IsZombie()) { continue; }
    
    vector<string> df_list = get_df_list(tfile);
    for (auto d: df_list) {  // parsing df_ directories in tfile
        vector<string> tree_list = get_df_trees(tfile, d);
        TTreeCol tree_map;
        for (auto t: tree_list){ tree_map[t] = GetTree(tfile, d, t); }

        TTree* tracks = tree_map["O2track"];

        tracks->AddFriend(tree_map["O2trackextra"]);
        tracks->AddFriend(tree_map["O2trackcov"]);
        for (const auto&& obj: *tracks->GetListOfFriends()) { cout << "Friend name : " << obj->GetName() << endl; }
        
        // just for grouping of tracks in collisions events
        CollEv coll_list;  // list of index collision groups
        tracks->SetBranchStatus("*",0);
        tracks->SetBranchStatus("fIndexCollisions",1);
        Int_t fIndexCollisions;
        tracks->SetBranchAddress("fIndexCollisions",&fIndexCollisions);
        for (Long64_t i = 0; i < tracks->GetEntries(); ++i) {
            tracks->GetEntry(i);
            coll_list[fIndexCollisions].push_back(i);
            }

        //######################
        // Now we can start to parse collisions
        //######################
        tracks->SetBranchStatus("*",1); // enable all branches in O2track
        UChar_t fTrackType;
        Float_t fX, fY, fZ, fAlpha, fSnp, fTgl, fSigned1Pt;
        tracks->SetBranchAddress("fTrackType",&fTrackType); 
        tracks->SetBranchAddress("fX",&fX); 
        tracks->SetBranchAddress("fY",&fY); 
        tracks->SetBranchAddress("fZ",&fZ); 
        tracks->SetBranchAddress("fAlpha",&fAlpha); 
        tracks->SetBranchAddress("fSnp",&fSnp); 
        tracks->SetBranchAddress("fTgl",&fTgl); 
        tracks->SetBranchAddress("fSigned1Pt",&fSigned1Pt); 
        for (auto i: coll_list) {  // lets parse collisions
            std::cout << "fIndexCollisions:[" << i.first << "]" << '\n';
            Float_t pt_sum = 0;
            Int_t tracks_nr = 0;
            for (long long ent: i.second) {
                tracks->GetEntry(ent);
                int track_type = static_cast<int>(fTrackType);
                if ( !((track_type == o2::aod::track::Track) || (track_type == o2::aod::track::Run2Track)) ) { continue; };  // if not Track or Run2Track then skip
                    
                tracks_nr++;
                pt_sum += o2alice::pt(fSigned1Pt);
                
                }  // end of loop over tracks in collision

            if (tracks_nr == 0) {
                cout << "No tracks in this collision" << endl;
                continue;
                }
                
            Float_t pt_sum_avrg = pt_sum/tracks_nr ;
            if (isnan(pt_sum_avrg)) {
                cout << "ptsum = " << pt_sum << " ; tracks_nr =  " << tracks_nr << endl;
                }
            else {
                std::cout << "<p_{T}> sum in collision >" << i.first << "< is = " << pt_sum_avrg << std::endl;
                }
            
            }  // end of loop over collisions
        }  // end of loop over DF_ directories
    }  // end of loop over file_list

return 0;
}

//##############################################
TTree* GetTree(TFile& tfile, std::string directory, std::string tree_name) {
    string ttree_path_track = directory + string("/") + tree_name;
    TTree* ttree = dynamic_cast<TTree*>(tfile.Get(ttree_path_track.c_str()));
    return ttree;
}

//##############################################
std::vector<std::string> get_df_list (const TFile& f) {
    std::vector<std::string> list;
    if (f.IsZombie()) { return list; }
    for (auto k: *f.GetListOfKeys()) {
        std::string key_class_name = dynamic_cast<TKey*>(k)->GetClassName();
        if ( key_class_name.rfind("TDirectory", 0) != 0 ) { continue; }
        list.push_back(std::string(k->GetName()));
        }
    return list;
    }

//##############################################
std::vector<std::string> get_df_trees (TFile& f, const std::string& df_name) {
    std::vector<std::string> list;
    if (f.IsZombie()) { return list; }
    TDirectory* tdir = f.GetDirectory(df_name.c_str());
    for (auto k: *tdir->GetListOfKeys()) {
        std::string key_class_name = dynamic_cast<TKey*>(k)->GetClassName();
        if ( key_class_name.compare("TTree") != 0 ) { continue; }
        list.push_back(std::string(k->GetName()));
        }
    return list;
    }

//##############################################
bool str_is_space (const std::string& input) {
    for (auto x: input) { if (!std::isspace(static_cast<unsigned char>(x))) { return false; } }
    return true;
    }

//##############################################
std::vector<std::string> str_split(const std::string& input, char delimiter) {
   std::vector<std::string> part_list;
   std::string part;
   std::istringstream part_stream(input);
   while (std::getline(part_stream, part, delimiter)) { if (!str_is_space(part)) {part_list.push_back(part);} }
   return part_list;
   }

//##############################################
std::vector<std::string> parse_file (std::string file) {
    std::vector<std::string> input_file_list;
    std::fstream infile;
    infile.open(file, std::ios::in);

    if (infile.is_open()) {
        infile.seekg(0);
        std::string line;
        while( std::getline(infile, line) ) {
            std::string_view line_sv = line;
            for (const auto& p: ROOT::Split(line_sv, " ", true)) { if (p[0] != '#') { input_file_list.push_back(p);} }
            }
        }
    return input_file_list;
}
