#include "DetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"

// add
#include "globals.hh"

DetectorConstruction::DetectorConstruction():G4VUserDetectorConstruction(){}

DetectorConstruction::~DetectorConstruction(){}

G4VPhysicalVolume* DetectorConstruction::Construct(){
  // 物質マネージャー
  //
  G4NistManager* nist = G4NistManager::Instance();
  G4Material* worldMat = nist->FindOrBuildMaterial("G4_AIR");

  // World
  G4double worldXYZ = 1.*cm;
  G4Box* solidWorld = new G4Box("World", worldXYZ/2, worldXYZ/2, worldXYZ/2);

  G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld, worldMat, "World");

  G4VPhysicalVolume* physWorld = new G4PVPlacement(0,                      // no rotation
                                                   G4ThreeVector(0, 0, 0), // at (0,0,0)
                                                   logicWorld,             // its logical volume
                                                   "World",                // its name
                                                   0,                      // its mother  volume
                                                   false,                  // no boolean operation
                                                   0,                      // copy number
                                                   true);                  // overlaps checking
  
  return physWorld;
}
