//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Feb 23 17:36:54 2022 by ROOT version 6.25/99
// from TTree O2track/Barrel tracks Parameters
// found on file: AO2D.root
//////////////////////////////////////////////////////////

#ifndef O2track_h
#define O2track_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>

// Headers needed by this particular selector


class O2track : public TSelector {
public :
   TTreeReader     fReader;  //!the tree reader
   TTree          *fChain = 0;   //!pointer to the analyzed TTree or TChain

   // Readers to access the data (delete the ones you do not need).
   TTreeReaderValue<Int_t> fIndexCollisions = {fReader, "fIndexCollisions"};
   TTreeReaderValue<UChar_t> fTrackType = {fReader, "fTrackType"};
   TTreeReaderValue<Float_t> fX = {fReader, "fX"};
   TTreeReaderValue<Float_t> fAlpha = {fReader, "fAlpha"};
   TTreeReaderValue<Float_t> fY = {fReader, "fY"};
   TTreeReaderValue<Float_t> fZ = {fReader, "fZ"};
   TTreeReaderValue<Float_t> fSnp = {fReader, "fSnp"};
   TTreeReaderValue<Float_t> fTgl = {fReader, "fTgl"};
   TTreeReaderValue<Float_t> fSigned1Pt = {fReader, "fSigned1Pt"};


   O2track(TTree * /*tree*/ =0) { }
   virtual ~O2track() { }
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

   ClassDef(O2track,0);

};

#endif

#ifdef O2track_cxx
void O2track::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the reader is initialized.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   fReader.SetTree(tree);
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


#endif // #ifdef O2track_cxx
