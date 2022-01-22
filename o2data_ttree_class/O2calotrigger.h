//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sat Jan 22 15:34:30 2022 by ROOT version 6.25/99
// from TTree O2calotrigger/Calorimeter triggers
// found on file: AO2D.root
//////////////////////////////////////////////////////////

#ifndef O2calotrigger_h
#define O2calotrigger_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class O2calotrigger {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           fIndexBCs;
   Short_t         fFastOrAbsID;
   Short_t         fLnAmplitude;
   Int_t           fTriggerBits;
   Char_t          fCaloType;

   // List of branches
   TBranch        *b_fIndexBCs;   //!
   TBranch        *b_fFastOrAbsID;   //!
   TBranch        *b_fLnAmplitude;   //!
   TBranch        *b_fTriggerBits;   //!
   TBranch        *b_fCaloType;   //!

   O2calotrigger(TTree *tree=0);
   virtual ~O2calotrigger();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef O2calotrigger_cxx
O2calotrigger::O2calotrigger(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("AO2D.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("AO2D.root");
      }
      TDirectory * dir = (TDirectory*)f->Get("AO2D.root:/DF_1390380072509039192");
      dir->GetObject("O2calotrigger",tree);

   }
   Init(tree);
}

O2calotrigger::~O2calotrigger()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t O2calotrigger::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t O2calotrigger::LoadTree(Long64_t entry)
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

void O2calotrigger::Init(TTree *tree)
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

   fChain->SetBranchAddress("fIndexBCs", &fIndexBCs, &b_fIndexBCs);
   fChain->SetBranchAddress("fFastOrAbsID", &fFastOrAbsID, &b_fFastOrAbsID);
   fChain->SetBranchAddress("fLnAmplitude", &fLnAmplitude, &b_fLnAmplitude);
   fChain->SetBranchAddress("fTriggerBits", &fTriggerBits, &b_fTriggerBits);
   fChain->SetBranchAddress("fCaloType", &fCaloType, &b_fCaloType);
   Notify();
}

Bool_t O2calotrigger::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void O2calotrigger::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t O2calotrigger::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef O2calotrigger_cxx
