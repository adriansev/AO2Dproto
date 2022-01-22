//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sat Jan 22 15:34:30 2022 by ROOT version 6.25/99
// from TTree O2fwdtrack/Forward tracks Parameters
// found on file: AO2D.root
//////////////////////////////////////////////////////////

#ifndef O2fwdtrack_h
#define O2fwdtrack_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class O2fwdtrack {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           fIndexCollisions;
   Int_t           fTrackType;
   Float_t         fX;
   Float_t         fY;
   Float_t         fZ;
   Float_t         fPhi;
   Float_t         fTgl;
   Float_t         fSigned1Pt;
   Int_t           fNClusters;
   Float_t         fPDca;
   Float_t         fRAtAbsorberEnd;
   Float_t         fChi2;
   Float_t         fChi2MatchMCHMID;
   Float_t         fChi2MatchMCHMFT;
   Float_t         fMatchScoreMCHMFT;
   Float_t         fTrackTime;
   Float_t         fTrackTimeRes;
   Int_t           fIndexMFTTracks;
   Int_t           fIndexFwdTracks_MatchMCHTrack;
   UShort_t        fMCHBitMap;
   UShort_t        fMIDBitMap;
   UInt_t          fMIDBoards;

   // List of branches
   TBranch        *b_fIndexCollisions;   //!
   TBranch        *b_fTrackType;   //!
   TBranch        *b_fX;   //!
   TBranch        *b_fY;   //!
   TBranch        *b_fZ;   //!
   TBranch        *b_fPhi;   //!
   TBranch        *b_fTgl;   //!
   TBranch        *b_fSigned1Pt;   //!
   TBranch        *b_fNClusters;   //!
   TBranch        *b_fPDca;   //!
   TBranch        *b_fRAtAbsorberEnd;   //!
   TBranch        *b_fChi2;   //!
   TBranch        *b_fChi2MatchMCHMID;   //!
   TBranch        *b_fChi2MatchMCHMFT;   //!
   TBranch        *b_fMatchScoreMCHMFT;   //!
   TBranch        *b_fTrackTime;   //!
   TBranch        *b_fTrackTimeRes;   //!
   TBranch        *b_fIndexMFTTracks;   //!
   TBranch        *b_fIndexFwdTracks_MatchMCHTrack;   //!
   TBranch        *b_fMCHBitMap;   //!
   TBranch        *b_fMIDBitMap;   //!
   TBranch        *b_fMIDBoards;   //!

   O2fwdtrack(TTree *tree=0);
   virtual ~O2fwdtrack();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef O2fwdtrack_cxx
O2fwdtrack::O2fwdtrack(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("AO2D.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("AO2D.root");
      }
      TDirectory * dir = (TDirectory*)f->Get("AO2D.root:/DF_1390380072509039192");
      dir->GetObject("O2fwdtrack",tree);

   }
   Init(tree);
}

O2fwdtrack::~O2fwdtrack()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t O2fwdtrack::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t O2fwdtrack::LoadTree(Long64_t entry)
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

void O2fwdtrack::Init(TTree *tree)
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
   fChain->SetBranchAddress("fY", &fY, &b_fY);
   fChain->SetBranchAddress("fZ", &fZ, &b_fZ);
   fChain->SetBranchAddress("fPhi", &fPhi, &b_fPhi);
   fChain->SetBranchAddress("fTgl", &fTgl, &b_fTgl);
   fChain->SetBranchAddress("fSigned1Pt", &fSigned1Pt, &b_fSigned1Pt);
   fChain->SetBranchAddress("fNClusters", &fNClusters, &b_fNClusters);
   fChain->SetBranchAddress("fPDca", &fPDca, &b_fPDca);
   fChain->SetBranchAddress("fRAtAbsorberEnd", &fRAtAbsorberEnd, &b_fRAtAbsorberEnd);
   fChain->SetBranchAddress("fChi2", &fChi2, &b_fChi2);
   fChain->SetBranchAddress("fChi2MatchMCHMID", &fChi2MatchMCHMID, &b_fChi2MatchMCHMID);
   fChain->SetBranchAddress("fChi2MatchMCHMFT", &fChi2MatchMCHMFT, &b_fChi2MatchMCHMFT);
   fChain->SetBranchAddress("fMatchScoreMCHMFT", &fMatchScoreMCHMFT, &b_fMatchScoreMCHMFT);
   fChain->SetBranchAddress("fTrackTime", &fTrackTime, &b_fTrackTime);
   fChain->SetBranchAddress("fTrackTimeRes", &fTrackTimeRes, &b_fTrackTimeRes);
   fChain->SetBranchAddress("fIndexMFTTracks", &fIndexMFTTracks, &b_fIndexMFTTracks);
   fChain->SetBranchAddress("fIndexFwdTracks_MatchMCHTrack", &fIndexFwdTracks_MatchMCHTrack, &b_fIndexFwdTracks_MatchMCHTrack);
   fChain->SetBranchAddress("fMCHBitMap", &fMCHBitMap, &b_fMCHBitMap);
   fChain->SetBranchAddress("fMIDBitMap", &fMIDBitMap, &b_fMIDBitMap);
   fChain->SetBranchAddress("fMIDBoards", &fMIDBoards, &b_fMIDBoards);
   Notify();
}

Bool_t O2fwdtrack::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void O2fwdtrack::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t O2fwdtrack::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef O2fwdtrack_cxx
