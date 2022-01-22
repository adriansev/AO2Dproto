//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sat Jan 22 15:34:30 2022 by ROOT version 6.25/99
// from TTree O2run2bcinfo/Run 2 BC Info
// found on file: AO2D.root
//////////////////////////////////////////////////////////

#ifndef O2run2bcinfo_h
#define O2run2bcinfo_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class O2run2bcinfo {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   UInt_t          fEventCuts;
   ULong64_t       fTriggerMaskNext50;
   UInt_t          fL0TriggerInputMask;
   UShort_t        fSPDClustersL0;
   UShort_t        fSPDClustersL1;
   UShort_t        fSPDFiredChipsL0;
   UShort_t        fSPDFiredChipsL1;
   UShort_t        fSPDFiredFastOrL0;
   UShort_t        fSPDFiredFastOrL1;
   UShort_t        fV0TriggerChargeA;
   UShort_t        fV0TriggerChargeC;

   // List of branches
   TBranch        *b_fEventCuts;   //!
   TBranch        *b_fTriggerMaskNext50;   //!
   TBranch        *b_fL0TriggerInputMask;   //!
   TBranch        *b_fSPDClustersL0;   //!
   TBranch        *b_fSPDClustersL1;   //!
   TBranch        *b_fSPDFiredChipsL0;   //!
   TBranch        *b_fSPDFiredChipsL1;   //!
   TBranch        *b_fSPDFiredFastOrL0;   //!
   TBranch        *b_fSPDFiredFastOrL1;   //!
   TBranch        *b_fV0TriggerChargeA;   //!
   TBranch        *b_fV0TriggerChargeC;   //!

   O2run2bcinfo(TTree *tree=0);
   virtual ~O2run2bcinfo();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef O2run2bcinfo_cxx
O2run2bcinfo::O2run2bcinfo(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("AO2D.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("AO2D.root");
      }
      TDirectory * dir = (TDirectory*)f->Get("AO2D.root:/DF_1390380072509039192");
      dir->GetObject("O2run2bcinfo",tree);

   }
   Init(tree);
}

O2run2bcinfo::~O2run2bcinfo()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t O2run2bcinfo::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t O2run2bcinfo::LoadTree(Long64_t entry)
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

void O2run2bcinfo::Init(TTree *tree)
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

   fChain->SetBranchAddress("fEventCuts", &fEventCuts, &b_fEventCuts);
   fChain->SetBranchAddress("fTriggerMaskNext50", &fTriggerMaskNext50, &b_fTriggerMaskNext50);
   fChain->SetBranchAddress("fL0TriggerInputMask", &fL0TriggerInputMask, &b_fL0TriggerInputMask);
   fChain->SetBranchAddress("fSPDClustersL0", &fSPDClustersL0, &b_fSPDClustersL0);
   fChain->SetBranchAddress("fSPDClustersL1", &fSPDClustersL1, &b_fSPDClustersL1);
   fChain->SetBranchAddress("fSPDFiredChipsL0", &fSPDFiredChipsL0, &b_fSPDFiredChipsL0);
   fChain->SetBranchAddress("fSPDFiredChipsL1", &fSPDFiredChipsL1, &b_fSPDFiredChipsL1);
   fChain->SetBranchAddress("fSPDFiredFastOrL0", &fSPDFiredFastOrL0, &b_fSPDFiredFastOrL0);
   fChain->SetBranchAddress("fSPDFiredFastOrL1", &fSPDFiredFastOrL1, &b_fSPDFiredFastOrL1);
   fChain->SetBranchAddress("fV0TriggerChargeA", &fV0TriggerChargeA, &b_fV0TriggerChargeA);
   fChain->SetBranchAddress("fV0TriggerChargeC", &fV0TriggerChargeC, &b_fV0TriggerChargeC);
   Notify();
}

Bool_t O2run2bcinfo::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void O2run2bcinfo::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t O2run2bcinfo::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef O2run2bcinfo_cxx
