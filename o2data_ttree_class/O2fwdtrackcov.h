//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sat Jan 22 15:34:30 2022 by ROOT version 6.25/99
// from TTree O2fwdtrackcov/Forward tracks Covariances
// found on file: AO2D.root
//////////////////////////////////////////////////////////

#ifndef O2fwdtrackcov_h
#define O2fwdtrackcov_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class O2fwdtrackcov {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Float_t         fSigmaX;
   Float_t         fSigmaY;
   Float_t         fSigmaPhi;
   Float_t         fSigmaTgl;
   Float_t         fSigma1Pt;
   Char_t          fRhoXY;
   Char_t          fRhoPhiX;
   Char_t          fRhoPhiY;
   Char_t          fRhoTglX;
   Char_t          fRhoTglY;
   Char_t          fRhoTglPhi;
   Char_t          fRho1PtX;
   Char_t          fRho1PtY;
   Char_t          fRho1PtPhi;
   Char_t          fRho1PtTgl;

   // List of branches
   TBranch        *b_fSigmaX;   //!
   TBranch        *b_fSigmaY;   //!
   TBranch        *b_fSigmaPhi;   //!
   TBranch        *b_fSigmaTgl;   //!
   TBranch        *b_fSigma1Pt;   //!
   TBranch        *b_fRhoXY;   //!
   TBranch        *b_fRhoPhiX;   //!
   TBranch        *b_fRhoPhiY;   //!
   TBranch        *b_fRhoTglX;   //!
   TBranch        *b_fRhoTglY;   //!
   TBranch        *b_fRhoTglPhi;   //!
   TBranch        *b_fRho1PtX;   //!
   TBranch        *b_fRho1PtY;   //!
   TBranch        *b_fRho1PtPhi;   //!
   TBranch        *b_fRho1PtTgl;   //!

   O2fwdtrackcov(TTree *tree=0);
   virtual ~O2fwdtrackcov();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef O2fwdtrackcov_cxx
O2fwdtrackcov::O2fwdtrackcov(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("AO2D.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("AO2D.root");
      }
      TDirectory * dir = (TDirectory*)f->Get("AO2D.root:/DF_1390380072509039192");
      dir->GetObject("O2fwdtrackcov",tree);

   }
   Init(tree);
}

O2fwdtrackcov::~O2fwdtrackcov()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t O2fwdtrackcov::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t O2fwdtrackcov::LoadTree(Long64_t entry)
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

void O2fwdtrackcov::Init(TTree *tree)
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

   fChain->SetBranchAddress("fSigmaX", &fSigmaX, &b_fSigmaX);
   fChain->SetBranchAddress("fSigmaY", &fSigmaY, &b_fSigmaY);
   fChain->SetBranchAddress("fSigmaPhi", &fSigmaPhi, &b_fSigmaPhi);
   fChain->SetBranchAddress("fSigmaTgl", &fSigmaTgl, &b_fSigmaTgl);
   fChain->SetBranchAddress("fSigma1Pt", &fSigma1Pt, &b_fSigma1Pt);
   fChain->SetBranchAddress("fRhoXY", &fRhoXY, &b_fRhoXY);
   fChain->SetBranchAddress("fRhoPhiX", &fRhoPhiX, &b_fRhoPhiX);
   fChain->SetBranchAddress("fRhoPhiY", &fRhoPhiY, &b_fRhoPhiY);
   fChain->SetBranchAddress("fRhoTglX", &fRhoTglX, &b_fRhoTglX);
   fChain->SetBranchAddress("fRhoTglY", &fRhoTglY, &b_fRhoTglY);
   fChain->SetBranchAddress("fRhoTglPhi", &fRhoTglPhi, &b_fRhoTglPhi);
   fChain->SetBranchAddress("fRho1PtX", &fRho1PtX, &b_fRho1PtX);
   fChain->SetBranchAddress("fRho1PtY", &fRho1PtY, &b_fRho1PtY);
   fChain->SetBranchAddress("fRho1PtPhi", &fRho1PtPhi, &b_fRho1PtPhi);
   fChain->SetBranchAddress("fRho1PtTgl", &fRho1PtTgl, &b_fRho1PtTgl);
   Notify();
}

Bool_t O2fwdtrackcov::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void O2fwdtrackcov::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t O2fwdtrackcov::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef O2fwdtrackcov_cxx
