//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sat Jan 22 15:34:30 2022 by ROOT version 6.25/99
// from TTree O2trackcov/Barrel tracks Covariance
// found on file: AO2D.root
//////////////////////////////////////////////////////////

#ifndef O2trackcov_h
#define O2trackcov_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class O2trackcov {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Float_t         fSigmaY;
   Float_t         fSigmaZ;
   Float_t         fSigmaSnp;
   Float_t         fSigmaTgl;
   Float_t         fSigma1Pt;
   Char_t          fRhoZY;
   Char_t          fRhoSnpY;
   Char_t          fRhoSnpZ;
   Char_t          fRhoTglY;
   Char_t          fRhoTglZ;
   Char_t          fRhoTglSnp;
   Char_t          fRho1PtY;
   Char_t          fRho1PtZ;
   Char_t          fRho1PtSnp;
   Char_t          fRho1PtTgl;

   // List of branches
   TBranch        *b_fSigmaY;   //!
   TBranch        *b_fSigmaZ;   //!
   TBranch        *b_fSigmaSnp;   //!
   TBranch        *b_fSigmaTgl;   //!
   TBranch        *b_fSigma1Pt;   //!
   TBranch        *b_fRhoZY;   //!
   TBranch        *b_fRhoSnpY;   //!
   TBranch        *b_fRhoSnpZ;   //!
   TBranch        *b_fRhoTglY;   //!
   TBranch        *b_fRhoTglZ;   //!
   TBranch        *b_fRhoTglSnp;   //!
   TBranch        *b_fRho1PtY;   //!
   TBranch        *b_fRho1PtZ;   //!
   TBranch        *b_fRho1PtSnp;   //!
   TBranch        *b_fRho1PtTgl;   //!

   O2trackcov(TTree *tree=0);
   virtual ~O2trackcov();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef O2trackcov_cxx
O2trackcov::O2trackcov(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("AO2D.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("AO2D.root");
      }
      TDirectory * dir = (TDirectory*)f->Get("AO2D.root:/DF_1390380072509039192");
      dir->GetObject("O2trackcov",tree);

   }
   Init(tree);
}

O2trackcov::~O2trackcov()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t O2trackcov::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t O2trackcov::LoadTree(Long64_t entry)
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

void O2trackcov::Init(TTree *tree)
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

   fChain->SetBranchAddress("fSigmaY", &fSigmaY, &b_fSigmaY);
   fChain->SetBranchAddress("fSigmaZ", &fSigmaZ, &b_fSigmaZ);
   fChain->SetBranchAddress("fSigmaSnp", &fSigmaSnp, &b_fSigmaSnp);
   fChain->SetBranchAddress("fSigmaTgl", &fSigmaTgl, &b_fSigmaTgl);
   fChain->SetBranchAddress("fSigma1Pt", &fSigma1Pt, &b_fSigma1Pt);
   fChain->SetBranchAddress("fRhoZY", &fRhoZY, &b_fRhoZY);
   fChain->SetBranchAddress("fRhoSnpY", &fRhoSnpY, &b_fRhoSnpY);
   fChain->SetBranchAddress("fRhoSnpZ", &fRhoSnpZ, &b_fRhoSnpZ);
   fChain->SetBranchAddress("fRhoTglY", &fRhoTglY, &b_fRhoTglY);
   fChain->SetBranchAddress("fRhoTglZ", &fRhoTglZ, &b_fRhoTglZ);
   fChain->SetBranchAddress("fRhoTglSnp", &fRhoTglSnp, &b_fRhoTglSnp);
   fChain->SetBranchAddress("fRho1PtY", &fRho1PtY, &b_fRho1PtY);
   fChain->SetBranchAddress("fRho1PtZ", &fRho1PtZ, &b_fRho1PtZ);
   fChain->SetBranchAddress("fRho1PtSnp", &fRho1PtSnp, &b_fRho1PtSnp);
   fChain->SetBranchAddress("fRho1PtTgl", &fRho1PtTgl, &b_fRho1PtTgl);
   Notify();
}

Bool_t O2trackcov::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void O2trackcov::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t O2trackcov::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef O2trackcov_cxx
