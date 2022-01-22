//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sat Jan 22 15:34:30 2022 by ROOT version 6.25/99
// from TTree O2trackextra/Barrel tracks Extra
// found on file: AO2D.root
//////////////////////////////////////////////////////////

#ifndef O2trackextra_h
#define O2trackextra_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class O2trackextra {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Float_t         fTPCInnerParam;
   UInt_t          fFlags;
   UChar_t         fITSClusterMap;
   UChar_t         fTPCNClsFindable;
   Char_t          fTPCNClsFindableMinusFound;
   Char_t          fTPCNClsFindableMinusCrossedRows;
   UChar_t         fTPCNClsShared;
   UChar_t         fTRDPattern;
   Float_t         fITSChi2NCl;
   Float_t         fTPCChi2NCl;
   Float_t         fTRDChi2;
   Float_t         fTOFChi2;
   Float_t         fTPCSignal;
   Float_t         fTRDSignal;
   Float_t         fLength;
   Float_t         fTOFExpMom;
   Float_t         fTrackEtaEMCAL;
   Float_t         fTrackPhiEMCAL;
   Float_t         fTrackTime;
   Float_t         fTrackTimeRes;

   // List of branches
   TBranch        *b_fTPCInnerParam;   //!
   TBranch        *b_fFlags;   //!
   TBranch        *b_fITSClusterMap;   //!
   TBranch        *b_fTPCNClsFindable;   //!
   TBranch        *b_fTPCNClsFindableMinusFound;   //!
   TBranch        *b_fTPCNClsFindableMinusCrossedRows;   //!
   TBranch        *b_fTPCNClsShared;   //!
   TBranch        *b_fTRDPattern;   //!
   TBranch        *b_fITSChi2NCl;   //!
   TBranch        *b_fTPCChi2NCl;   //!
   TBranch        *b_fTRDChi2;   //!
   TBranch        *b_fTOFChi2;   //!
   TBranch        *b_fTPCSignal;   //!
   TBranch        *b_fTRDSignal;   //!
   TBranch        *b_fLength;   //!
   TBranch        *b_fTOFExpMom;   //!
   TBranch        *b_fTrackEtaEMCAL;   //!
   TBranch        *b_fTrackPhiEMCAL;   //!
   TBranch        *b_fTrackTime;   //!
   TBranch        *b_fTrackTimeRes;   //!

   O2trackextra(TTree *tree=0);
   virtual ~O2trackextra();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef O2trackextra_cxx
O2trackextra::O2trackextra(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("AO2D.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("AO2D.root");
      }
      TDirectory * dir = (TDirectory*)f->Get("AO2D.root:/DF_1390380072509039192");
      dir->GetObject("O2trackextra",tree);

   }
   Init(tree);
}

O2trackextra::~O2trackextra()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t O2trackextra::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t O2trackextra::LoadTree(Long64_t entry)
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

void O2trackextra::Init(TTree *tree)
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

   fChain->SetBranchAddress("fTPCInnerParam", &fTPCInnerParam, &b_fTPCInnerParam);
   fChain->SetBranchAddress("fFlags", &fFlags, &b_fFlags);
   fChain->SetBranchAddress("fITSClusterMap", &fITSClusterMap, &b_fITSClusterMap);
   fChain->SetBranchAddress("fTPCNClsFindable", &fTPCNClsFindable, &b_fTPCNClsFindable);
   fChain->SetBranchAddress("fTPCNClsFindableMinusFound", &fTPCNClsFindableMinusFound, &b_fTPCNClsFindableMinusFound);
   fChain->SetBranchAddress("fTPCNClsFindableMinusCrossedRows", &fTPCNClsFindableMinusCrossedRows, &b_fTPCNClsFindableMinusCrossedRows);
   fChain->SetBranchAddress("fTPCNClsShared", &fTPCNClsShared, &b_fTPCNClsShared);
   fChain->SetBranchAddress("fTRDPattern", &fTRDPattern, &b_fTRDPattern);
   fChain->SetBranchAddress("fITSChi2NCl", &fITSChi2NCl, &b_fITSChi2NCl);
   fChain->SetBranchAddress("fTPCChi2NCl", &fTPCChi2NCl, &b_fTPCChi2NCl);
   fChain->SetBranchAddress("fTRDChi2", &fTRDChi2, &b_fTRDChi2);
   fChain->SetBranchAddress("fTOFChi2", &fTOFChi2, &b_fTOFChi2);
   fChain->SetBranchAddress("fTPCSignal", &fTPCSignal, &b_fTPCSignal);
   fChain->SetBranchAddress("fTRDSignal", &fTRDSignal, &b_fTRDSignal);
   fChain->SetBranchAddress("fLength", &fLength, &b_fLength);
   fChain->SetBranchAddress("fTOFExpMom", &fTOFExpMom, &b_fTOFExpMom);
   fChain->SetBranchAddress("fTrackEtaEMCAL", &fTrackEtaEMCAL, &b_fTrackEtaEMCAL);
   fChain->SetBranchAddress("fTrackPhiEMCAL", &fTrackPhiEMCAL, &b_fTrackPhiEMCAL);
   fChain->SetBranchAddress("fTrackTime", &fTrackTime, &b_fTrackTime);
   fChain->SetBranchAddress("fTrackTimeRes", &fTrackTimeRes, &b_fTrackTimeRes);
   Notify();
}

Bool_t O2trackextra::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void O2trackextra::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t O2trackextra::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef O2trackextra_cxx
