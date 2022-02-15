//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sat Jan 22 15:35:17 2022 by ROOT version 6.25/99
// from TTree O2fv0a/FV0A
// found on file: AO2D.root
//////////////////////////////////////////////////////////

#pragma once

#ifndef O2fv0a_h
#define O2fv0a_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>

// Headers needed by this particular selector


class O2fv0a : public TSelector {
public :
   TTreeReader     fReader;  //!the tree reader
   TTree          *fChain = 0;   //!pointer to the analyzed TTree or TChain

   // Readers to access the data (delete the ones you do not need).
   TTreeReaderValue<Int_t> fIndexBCs = {fReader, "fIndexBCs"};
   TTreeReaderArray<Float_t> fAmplitude = {fReader, "fAmplitude"};
   TTreeReaderValue<Float_t> fTime = {fReader, "fTime"};
   TTreeReaderValue<UChar_t> fTriggerMask = {fReader, "fTriggerMask"};


   O2fv0a(TTree * /*tree*/ =0) { }
   virtual ~O2fv0a() { }
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

   ClassDef(O2fv0a,0);

};

#endif

#ifdef O2fv0a_cxx
void O2fv0a::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the reader is initialized.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   fReader.SetTree(tree);
}

Bool_t O2fv0a::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}


#endif // #ifdef O2fv0a_cxx
