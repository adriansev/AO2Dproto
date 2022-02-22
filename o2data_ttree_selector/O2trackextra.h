//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Feb 18 23:20:43 2022 by ROOT version 6.25/99
// from TTree O2trackextra/Barrel tracks Extra
// found on file: AO2D.root
//////////////////////////////////////////////////////////

#ifndef O2trackextra_h
#define O2trackextra_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>

// Headers needed by this particular selector


class O2trackextra : public TSelector {
public :
   TTreeReader     fReader;  //!the tree reader
   TTree          *fChain = 0;   //!pointer to the analyzed TTree or TChain

   // Readers to access the data (delete the ones you do not need).
   TTreeReaderValue<Float_t> fTPCInnerParam = {fReader, "fTPCInnerParam"};
   TTreeReaderValue<UInt_t> fFlags = {fReader, "fFlags"};
   TTreeReaderValue<UChar_t> fITSClusterMap = {fReader, "fITSClusterMap"};
   TTreeReaderValue<UChar_t> fTPCNClsFindable = {fReader, "fTPCNClsFindable"};
   TTreeReaderValue<Char_t> fTPCNClsFindableMinusFound = {fReader, "fTPCNClsFindableMinusFound"};
   TTreeReaderValue<Char_t> fTPCNClsFindableMinusCrossedRows = {fReader, "fTPCNClsFindableMinusCrossedRows"};
   TTreeReaderValue<UChar_t> fTPCNClsShared = {fReader, "fTPCNClsShared"};
   TTreeReaderValue<UChar_t> fTRDPattern = {fReader, "fTRDPattern"};
   TTreeReaderValue<Float_t> fITSChi2NCl = {fReader, "fITSChi2NCl"};
   TTreeReaderValue<Float_t> fTPCChi2NCl = {fReader, "fTPCChi2NCl"};
   TTreeReaderValue<Float_t> fTRDChi2 = {fReader, "fTRDChi2"};
   TTreeReaderValue<Float_t> fTOFChi2 = {fReader, "fTOFChi2"};
   TTreeReaderValue<Float_t> fTPCSignal = {fReader, "fTPCSignal"};
   TTreeReaderValue<Float_t> fTRDSignal = {fReader, "fTRDSignal"};
   TTreeReaderValue<Float_t> fLength = {fReader, "fLength"};
   TTreeReaderValue<Float_t> fTOFExpMom = {fReader, "fTOFExpMom"};
   TTreeReaderValue<Float_t> fTrackEtaEMCAL = {fReader, "fTrackEtaEMCAL"};
   TTreeReaderValue<Float_t> fTrackPhiEMCAL = {fReader, "fTrackPhiEMCAL"};
   TTreeReaderValue<Float_t> fTrackTime = {fReader, "fTrackTime"};
   TTreeReaderValue<Float_t> fTrackTimeRes = {fReader, "fTrackTimeRes"};


   O2trackextra(TTree * /*tree*/ =0) { }
   virtual ~O2trackextra() { }
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

   ClassDef(O2trackextra,0);

};

#endif

#ifdef O2trackextra_cxx
void O2trackextra::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the reader is initialized.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   fReader.SetTree(tree);
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


#endif // #ifdef O2trackextra_cxx
