//usr/bin/env -S root.exe -b -q -l -e ".x ${0}" ; exit $?
#include "TString.h"

std::vector<TString> ListFiles(const TString& path, const TString& fileExt);

int load_selectors() {
std::vector<TString> file_list = ListFiles("o2data_ttree_selector", "C");
for (const auto& f: file_list) { gROOT->LoadMacro(f + "+"); }

return 0;
}

std::vector<TString> ListFiles(const TString& path, const TString& fileExt = "") {
std::vector<TString> file_list;
void* dirp = gSystem->OpenDirectory(path.Data());
if (!dirp) { return file_list; }
TString ext;
if (fileExt.Length() != 0) { ext = "." + fileExt; }

const Char_t* file = 0;
while((file = gSystem->GetDirEntry(dirp))) {
    TString file_str {file};
    if (!file_str.Length() || file_str.EqualTo(".") || file_str.EqualTo("..")) { continue; }
    Long_t id = 0, flags = 0, modtime = 0; Long64_t size = 0;
    TString fullPath = path + '/' + file_str;
    gSystem->GetPathInfo(fullPath.Data(), &id, &size, &flags, &modtime);
    if (2 & flags) { continue; } // is directory
    if ((ext.Length() == 0) || fullPath.EndsWith(ext)) { file_list.push_back(fullPath); }
    }

return file_list;
}
