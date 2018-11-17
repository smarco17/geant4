#include "DetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "globals.hh"

#include "G4GDMLParser.hh"

DetectorConstruction::DetectorConstruction():G4VUserDetectorConstruction(){}

DetectorConstruction::~DetectorConstruction(){}

G4VPhysicalVolume* DetectorConstruction::Construct(){
  G4GDMLParser parser;
  parser.Read("solids.gdml", false);
  
  G4VPhysicalVolume* physWorld = parser.GetWorldVolume();  
  
  return physWorld;
}
