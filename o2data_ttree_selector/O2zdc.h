//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Feb 18 23:20:43 2022 by ROOT version 6.25/99
// from TTree O2zdc/ZDC
// found on file: AO2D.root
//////////////////////////////////////////////////////////

#ifndef O2zdc_h
#define O2zdc_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>

// Headers needed by this particular selector


class O2zdc : public TSelector {
public :
   TTreeReader     fReader;  //!the tree reader
   TTree          *fChain = 0;   //!pointer to the analyzed TTree or TChain

   // Readers to access the data (delete the ones you do not need).
   TTreeReaderValue<Int_t> fIndexBCs = {fReader, "fIndexBCs"};
   TTreeReaderValue<Float_t> fEnergyZEM1 = {fReader, "fEnergyZEM1"};
   TTreeReaderValue<Float_t> fEnergyZEM2 = {fReader, "fEnergyZEM2"};
   TTreeReaderValue<Float_t> fEnergyCommonZNA = {fReader, "fEnergyCommonZNA"};
   TTreeReaderValue<Float_t> fEnergyCommonZNC = {fReader, "fEnergyCommonZNC"};
   TTreeReaderValue<Float_t> fEnergyCommonZPA = {fReader, "fEnergyCommonZPA"};
   TTreeReaderValue<Float_t> fEnergyCommonZPC = {fReader, "fEnergyCommonZPC"};
   TTreeReaderArray<Float_t> fEnergySectorZNA = {fReader, "fEnergySectorZNA"};
   TTreeReaderArray<Float_t> fEnergySectorZNC = {fReader, "fEnergySectorZNC"};
   TTreeReaderArray<Float_t> fEnergySectorZPA = {fReader, "fEnergySectorZPA"};
   TTreeReaderArray<Float_t> fEnergySectorZPC = {fReader, "fEnergySectorZPC"};
   TTreeReaderValue<Float_t> fTimeZEM1 = {fReader, "fTimeZEM1"};
   TTreeReaderValue<Float_t> fTimeZEM2 = {fReader, "fTimeZEM2"};
   TTreeReaderValue<Float_t> fTimeZNA = {fReader, "fTimeZNA"};
   TTreeReaderValue<Float_t> fTimeZNC = {fReader, "fTimeZNC"};
   TTreeReaderValue<Float_t> fTimeZPA = {fReader, "fTimeZPA"};
   TTreeReaderValue<Float_t> fTimeZPC = {fReader, "fTimeZPC"};


   O2zdc(TTree * /*tree*/ =0) { }
   virtual ~O2zdc() { }
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

   ClassDef(O2zdc,0);

};

#endif

#ifdef O2zdc_cxx
void O2zdc::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the reader is initialized.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   fReader.SetTree(tree);
}

Bool_t O2zdc::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}


#endif // #ifdef O2zdc_cxx
