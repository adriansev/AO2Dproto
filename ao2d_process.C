//usr/bin/env -S root.exe -b -q -l -e ".x ${0}" ; exit $?
#include <algorithm>
#include <unordered_map>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <cctype>
#include <cmath>
#include <string>
#include <string_view>
#include <memory>

#include <TROOT.h>
#include <TSystem.h>
#include <TFile.h>
#include <TKey.h>
#include <TTree.h>
#include <TH1.h>
#include <TH2.h>
#include <TProfile.h>
#include <TEntryList.h>

#include <ROOT/StringUtils.hxx>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>

#include "ttree_selectors.h"
#include "ao2d_tools.C"
#include "load_selectors.C"
#include "o2data_model/DataTypes.h"
#include "alice_DataModel.C"

R__ADD_INCLUDE_PATH(./o2data_ttree_selector)
R__ADD_LIBRARY_PATH(./o2data_ttree_selector)

using std::cout;
using std::endl;
using std::string;
using std::vector;

typedef std::vector<long long> VecInt;
typedef std::unordered_map<int, VecInt> CollEv;
typedef std::unordered_map<std::string, TTree*> TTreeCol;

bool CheckValue(ROOT::Internal::TTreeReaderValueBase& value);

//###############################################
int ao2d_process (/*int argc, char* argv[]*/) {
// vector<string> args(argv + 1, argv + argc);    // put all args in a vector // TODO process args
ROOT::EnableImplicitMT();  // enable multi-threading
load_selectors();  // load (+compile) the selectors of TTree structures of AO2D format

std::string input_file = "file_list";
std::vector<std::string> input_file_list = parse_file(input_file);
std::vector< std::pair<std::string,std::string> > df_locations = GetDFlist(input_file);  // collection of <file,DF> pairs

//##################
// DECLARE HISTOGRAMS TO BE FILLED; these should be outside of loops over collisions/tracks
TH1::AddDirectory(kFALSE); // disable automatic association to gDirectory (latest opened TFile)
// std::unique_ptr<TH1> hist = new TH1F("hist", "hist", 10, 0., 1.)
std::unique_ptr<TH1I> fVtx                 (new TH1I("fVtx","Vtx info (0=no, 1=yes); Vtx; Counts", 2, -0.5, 1.5));
std::unique_ptr<TH1F> fVtxCuts             (new TH1F("fVtxCuts", "Vtx distribution (before cuts); Vtx z [cm]; Counts", 120, -30, 30));
std::unique_ptr<TH2F> fMultvsCent          (new TH2F("fMultvsCent", "; centrality; multiplicity", 100, 0, 100, 1000, -0.5, 3999.5));
std::unique_ptr<TH2F> fCenCL0vsV0M         (new TH2F("fCenCL0vsV0M", "; centrality V0M; centrality CL0", 100, 0, 100, 100, 0, 100));
std::unique_ptr<TH2F> fCenCL1vsV0M         (new TH2F("fCenCL1vsV0M", "; centrality V0M; centrality CL1", 100, 0, 100, 100, 0, 100));
std::unique_ptr<TH2F> fCenCL0vsCL1         (new TH2F("fCenCL0vsCL1", "; centrality CL1; centrality CL0", 100, 0, 100, 100, 0, 100));
std::unique_ptr<TH2I> fSPclsvsSPDtrks      (new TH2I("fSPclsvsSPDtrks", "; SPD N_{tracklets}; SPD N_{clusters}", 1000, -0.5, 6999.5, 1000, -0.5, 24999.5));
std::unique_ptr<TH2F> fMultV0onvsMultV0of  (new TH2F("fMultV0onvsMultV0of", "; V0 offline; V0 online", 1000, 0, 50000, 1000, 0, 50000));
std::unique_ptr<TH2F> fNclsTPCvsMultV0     (new TH2F("fNclsTPCvsMultV0", "; V0 multiplicity; N_{cls}", 1000, 0, 50000, 1000, 0, 8000000));
std::unique_ptr<TH2F> fNclsTPCvsNclsSDDSSD (new TH2F("fNclsTPCvsNclsSDDSSD", "; N_{cls} (SSD+SDD); N_{cls} (TPC)", 1000, 0, 60000, 1000, 0, 8000000));

const Int_t nCenB = 9;
Float_t cenBins[nCenB+1] = {0, 5., 10., 20., 30., 40., 50., 60., 70., 80.};

std::unique_ptr<TProfile> fRes (new TProfile("fRes", "; centrality percentile; Resolution", nCenB, cenBins));
std::unique_ptr<TProfile> fQxnA (new TProfile("fQxnA", "; centrality percentile; #LT Q_{x}^{n} #GT", nCenB, cenBins));
std::unique_ptr<TProfile> fQxnC (new TProfile("fQxnC", "; centrality percentile; #LT Q_{x}^{n} #GT", nCenB, cenBins));
std::unique_ptr<TProfile> fQynA (new TProfile("fQynA", "; centrality percentile; #LT Q_{y}^{n} #GT", nCenB, cenBins));
std::unique_ptr<TProfile> fQynC (new TProfile("fQynC", "; centrality percentile; #LT Q_{y}^{n} #GT", nCenB, cenBins));

const Int_t nPtB = 25;
Double_t ptBins[nPtB+1] = {0., 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 1.2, 1.4, 1.6, 1.8, 2.0, 2.25, 2.5, 2.75, 3.0, 3.5, 4.0, 4.5, 5.0, 6.0, 8.0, 10.};

TProfile*  fVnAPt[9];            // vn SP TPC A
TProfile*  fVnCPt[9];            // vn SP TPC A
TProfile*  fSinnAPt[9];          // <sin(n*phi)> TPC A
TProfile*  fSinnCPt[9];          // <sin(n*phi)> TPC A
TProfile*  fCosnAPt[9];          // <cos(n*phi)> TPC A
TProfile*  fCosnCPt[9];          // <cos(n*phi)> TPC A

for (Int_t i = 0 ; i < 9; i++) {
    fVnAPt[i] = new TProfile(Form("fVnAPt_%d", i), "; p_{T} (GeV/c); v_{n}", nPtB, ptBins);
    fVnCPt[i] = new TProfile(Form("fVnCPt_%d", i), "; p_{T} (GeV/c); v_{n}", nPtB, ptBins);
    fSinnAPt[i] = new TProfile(Form("fSinnAPt_%d", i), "; p_{T} (GeV/c); #LT sin(n*#phi) #Gt", nPtB, ptBins);
    fSinnCPt[i] = new TProfile(Form("fSinnCPt_%d", i), "; p_{T} (GeV/c); #LT sin(n*#phi) #Gt", nPtB, ptBins);
    fCosnAPt[i] = new TProfile(Form("fCosnAPt_%d", i), "; p_{T} (GeV/c); #LT cos(n*#phi) #Gt", nPtB, ptBins);
    fCosnCPt[i] = new TProfile(Form("fCosnCPt_%d", i), "; p_{T} (GeV/c); #LT cos(n*#phi) #Gt", nPtB, ptBins);
    }

//##################
for (auto d: df_locations) {  // parse DFs found in files
        TFile tfile(d.first.c_str());
        vector<string> tree_list = get_df_trees(tfile, d.second);
        if (tree_list.empty()) { continue; }
        TTreeCol df_trees;
        for (auto t: tree_list){ df_trees[t] = GetTree(tfile, d.second, t); }

        df_trees["O2track"]->AddFriend(df_trees["O2trackextra"]);
        df_trees["O2track"]->AddFriend(df_trees["O2trackcov"]);
        //for (const auto&& obj: *df_trees["O2track"]->GetListOfFriends()) { cout << "Friend name : " << obj->GetName() << endl; }
        
        // just for grouping of tracks in collisions events
        CollEv coll_list;  // list of index collision groups

        O2track o2track;
        o2track.Init(df_trees["O2track"]);
        df_trees["O2track"]->SetBranchStatus("*",0);
        df_trees["O2track"]->SetBranchStatus("fIndexCollisions",1);

        /*
        IMPORTANT DETAIL on collisionIDs !!!!
        Anton Alkin dixit: the positive indices are sorted, and the negative are sorted on their own
        */
        bool firstEntry = true;
        while (o2track.fReader.Next()) {
            if (firstEntry) { // check availability of the variable
                if (!CheckValue(o2track.fIndexCollisions)) { break; }
                firstEntry = false;
                }
            if (*o2track.fIndexCollisions < 0) { continue; } // negative fIndexCollisions means that track is not assigned to a collision
            coll_list[*o2track.fIndexCollisions].push_back(o2track.fReader.GetCurrentEntry());
            }
        if (coll_list.size() == 0) {
            std::cout << "No collision grouping could be made on this data: " << d.first + "/" + d.second << std::endl;
            continue;
            }
        df_trees["O2track"]->SetBranchStatus("*",1); // re-enable all branches

        // START OF COLLISIONS/EVENTS? parsin
        for (auto ev: coll_list) {  // guaranteed to have non-null tracks vector
            // HERE we can filter on aod::Collisions
            // https://github.com/AliceO2Group/analysis-framework/blob/master/docs/datamodel/ao2dTables.md
            // to add getters for collisons info
            // APPLY FILTERING ON COLLISIONS
            // DECLARE PER COLLISION VARIABLES

            // Compute vertex  // TODO
            // GetPrimaryVertex()
            // GetPrimaryVertexSPD
            // Compute zvtx and act on it  
            // fVtx->Fill( (zvtx < -990)? 0: 1)
            // if (abs(zvtx) > fVtxCut) { continue; } // skip this collision if zvtx is over the cut
//             fVtxCuts->Fill(vtxZ);

//             //new vertex selection
//             const AliAODVertex* vtTrc = aod->GetPrimaryVertex();
//             const AliAODVertex* vtSPD = aod->GetPrimaryVertexSPD();
//             
//             double covTrc[6], covSPD[6];
//             vtTrc->GetCovarianceMatrix(covTrc);
//             vtSPD->GetCovarianceMatrix(covSPD);
//             
//             double dz = vtTrc->GetZ() - vtSPD->GetZ();
//             
//             double errTot = TMath::Sqrt(covTrc[5]+covSPD[5]);
//             double errTrc = TMath::Sqrt(covTrc[5]);
//             double nsigTot = dz/errTot;
//             double nsigTrc = dz/errTrc;
//             
//             if (TMath::Abs(dz)>0.5 || TMath::Abs(nsigTot)>10 || TMath::Abs(nsigTrc)>20)
//                 return; // bad vertexing

            // Compute multiplicity  // TODO
            // v0Centr // V0M

            // cl1Centr // CL1
            // cl0Centr // CL0
            // if (v0Centr >= 80. || v0Centr < 0) { continue; }
//             fCenCL0vsV0M->Fill(v0Centr, cl0Centr);
//             fCenCL1vsV0M->Fill(v0Centr, cl1Centr);
//             fCenCL0vsCL1->Fill(cl1Centr, cl0Centr);


//             Short_t centrCode = -10;
//             if ((v0Centr >= 0) && (v0Centr < 5.))
//                 centrCode = 0;
//             else if ((v0Centr >= 5.) && (v0Centr < 10.))
//                 centrCode = 1;
//             else if ((v0Centr >= 10.) && (v0Centr < 20.))
//                 centrCode = 2;
//             else if ((v0Centr >= 20.) && (v0Centr < 30.))
//                 centrCode = 3;
//             else if ((v0Centr >= 30.) && (v0Centr < 40.))
//                 centrCode = 4;
//             else if ((v0Centr >= 40.) && (v0Centr < 50.))
//                 centrCode = 5;
//             else if ((v0Centr >= 50.) && (v0Centr < 60.))
//                 centrCode = 6;
//             else if ((v0Centr >= 60.) && (v0Centr < 70.))
//                 centrCode = 7;
//             else if ((v0Centr >= 70.) && (v0Centr < 80.))
//                 centrCode = 8;
// 
//             if (centrCode < 0)
//                 return;

//             Int_t nITSClsLy0 = aod->GetNumberOfITSClusters(0);
//             Int_t nITSClsLy1 = aod->GetNumberOfITSClusters(1);
//             Int_t nITSCls = nITSClsLy0 + nITSClsLy1;
//             
//             AliAODTracklets* aodTrkl = (AliAODTracklets*)aod->GetTracklets();
//             Int_t nITSTrkls = aodTrkl->GetNumberOfTracklets();
//             fSPclsvsSPDtrks->Fill(nITSTrkls, nITSCls);

//             AliAODVZERO* aodV0 = aod->GetVZEROData();
//             Float_t multV0a = aodV0->GetMTotV0A();
//             Float_t multV0c = aodV0->GetMTotV0C();
//             Float_t multV0Tot = multV0a + multV0c;

//             UShort_t multV0aOn = aodV0->GetTriggerChargeA();
//             UShort_t multV0cOn = aodV0->GetTriggerChargeC();
//             UShort_t multV0On = multV0aOn + multV0cOn;
//             
//             Int_t tpcClsTot = aod->GetNumberOfTPCClusters();
//             //clusters SDD+SSD
//             AliVMultiplicity* mult = aod->GetMultiplicity();
//             Int_t nCluSDDSSD=0;
//             for(Int_t iLay = 2; iLay < 6; iLay++)
//                 nCluSDDSSD += mult->GetNumberOfITSClusters(iLay);

//             fMultV0onvsMultV0of->Fill(multV0Tot, multV0On);
//             fNclsTPCvsMultV0->Fill(multV0Tot, tpcClsTot);
//             fNclsTPCvsNclsSDDSSD->Fill(nCluSDDSSD, tpcClsTot);

    
            Double_t QxnGapA = 0., QynGapA = 0., QxnGapC = 0., QynGapC = 0.;
            Int_t multGapA = 0, multGapC = 0, multTrk = 0;





            for (auto entry: ev.second) {  // parse vector of entries
                o2track.fReader.SetEntry(entry);
                o2track.fReader.Next();
                int track_type = static_cast<int>(*o2track.fTrackType);
                // if not Track or Run2Track then skip
                if ( !((track_type == o2::aod::track::Track) || (track_type == o2::aod::track::Run2Track)) ) { continue; };
                // Track filtering
                // if (!condition) { continue; }
                // taskD->SetMinPt(minPt);
                // taskD->SetMaxPt(maxPt);
                // taskD->SetNoClus(noclus); // No of TPC clusters
                // taskD->SetEtaCut(etaCut); // Eta cut used to select particles
                // taskD->SetVtxCut(vtxCut); // Vtx cut on z position in cm
                // taskD->SetNHarmonic(nHarm); // harmonic number
                // taskD->SetEtaGap(etaGap); // eta gap for gap 1 -> fEtaGap = 0.5
              
                // taskD->SetFilterbit(filterbit); // Not existent???

                // fVtxCut(10.0), fEtaCut(0.8), fNoClus(70), fMinPt(0.2),
                // fMaxPt(5.0), fNHarm(2.), fFilterbit(768), fEtaGap(0.5),

//         if (aodTrk->TestFilterBit(32)) multTrk++;
//         if (!(aodTrk->TestFilterBit(fFilterbit))) continue;
        
//         if ((TMath::Abs(aodTrk->Eta()) >= fEtaCut) ||
//             (aodTrk->Pt() < fMinPt) || (aodTrk->Pt() >= fMaxPt) ||
//             (aodTrk->GetTPCNcls() < fNoClus)) { continue; }
        
//         if (aodTrk->Eta() > fEtaGap) {
//             QxnGapC += TMath::Cos(fNHarm*aodTrk->Phi());
//             QynGapC += TMath::Sin(fNHarm*aodTrk->Phi());
//             multGapC++;
//             }
        
//         if (aodTrk->Eta() < -fEtaGap){
//             QxnGapA += TMath::Cos(fNHarm*aodTrk->Phi());
//             QynGapA += TMath::Sin(fNHarm*aodTrk->Phi());
//             multGapA++;
//             }


                }  // end of loop over collision tracks

            // Use global/per collision accumulated metrics; Fill histos


//     fMultvsCent->Fill(v0Centr, multTrk);
//     
//     if (multGapA > 0 && multGapC > 0){
//         Double_t resGap = (QxnGapA*QxnGapC + QynGapA*QynGapC)/(Double_t)multGapA/(Double_t)multGapC;
//         fRes->Fill(v0Centr, resGap);
//         fQxnA->Fill(v0Centr, QxnGapA/(Double_t)multGapA);
//         fQxnC->Fill(v0Centr, QxnGapC/(Double_t)multGapC);
//         fQynA->Fill(v0Centr, QynGapA/(Double_t)multGapA);
//         fQynC->Fill(v0Centr, QynGapC/(Double_t)multGapC);
//         }

            // SECOND LOOP OVER TRACKS
            for (auto entry: ev.second) {
                o2track.fReader.SetEntry(entry);
                o2track.fReader.Next();
                int track_type = static_cast<int>(*o2track.fTrackType);
                // if not Track or Run2Track then skip
                if ( !((track_type == o2::aod::track::Track) || (track_type == o2::aod::track::Run2Track)) ) { continue; };


//                 if (aodTrk1->Eta() < -fEtaGap && multGapC > 0){
//                     Double_t vnA = (TMath::Cos(fNHarm*aodTrk1->Phi())*QxnGapC + TMath::Sin(fNHarm*aodTrk1->Phi())*QynGapC)/(Double_t)multGapC;
//                     fVnAPt[centrCode]->Fill(aodTrk1->Pt(), vnA);
//                     fSinnAPt[centrCode]->Fill(aodTrk1->Pt(), TMath::Sin(fNHarm*aodTrk1->Phi()));
//                     fCosnAPt[centrCode]->Fill(aodTrk1->Pt(), TMath::Cos(fNHarm*aodTrk1->Phi()));
//                     }
//                 
//                 if (aodTrk1->Eta() > fEtaGap && multGapA > 0){
//                     Double_t vnC = (TMath::Cos(fNHarm*aodTrk1->Phi())*QxnGapA + TMath::Sin(fNHarm*aodTrk1->Phi())*QynGapA)/(Double_t)multGapA;
//                     fVnCPt[centrCode]->Fill(aodTrk1->Pt(), vnC);
//                     fSinnCPt[centrCode]->Fill(aodTrk1->Pt(), TMath::Sin(fNHarm*aodTrk1->Phi()));
//                     fCosnCPt[centrCode]->Fill(aodTrk1->Pt(), TMath::Cos(fNHarm*aodTrk1->Phi()));
//                     }

                }  // end of loope over collision tracks


            }  // end of loop over collisions

            
} // end of loop over DFs

return 0;
}

//###################################################################
bool CheckValue(ROOT::Internal::TTreeReaderValueBase& value) {
    if (value.GetSetupStatus() < 0) {
        std::cerr << "Error " << value.GetSetupStatus() << "setting up reader for " << value.GetBranchName() << '\n';
        return false;
        }
    return true;
    }

