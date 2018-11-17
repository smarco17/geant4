#include "DetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "globals.hh"
#include "G4PhysicalConstants.hh"
#include "G4RotationMatrix.hh"

DetectorConstruction::DetectorConstruction():G4VUserDetectorConstruction(){}

DetectorConstruction::~DetectorConstruction(){}

G4VPhysicalVolume* DetectorConstruction::Construct(){
  G4NistManager* nist = G4NistManager::Instance();
  G4Material* worldMat = nist->FindOrBuildMaterial("G4_AIR");
  G4Material* targetMat = nist->FindOrBuildMaterial("G4_Au");

  // World
  G4double worldXYZ = 5.*cm;
  G4Box* solidWorld = new G4Box("World", worldXYZ/2, worldXYZ/2, worldXYZ/2);

  G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld, worldMat, "World");

  G4VPhysicalVolume* physWorld = new G4PVPlacement(0,
                                                   G4ThreeVector(0, 0, 0),
                                                   logicWorld,
                                                   "World",
                                                   0,
                                                   false,
                                                   0,
                                                   true);
  
  // Target
  G4double targetXY = 2.*cm;
  G4double targetZ = 0.5*cm;

  G4Box* solidTarget = new G4Box("Target", targetXY/2, targetXY/2, targetZ/2);
  G4LogicalVolume* logicTarget = new G4LogicalVolume(solidTarget, targetMat, "Target");
  new G4PVPlacement(0,
                    G4ThreeVector(0, 0, -targetZ),
                    logicTarget,
                    "Target",
                    logicWorld,
                    false,
                    0,
                    true);
  
  // detector
  G4double detectorR = 0.5*cm;
  G4double detectorT = 1*um;
  G4RotationMatrix* rot = new G4RotationMatrix();
  rot->rotateY(-pi/4*radian);

  G4Tubs* solidDetector = new G4Tubs("Detector",
                                     0, detectorR,
                                     detectorT,
                                     0, 2*pi*radian);
  G4LogicalVolume* logicDetector = new G4LogicalVolume(solidDetector, worldMat, "Detector");
  new G4PVPlacement(rot,
                    G4ThreeVector(1*cm, 0, 1*cm),
                    logicDetector,
                    "Detector",
                    logicWorld,
                    false,
                    0,
                    true);

  fDetector = logicDetector;
  
  return physWorld;
}
