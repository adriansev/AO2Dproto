#pragma once

#include <Rtypes.h>
#include <TMath.h>
#include <TVector2.h>
#include <Math/GenVector/LorentzVector.h>
#include <Math/Vector4D.h>
#include "o2data_model/DataTypes.h"
#include "ttree_selectors.h"

//https://aliceo2group.github.io/analysis-framework/docs/datamodel/ao2dTables.html
//https://github.com/AliceO2Group/AliceO2/blob/dev/Framework/Core/include/Framework/AnalysisDataModel.h#L115
//https://github.com/AliceO2Group/AliceO2/blob/dev/Common/MathUtils/include/MathUtils/Utils.h
//https://arrow.apache.org/docs/python/api/compute.html

namespace o2alice {
using namespace TMath;

// Transverse momentum of the track in GeV/c
Float_t track_pt (O2track& trk) { return Abs(1./(*trk.fSigned1Pt)); }
    
bool track_is_pos (O2track& trk) { return (*trk.fSigned1Pt > 0); }

Short_t track_chg (O2track& trk) { return (*trk.fSigned1Pt > 0) ? 1 : -1; }

Float_t track_phi_raw (O2track& trk) { return ASin(*trk.fSnp) + *trk.fAlpha; }

Float_t norm_phi (Float_t phi) { return TVector2::Phi_0_2pi(phi); }

Float_t track_phi (O2track& trk) { return norm_phi(track_phi_raw(trk)); } 

Float_t track_eta (O2track& trk) { return -1.0 * Log( Tan(0.25 * PiOver2() - 0.5 * ATan(*trk.fTgl)) ); }

std::tuple<Float_t, Float_t> sincos(Float_t alpha) {
    Float_t norm_alpha = norm_phi(alpha);
    return std::make_tuple(Sin(norm_alpha), Cos(norm_alpha));
    }

ROOT::Math::XYZTVectorF get_track_xyz(Float_t x, Float_t y, Float_t z) {
    return ROOT::Math::XYZTVectorF(x, y, z, 0.);
    }

ROOT::Math::PtEtaPhiMVector get_track(O2track& trk) { return ROOT::Math::PtEtaPhiMVector(track_pt(trk), track_eta(trk), track_phi(trk), 0.); }

ROOT::Math::PxPyPzMVector get_track_pxpypz(O2track& trk) {
    Float_t sn, cs;
    std::tie(sn, cs) = sincos(*trk.fAlpha);
    Float_t pt = track_pt(trk);
    Float_t r = Sqrt((1.0 - *trk.fSnp) * (1.0 + *trk.fSnp));

    Float_t px = pt * (        r * cs - *trk.fSnp * sn);
    Float_t py = pt * (*trk.fSnp * cs +         r * sn);
    Float_t pz = pt * (*trk.fTgl);
    return ROOT::Math::PxPyPzMVector(px, py, pz, 0.);
    }

Float_t get_track_P (O2track& trk) {
    return 0.5 * (Tan(PiOver4() - 0.5 * ATan(*trk.fTgl)) + 1./Tan(PiOver4() - 0.5 * ATan(*trk.fTgl))) / Abs(*trk.fSigned1Pt) ;
    }

bool track_is_type (O2track& trk, o2::aod::track::TrackTypeEnum type) { return (static_cast<int>(*trk.fTrackType) == type); }
bool is_track (O2track& trk) { return (o2alice::track_is_type(trk,o2::aod::track::Track) || o2alice::track_is_type(trk,o2::aod::track::Run2Track)) ; }
bool is_run2  (O2track& trk) { return (o2alice::track_is_type(trk,o2::aod::track::Run2Track) || o2alice::track_is_type(trk,o2::aod::track::Run2Tracklet)) ; }


// Default track selection requiring one hit in the SPD
TrackSelection getGlobalTrackSelection() {
    TrackSelection selectedTracks;
    selectedTracks.SetTrackType(o2::aod::track::Run2Track);
    selectedTracks.SetPtRange(0.1f, 1e10f);
    selectedTracks.SetEtaRange(-0.8f, 0.8f);
    selectedTracks.SetRequireITSRefit(true);
    selectedTracks.SetRequireTPCRefit(true);
    selectedTracks.SetRequireGoldenChi2(true);
    selectedTracks.SetMinNCrossedRowsTPC(70);
    selectedTracks.SetMinNCrossedRowsOverFindableClustersTPC(0.8f);
    selectedTracks.SetMaxChi2PerClusterTPC(4.f);
    selectedTracks.SetRequireHitsInITSLayers(1, {0, 1}); // one hit in any SPD layer
    selectedTracks.SetMaxChi2PerClusterITS(36.f);
    selectedTracks.SetMaxDcaXYPtDep([](float pt) { return 0.0105f + 0.0350f / pow(pt, 1.1f); });
    selectedTracks.SetMaxDcaZ(2.f);
    return selectedTracks;
    }

// Default track selection requiring no hit in the SPD and one in the innermost
// SDD -> complementary tracks to global selection
TrackSelection getGlobalTrackSelectionSDD() {
    TrackSelection selectedTracks = getGlobalTrackSelection();
    selectedTracks.ResetITSRequirements();
    selectedTracks.SetRequireNoHitsInITSLayers({0, 1}); // no hit in SPD layers
    selectedTracks.SetRequireHitsInITSLayers(1, {2});   // one hit in first SDD layer
    return selectedTracks;
    }

















}

