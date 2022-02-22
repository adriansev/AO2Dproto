//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Feb 18 23:20:43 2022 by ROOT version 6.25/99
// from TTree O2fwdtrack/Forward tracks Parameters
// found on file: AO2D.root
//////////////////////////////////////////////////////////

#ifndef O2fwdtrack_h
#define O2fwdtrack_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>

// Headers needed by this particular selector


class O2fwdtrack : public TSelector {
public :
   TTreeReader     fReader;  //!the tree reader
   TTree          *fChain = 0;   //!pointer to the analyzed TTree or TChain

   // Readers to access the data (delete the ones you do not need).
   TTreeReaderValue<Int_t> fIndexCollisions = {fReader, "fIndexCollisions"};
   TTreeReaderValue<Int_t> fTrackType = {fReader, "fTrackType"};
   TTreeReaderValue<Float_t> fX = {fReader, "fX"};
   TTreeReaderValue<Float_t> fY = {fReader, "fY"};
   TTreeReaderValue<Float_t> fZ = {fReader, "fZ"};
   TTreeReaderValue<Float_t> fPhi = {fReader, "fPhi"};
   TTreeReaderValue<Float_t> fTgl = {fReader, "fTgl"};
   TTreeReaderValue<Float_t> fSigned1Pt = {fReader, "fSigned1Pt"};
   TTreeReaderValue<Int_t> fNClusters = {fReader, "fNClusters"};
   TTreeReaderValue<Float_t> fPDca = {fReader, "fPDca"};
   TTreeReaderValue<Float_t> fRAtAbsorberEnd = {fReader, "fRAtAbsorberEnd"};
   TTreeReaderValue<Float_t> fChi2 = {fReader, "fChi2"};
   TTreeReaderValue<Float_t> fChi2MatchMCHMID = {fReader, "fChi2MatchMCHMID"};
   TTreeReaderValue<Float_t> fChi2MatchMCHMFT = {fReader, "fChi2MatchMCHMFT"};
   TTreeReaderValue<Float_t> fMatchScoreMCHMFT = {fReader, "fMatchScoreMCHMFT"};
   TTreeReaderValue<Float_t> fTrackTime = {fReader, "fTrackTime"};
   TTreeReaderValue<Float_t> fTrackTimeRes = {fReader, "fTrackTimeRes"};
   TTreeReaderValue<Int_t> fIndexMFTTracks = {fReader, "fIndexMFTTracks"};
   TTreeReaderValue<Int_t> fIndexFwdTracks_MatchMCHTrack = {fReader, "fIndexFwdTracks_MatchMCHTrack"};
   TTreeReaderValue<UShort_t> fMCHBitMap = {fReader, "fMCHBitMap"};
   TTreeReaderValue<UShort_t> fMIDBitMap = {fReader, "fMIDBitMap"};
   TTreeReaderValue<UInt_t> fMIDBoards = {fReader, "fMIDBoards"};


   O2fwdtrack(TTree * /*tree*/ =0) { }
   virtual ~O2fwdtrack() { }
   virtual Int_t   Version() const { return 2; }
   virtual void    Begin(TTree *tree);
   virtual void    SlaveBegin(TTree *tree);
   virtual void    Init(TTree *tree);
   virtual Bool_t  Notify();
   virtual Bool_t  Process(Long64_t entry);
   virtual Int_t   GetEntry(Long64_t entry, Int_t getall = 0) { return fChain ? fChain->GetTree()->GetEntry(entry, getall) : 0; }
   virtual void    SetOption(const char *option) { fOption = option; }
   virtual void    SetObject(TObject *obj) { fObject = obj; }
   virtual void    SetInputList(TList *input) { fInput = input; }
   virtual TList  *GetOutputList() const { return fOutput; }
   virtual void    SlaveTerminate();
   virtual void    Terminate();

   ClassDef(O2fwdtrack,0);

};

#endif

#ifdef O2fwdtrack_cxx
void O2fwdtrack::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the reader is initialized.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   fReader.SetTree(tree);
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


#endif // #ifdef O2fwdtrack_cxx
