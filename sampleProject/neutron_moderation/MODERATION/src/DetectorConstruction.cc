#include "DetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Sphere.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"

#include "globals.hh"
#include "G4PhysicalConstants.hh"

DetectorConstruction::DetectorConstruction():G4VUserDetectorConstruction(){}

DetectorConstruction::~DetectorConstruction(){}

G4VPhysicalVolume* DetectorConstruction::Construct(){
  G4NistManager* nist = G4NistManager::Instance();
  G4Material* worldMat = nist->FindOrBuildMaterial("G4_AIR");
  G4Material* containerMat = nist->FindOrBuildMaterial("G4_WATER");

  // World
  G4double worldXYZ = 20.*cm;
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
  // Container
  G4Sphere* solidContainer = new G4Sphere("Container",
                                          1*cm, 8*cm,
                                          0*radian, 2*pi*radian,
                                          0*radian, 2*pi*radian);

  G4LogicalVolume* logicContainer = new G4LogicalVolume(solidContainer, containerMat, "Container");

  new G4PVPlacement(0,
                   G4ThreeVector(0, 0, 0),
                   logicContainer,
                   "Container",
                   logicWorld,
                   false,
                   0,
                   true);

  return physWorld;
}
