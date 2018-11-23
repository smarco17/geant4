#include "DetectorConstruction.hh"
#include "TrackerSD.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4SDManager.hh"

#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"

#include "G4GeometryTolerance.hh"
#include "G4GeometryManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4RotationMatrix.hh"


DetectorConstruction::DetectorConstruction() : G4VUserDetectorConstruction(),
fAir(0), fAu(0), fSi(0), fCheckOverlaps(true){
  DefineMaterials();
}

DetectorConstruction::~DetectorConstruction(){}
 
G4VPhysicalVolume* DetectorConstruction::Construct(){
  return DefineVolumes();
}

void DetectorConstruction::DefineMaterials(){
  G4NistManager* nistManager = G4NistManager::Instance();
  fAir = nistManager->FindOrBuildMaterial("G4_AIR");
  fAu = nistManager->FindOrBuildMaterial("G4_Au");
  fSi = nistManager->FindOrBuildMaterial("G4_Si");
}

G4VPhysicalVolume* DetectorConstruction::DefineVolumes(){
  G4double worldSize = 20*cm;

  G4Box* worldS = new G4Box("World", worldSize/2, worldSize/2, worldSize/2);
  G4LogicalVolume* worldLV = new G4LogicalVolume(worldS, fAir, "World");
  
  G4VPhysicalVolume* worldPV = new G4PVPlacement(0,
                                                 G4ThreeVector(),
                                                 worldLV,
                                                 "World",
                                                 0,
                                                 false,
                                                 0,
                                                 fCheckOverlaps); 
                                    
  G4Box* targetS = new G4Box("Target", 4*cm, 4*cm, 1*cm/2);
  G4LogicalVolume* targetLV = new G4LogicalVolume(targetS, fAu, "Target");
  new G4PVPlacement(0,
                    G4ThreeVector(0, 0, 0),
                    targetLV,
                    "Target",
                    worldLV,
                    false,
                    0,
                    fCheckOverlaps); 

  // Tracker
  G4RotationMatrix* rot = new G4RotationMatrix();
  rot->rotateY(135*deg);

  G4Tubs* trackerS = new G4Tubs("Tracker", 0, 1*cm, 3*mm/2, 0.*deg, 360.*deg);
  G4LogicalVolume* trackerLV = new G4LogicalVolume(trackerS, fSi, "Tracker");  
  new G4PVPlacement(rot,
                    G4ThreeVector(1.*cm, 0, 1.*cm),
                    trackerLV,
                    "Tracker",
                    worldLV,
                    false,
                    0,
                    fCheckOverlaps);

  return worldPV;
}
 
void DetectorConstruction::ConstructSDandField(){
  G4String trackerChamberSDname = "TrackerSD";
  TrackerSD* aTrackerSD = new TrackerSD(trackerChamberSDname, "TrackerHitsCollection");

  G4SDManager::GetSDMpointer()->AddNewDetector(aTrackerSD);
  SetSensitiveDetector("Tracker", aTrackerSD, true);
}
