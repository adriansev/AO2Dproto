#include <Rtypes.h>
#include <TMath.h>
#include <TVector2.h>
#include <Math/GenVector/LorentzVector.h>
#include <Math/Vector4D.h>

//https://github.com/AliceO2Group/AliceO2/blob/dev/Framework/Core/include/Framework/AnalysisDataModel.h#L115
//https://github.com/AliceO2Group/AliceO2/blob/dev/Common/MathUtils/include/MathUtils/Utils.h
//https://arrow.apache.org/docs/python/api/compute.html

namespace o2alice {
using namespace TMath;

// Transverse momentum of the track in GeV/c
Float_t pt (Float_t signed1pt) {
    return Abs(1./signed1pt);
    }

bool is_pos (Float_t signed1pt) {
    return (signed1pt > 0);
    }

Short_t charge (Float_t signed1pt) {
    return (signed1pt > 0) ? 1 : -1;
    }

Float_t phi_raw (Float_t snp, Float_t alpha) {
    return ASin(snp) + alpha;
    }

Float_t norm_phi (Float_t phi) {
    return TVector2::Phi_0_2pi(phi);
    }

Float_t phi (Float_t snp, Float_t alpha) {
    return norm_phi(phi_raw(snp, alpha));
    }

Float_t eta (Float_t tgl) {
    return -1.0 * Log( Tan(0.25 * PiOver2() - 0.5 * ATan(tgl)) );
    }

std::tuple<Float_t, Float_t> sincos(Float_t alpha) {
    float norm_alpha = norm_phi(alpha);
    return std::make_tuple(Sin(norm_alpha), Cos(norm_alpha));
    }

ROOT::Math::XYZTVectorF track_xyz(Float_t x, Float_t y, Float_t z) {
    return ROOT::Math::XYZTVectorF(x, y, z, 0.);
    }
    
ROOT::Math::PtEtaPhiMVector track(Float_t alpha, Float_t snp, Float_t tgl, Float_t signed1pt) {
    return ROOT::Math::PtEtaPhiMVector(pt(signed1pt), eta(tgl), phi(snp, alpha), 0.);     
    }
    
ROOT::Math::PxPyPzMVector track_pxpypz(Float_t alpha, Float_t snp, Float_t tgl, Float_t signed1pt) {
    Float_t sn, cs;
    std::tie(sn, cs) = sincos(alpha);
    Float_t val_pt = pt(signed1pt);
    Float_t r = Sqrt((1.0 - snp) * (1.0 + snp));
    
    Float_t px = val_pt * (  r * cs - snp * sn);
    Float_t py = val_pt * (snp * cs +   r * sn);
    Float_t pz = val_pt * tgl;
    return ROOT::Math::PxPyPzMVector(px, py, pz, 0.);
    }    
    
Float_t P(Float_t tgl, Float_t signed1pt) {
    return 0.5 * (Tan(PiOver4() - 0.5 * ATan(tgl)) + 1./Tan(PiOver4() - 0.5 * ATan(tgl))) / Abs(signed1pt) ;
    }    
    

}

