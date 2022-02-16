//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sat Jan 22 15:34:30 2022 by ROOT version 6.25/99
// from TTree O2fdd/FDD
// found on file: AO2D.root
//////////////////////////////////////////////////////////

#ifndef O2fdd_h
#define O2fdd_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class O2fdd {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           fIndexBCs;
   Float_t         fAmplitudeA[4];
   Float_t         fAmplitudeC[4];
   Float_t         fTimeA;
   Float_t         fTimeC;
   UChar_t         fTriggerMask;

   // List of branches
   TBranch        *b_fIndexBCs;   //!
   TBranch        *b_fAmplitudeA;   //!
   TBranch        *b_fAmplitudeC;   //!
   TBranch        *b_fTimeA;   //!
   TBranch        *b_fTimeC;   //!
   TBranch        *b_fTriggerMask;   //!

   O2fdd(TTree *tree=0);
   virtual ~O2fdd();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef O2fdd_cxx
O2fdd::O2fdd(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("AO2D.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("AO2D.root");
      }
      TDirectory * dir = (TDirectory*)f->Get("AO2D.root:/DF_1390380072509039192");
      dir->GetObject("O2fdd",tree);

   }
   Init(tree);
}

O2fdd::~O2fdd()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t O2fdd::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t O2fdd::LoadTree(Long64_t entry)
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

void O2fdd::Init(TTree *tree)
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
   fChain->SetBranchAddress("fAmplitudeA", fAmplitudeA, &b_fAmplitudeA);
   fChain->SetBranchAddress("fAmplitudeC", fAmplitudeC, &b_fAmplitudeC);
   fChain->SetBranchAddress("fTimeA", &fTimeA, &b_fTimeA);
   fChain->SetBranchAddress("fTimeC", &fTimeC, &b_fTimeC);
   fChain->SetBranchAddress("fTriggerMask", &fTriggerMask, &b_fTriggerMask);
   Notify();
}

Bool_t O2fdd::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void O2fdd::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t O2fdd::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef O2fdd_cxx