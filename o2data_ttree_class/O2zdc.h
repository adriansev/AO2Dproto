//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sat Jan 22 15:34:30 2022 by ROOT version 6.25/99
// from TTree O2zdc/ZDC
// found on file: AO2D.root
//////////////////////////////////////////////////////////

#ifndef O2zdc_h
#define O2zdc_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class O2zdc {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           fIndexBCs;
   Float_t         fEnergyZEM1;
   Float_t         fEnergyZEM2;
   Float_t         fEnergyCommonZNA;
   Float_t         fEnergyCommonZNC;
   Float_t         fEnergyCommonZPA;
   Float_t         fEnergyCommonZPC;
   Float_t         fEnergySectorZNA[4];
   Float_t         fEnergySectorZNC[4];
   Float_t         fEnergySectorZPA[4];
   Float_t         fEnergySectorZPC[4];
   Float_t         fTimeZEM1;
   Float_t         fTimeZEM2;
   Float_t         fTimeZNA;
   Float_t         fTimeZNC;
   Float_t         fTimeZPA;
   Float_t         fTimeZPC;

   // List of branches
   TBranch        *b_fIndexBCs;   //!
   TBranch        *b_fEnergyZEM1;   //!
   TBranch        *b_fEnergyZEM2;   //!
   TBranch        *b_fEnergyCommonZNA;   //!
   TBranch        *b_fEnergyCommonZNC;   //!
   TBranch        *b_fEnergyCommonZPA;   //!
   TBranch        *b_fEnergyCommonZPC;   //!
   TBranch        *b_fEnergySectorZNA;   //!
   TBranch        *b_fEnergySectorZNC;   //!
   TBranch        *b_fEnergySectorZPA;   //!
   TBranch        *b_fEnergySectorZPC;   //!
   TBranch        *b_fTimeZEM1;   //!
   TBranch        *b_fTimeZEM2;   //!
   TBranch        *b_fTimeZNA;   //!
   TBranch        *b_fTimeZNC;   //!
   TBranch        *b_fTimeZPA;   //!
   TBranch        *b_fTimeZPC;   //!

   O2zdc(TTree *tree=0);
   virtual ~O2zdc();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef O2zdc_cxx
O2zdc::O2zdc(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("AO2D.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("AO2D.root");
      }
      TDirectory * dir = (TDirectory*)f->Get("AO2D.root:/DF_1390380072509039192");
      dir->GetObject("O2zdc",tree);

   }
   Init(tree);
}

O2zdc::~O2zdc()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t O2zdc::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t O2zdc::LoadTree(Long64_t entry)
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

void O2zdc::Init(TTree *tree)
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
   fChain->SetBranchAddress("fEnergyZEM1", &fEnergyZEM1, &b_fEnergyZEM1);
   fChain->SetBranchAddress("fEnergyZEM2", &fEnergyZEM2, &b_fEnergyZEM2);
   fChain->SetBranchAddress("fEnergyCommonZNA", &fEnergyCommonZNA, &b_fEnergyCommonZNA);
   fChain->SetBranchAddress("fEnergyCommonZNC", &fEnergyCommonZNC, &b_fEnergyCommonZNC);
   fChain->SetBranchAddress("fEnergyCommonZPA", &fEnergyCommonZPA, &b_fEnergyCommonZPA);
   fChain->SetBranchAddress("fEnergyCommonZPC", &fEnergyCommonZPC, &b_fEnergyCommonZPC);
   fChain->SetBranchAddress("fEnergySectorZNA", fEnergySectorZNA, &b_fEnergySectorZNA);
   fChain->SetBranchAddress("fEnergySectorZNC", fEnergySectorZNC, &b_fEnergySectorZNC);
   fChain->SetBranchAddress("fEnergySectorZPA", fEnergySectorZPA, &b_fEnergySectorZPA);
   fChain->SetBranchAddress("fEnergySectorZPC", fEnergySectorZPC, &b_fEnergySectorZPC);
   fChain->SetBranchAddress("fTimeZEM1", &fTimeZEM1, &b_fTimeZEM1);
   fChain->SetBranchAddress("fTimeZEM2", &fTimeZEM2, &b_fTimeZEM2);
   fChain->SetBranchAddress("fTimeZNA", &fTimeZNA, &b_fTimeZNA);
   fChain->SetBranchAddress("fTimeZNC", &fTimeZNC, &b_fTimeZNC);
   fChain->SetBranchAddress("fTimeZPA", &fTimeZPA, &b_fTimeZPA);
   fChain->SetBranchAddress("fTimeZPC", &fTimeZPC, &b_fTimeZPC);
   Notify();
}

Bool_t O2zdc::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void O2zdc::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t O2zdc::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef O2zdc_cxx
