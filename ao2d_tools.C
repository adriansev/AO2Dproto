//usr/bin/env -S root.exe -b -q -l -e ".x ${0}" ; exit $?
#include <algorithm>
#include <unordered_map>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <cctype>
#include <cmath>
#include <string>
#include <utility>
#include <string_view>

#include <TROOT.h>
#include <TSystem.h>
#include <TFile.h>
#include <TKey.h>
#include <TTree.h>
#include <ROOT/StringUtils.hxx>

std::vector<std::string> parse_file (std::string file);
std::vector<std::string> get_df_list (const TFile& f);

std::vector< std::pair<std::string,std::string> > GetDFlist(std::string input) {
    std::vector< std::pair<std::string,std::string> > df_locations;
    std::vector<std::string> input_file_list = parse_file(input);
    for (auto f: input_file_list) {  // parsing files in list
        TFile tfile(f.c_str());
        if (tfile.IsZombie()) { continue; }
        std::vector<std::string> df_list = get_df_list(tfile);
        for (auto df: df_list) { df_locations.push_back( std::make_pair(f, df) ); }
        }
    return df_locations;
    }



//##############################################
TTree* GetTree(TFile& tfile, std::string directory, std::string tree_name) {
    std::string ttree_path_track = directory + std::string("/") + tree_name;
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
    std::fstream infile(file, std::ios::in);
    if (infile.is_open()) {
        std::string line;
        while( std::getline(infile, line) ) {
            std::string_view line_sv {line};
            for (const auto& p: ROOT::Split(line_sv, " ", true)) {
                int valid_chars_in_line = 0;  // check for whitespace line
                for (auto& c: p) { if (!std::isspace(static_cast<unsigned char>(c))) { valid_chars_in_line++; } }
                if (valid_chars_in_line == 0) continue;
                if (p[0] != '#') { input_file_list.push_back(p);} }
                }
        }
    return input_file_list;
}

