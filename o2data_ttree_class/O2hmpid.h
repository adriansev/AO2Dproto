//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sat Jan 22 15:34:30 2022 by ROOT version 6.25/99
// from TTree O2hmpid/HMPID info
// found on file: AO2D.root
//////////////////////////////////////////////////////////

#ifndef O2hmpid_h
#define O2hmpid_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class O2hmpid {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           fIndexTracks;
   Float_t         fHMPIDSignal;
   Float_t         fHMPIDDistance;
   Short_t         fHMPIDNPhotons;
   Short_t         fHMPIDQMip;

   // List of branches
   TBranch        *b_fIndexTracks;   //!
   TBranch        *b_fHMPIDSignal;   //!
   TBranch        *b_fHMPIDDistance;   //!
   TBranch        *b_fHMPIDNPhotons;   //!
   TBranch        *b_fHMPIDQMip;   //!

   O2hmpid(TTree *tree=0);
   virtual ~O2hmpid();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef O2hmpid_cxx
O2hmpid::O2hmpid(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("AO2D.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("AO2D.root");
      }
      TDirectory * dir = (TDirectory*)f->Get("AO2D.root:/DF_1390380072509039192");
      dir->GetObject("O2hmpid",tree);

   }
   Init(tree);
}

O2hmpid::~O2hmpid()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t O2hmpid::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t O2hmpid::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void O2hmpid::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("fIndexTracks", &fIndexTracks, &b_fIndexTracks);
   fChain->SetBranchAddress("fHMPIDSignal", &fHMPIDSignal, &b_fHMPIDSignal);
   fChain->SetBranchAddress("fHMPIDDistance", &fHMPIDDistance, &b_fHMPIDDistance);
   fChain->SetBranchAddress("fHMPIDNPhotons", &fHMPIDNPhotons, &b_fHMPIDNPhotons);
   fChain->SetBranchAddress("fHMPIDQMip", &fHMPIDQMip, &b_fHMPIDQMip);
   Notify();
}

Bool_t O2hmpid::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void O2hmpid::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t O2hmpid::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef O2hmpid_cxx
