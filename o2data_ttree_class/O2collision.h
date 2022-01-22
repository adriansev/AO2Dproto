//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sat Jan 22 15:34:30 2022 by ROOT version 6.25/99
// from TTree O2collision/Collision tree
// found on file: AO2D.root
//////////////////////////////////////////////////////////

#ifndef O2collision_h
#define O2collision_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class O2collision {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           fIndexBCs;
   Float_t         fPosX;
   Float_t         fPosY;
   Float_t         fPosZ;
   Float_t         fCovXX;
   Float_t         fCovXY;
   Float_t         fCovXZ;
   Float_t         fCovYY;
   Float_t         fCovYZ;
   Float_t         fCovZZ;
   UShort_t        fFlags;
   Float_t         fChi2;
   UShort_t        fNumContrib;
   Float_t         fCollisionTime;
   Float_t         fCollisionTimeRes;

   // List of branches
   TBranch        *b_fIndexBCs;   //!
   TBranch        *b_fPosX;   //!
   TBranch        *b_fPosY;   //!
   TBranch        *b_fPosZ;   //!
   TBranch        *b_fCovXX;   //!
   TBranch        *b_fCovXY;   //!
   TBranch        *b_fCovXZ;   //!
   TBranch        *b_fCovYY;   //!
   TBranch        *b_fCovYZ;   //!
   TBranch        *b_fCovZZ;   //!
   TBranch        *b_fFlags;   //!
   TBranch        *b_fChi2;   //!
   TBranch        *b_fNumContrib;   //!
   TBranch        *b_fCollisionTime;   //!
   TBranch        *b_fCollisionTimeRes;   //!

   O2collision(TTree *tree=0);
   virtual ~O2collision();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef O2collision_cxx
O2collision::O2collision(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("AO2D.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("AO2D.root");
      }
      TDirectory * dir = (TDirectory*)f->Get("AO2D.root:/DF_1390380072509039192");
      dir->GetObject("O2collision",tree);

   }
   Init(tree);
}

O2collision::~O2collision()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t O2collision::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t O2collision::LoadTree(Long64_t entry)
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

void O2collision::Init(TTree *tree)
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
   fChain->SetBranchAddress("fPosX", &fPosX, &b_fPosX);
   fChain->SetBranchAddress("fPosY", &fPosY, &b_fPosY);
   fChain->SetBranchAddress("fPosZ", &fPosZ, &b_fPosZ);
   fChain->SetBranchAddress("fCovXX", &fCovXX, &b_fCovXX);
   fChain->SetBranchAddress("fCovXY", &fCovXY, &b_fCovXY);
   fChain->SetBranchAddress("fCovXZ", &fCovXZ, &b_fCovXZ);
   fChain->SetBranchAddress("fCovYY", &fCovYY, &b_fCovYY);
   fChain->SetBranchAddress("fCovYZ", &fCovYZ, &b_fCovYZ);
   fChain->SetBranchAddress("fCovZZ", &fCovZZ, &b_fCovZZ);
   fChain->SetBranchAddress("fFlags", &fFlags, &b_fFlags);
   fChain->SetBranchAddress("fChi2", &fChi2, &b_fChi2);
   fChain->SetBranchAddress("fNumContrib", &fNumContrib, &b_fNumContrib);
   fChain->SetBranchAddress("fCollisionTime", &fCollisionTime, &b_fCollisionTime);
   fChain->SetBranchAddress("fCollisionTimeRes", &fCollisionTimeRes, &b_fCollisionTimeRes);
   Notify();
}

Bool_t O2collision::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void O2collision::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t O2collision::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef O2collision_cxx
