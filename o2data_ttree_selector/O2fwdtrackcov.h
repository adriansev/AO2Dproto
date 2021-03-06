//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Feb 23 17:36:54 2022 by ROOT version 6.25/99
// from TTree O2fwdtrackcov/Forward tracks Covariances
// found on file: AO2D.root
//////////////////////////////////////////////////////////

#ifndef O2fwdtrackcov_h
#define O2fwdtrackcov_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>

// Headers needed by this particular selector


class O2fwdtrackcov : public TSelector {
public :
   TTreeReader     fReader;  //!the tree reader
   TTree          *fChain = 0;   //!pointer to the analyzed TTree or TChain

   // Readers to access the data (delete the ones you do not need).
   TTreeReaderValue<Float_t> fSigmaX = {fReader, "fSigmaX"};
   TTreeReaderValue<Float_t> fSigmaY = {fReader, "fSigmaY"};
   TTreeReaderValue<Float_t> fSigmaPhi = {fReader, "fSigmaPhi"};
   TTreeReaderValue<Float_t> fSigmaTgl = {fReader, "fSigmaTgl"};
   TTreeReaderValue<Float_t> fSigma1Pt = {fReader, "fSigma1Pt"};
   TTreeReaderValue<Char_t> fRhoXY = {fReader, "fRhoXY"};
   TTreeReaderValue<Char_t> fRhoPhiX = {fReader, "fRhoPhiX"};
   TTreeReaderValue<Char_t> fRhoPhiY = {fReader, "fRhoPhiY"};
   TTreeReaderValue<Char_t> fRhoTglX = {fReader, "fRhoTglX"};
   TTreeReaderValue<Char_t> fRhoTglY = {fReader, "fRhoTglY"};
   TTreeReaderValue<Char_t> fRhoTglPhi = {fReader, "fRhoTglPhi"};
   TTreeReaderValue<Char_t> fRho1PtX = {fReader, "fRho1PtX"};
   TTreeReaderValue<Char_t> fRho1PtY = {fReader, "fRho1PtY"};
   TTreeReaderValue<Char_t> fRho1PtPhi = {fReader, "fRho1PtPhi"};
   TTreeReaderValue<Char_t> fRho1PtTgl = {fReader, "fRho1PtTgl"};


   O2fwdtrackcov(TTree * /*tree*/ =0) { }
   virtual ~O2fwdtrackcov() { }
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

   ClassDef(O2fwdtrackcov,0);

};

#endif

#ifdef O2fwdtrackcov_cxx
void O2fwdtrackcov::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the reader is initialized.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   fReader.SetTree(tree);
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


#endif // #ifdef O2fwdtrackcov_cxx
