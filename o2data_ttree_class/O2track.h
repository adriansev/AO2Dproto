//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sat Jan 22 15:34:30 2022 by ROOT version 6.25/99
// from TTree O2track/Barrel tracks Parameters
// found on file: AO2D.root
//////////////////////////////////////////////////////////

#ifndef O2track_h
#define O2track_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class O2track {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           fIndexCollisions;
   UChar_t         fTrackType;
   Float_t         fX;
   Float_t         fAlpha;
   Float_t         fY;
   Float_t         fZ;
   Float_t         fSnp;
   Float_t         fTgl;
   Float_t         fSigned1Pt;

   // List of branches
   TBranch        *b_fIndexCollisions;   //!
   TBranch        *b_fTrackType;   //!
   TBranch        *b_fX;   //!
   TBranch        *b_fAlpha;   //!
   TBranch        *b_fY;   //!
   TBranch        *b_fZ;   //!
   TBranch        *b_fSnp;   //!
   TBranch        *b_fTgl;   //!
   TBranch        *b_fSigned1Pt;   //!

   O2track(TTree *tree=0);
   virtual ~O2track();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef O2track_cxx
O2track::O2track(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("AO2D.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("AO2D.root");
      }
      TDirectory * dir = (TDirectory*)f->Get("AO2D.root:/DF_1390380072509039192");
      dir->GetObject("O2track",tree);

   }
   Init(tree);
}

O2track::~O2track()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t O2track::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t O2track::LoadTree(Long64_t entry)
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

void O2track::Init(TTree *tree)
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

   fChain->SetBranchAddress("fIndexCollisions", &fIndexCollisions, &b_fIndexCollisions);
   fChain->SetBranchAddress("fTrackType", &fTrackType, &b_fTrackType);
   fChain->SetBranchAddress("fX", &fX, &b_fX);
   fChain->SetBranchAddress("fAlpha", &fAlpha, &b_fAlpha);
   fChain->SetBranchAddress("fY", &fY, &b_fY);
   fChain->SetBranchAddress("fZ", &fZ, &b_fZ);
   fChain->SetBranchAddress("fSnp", &fSnp, &b_fSnp);
   fChain->SetBranchAddress("fTgl", &fTgl, &b_fTgl);
   fChain->SetBranchAddress("fSigned1Pt", &fSigned1Pt, &b_fSigned1Pt);
   Notify();
}

Bool_t O2track::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void O2track::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t O2track::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef O2track_cxx
