#pragma once
#include <cstdint>

namespace o2alice {

namespace collision {
enum CollisionFlagsRun2 : uint16_t {
  Run2VertexerTracks = 0x1,
  Run2VertexerZ = 0x2,
  Run2Vertexer3D = 0x4,
  // upper 8 bits for flags
  Run2VertexerTracksWithConstraint = 0x10,
  Run2VertexerTracksOnlyFitter = 0x20,
  Run2VertexerTracksMultiVertex = 0x40
  };
} // namespace collision

namespace track {

enum TrackTypeEnum : uint8_t {
  Track = 0,
  Run2Track = 254,
  Run2Tracklet = 255
  };
enum TrackFlags {
  TrackTimeResIsRange = 0x1, // Gaussian or range
  PVContributor = 0x2,       // This track has contributed to the collision vertex fit
  OrphanTrack = 0x4          // Track has no association with any collision vertexd
  // NOTE Highest 4 (29..32) bits reserved for PID hypothesis
  };
enum TrackFlagsRun2Enum {
  ITSrefit = 0x1,
  TPCrefit = 0x2,
  GoldenChi2 = 0x4,
  // NOTE Highest 4 (29..32) bits reserved for PID hypothesis
  };
enum DetectorMapEnum : uint8_t {
  ITS = 0x1,
  TPC = 0x2,
  TRD = 0x4,
  TOF = 0x8
  };
} // track

namespace fwdtrack {
enum ForwardTrackTypeEnum : uint8_t {
  GlobalMuonTrack = 0,       // MFT-MCH-MID
  GlobalMuonTrackOtherMatch, // MFT-MCH-MID (MCH-MID used another time)
  GlobalForwardTrack,        // MFT-MCH
  MuonStandaloneTrack,       // MCH-MID
  MCHStandaloneTrack         // MCH
};
} // namespace fwdtrack

namespace mcparticle {
namespace enums {
enum MCParticleFlags : uint8_t {
  ProducedByTransport = 0x1,
  FromBackgroundEvent = 0x2, // Particle from background event (may have been used several times)
  PhysicalPrimary = 0x4      // Particle is a physical primary according to ALICE definition
};
} } // namespace mcparticle::enums

namespace run2 {
enum Run2EventSelectionCut {
  kINELgtZERO = 0,
  kPileupInMultBins,
  kConsistencySPDandTrackVertices,
  kTrackletsVsClusters,
  kNonZeroNContribs,
  kIncompleteDAQ,
  kPileUpMV,
  kTPCPileUp,
  kTimeRangeCut,
  kEMCALEDCut,
  kAliEventCutsAccepted,
  kIsPileupFromSPD,
  kIsV0PFPileup,
  kIsTPCHVdip,
  kIsTPCLaserWarmUp,
  kTRDHCO, // Offline TRD cosmic trigger decision
  kTRDHJT, // Offline TRD jet trigger decision
  kTRDHSE, // Offline TRD single electron trigger decision
  kTRDHQU, // Offline TRD quarkonium trigger decision
  kTRDHEE  // Offline TRD single-electron-in-EMCAL-acceptance trigger decision
};
} // namespace run2

} // namespace o2alice
