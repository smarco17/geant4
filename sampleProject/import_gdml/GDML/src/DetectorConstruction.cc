#include "DetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
// #include "G4Box.hh"
// #include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "globals.hh"

// GDMLparserクラスのヘッダー
//
#include "G4GDMLParser.hh"

DetectorConstruction::DetectorConstruction():G4VUserDetectorConstruction(){}

DetectorConstruction::~DetectorConstruction(){}

G4VPhysicalVolume* DetectorConstruction::Construct(){
  // GDML形式のファイルをparseするためのparser
  // 
  G4GDMLParser parser;

  // solids.gdmlの読み込み
  parser.Read("solids.gdml", false);
  
  // parserからWorldを取得
  // このWorldには子要素の全てのボリュームの情報が記述されている
  // 
  G4VPhysicalVolume* physWorld = parser.GetWorldVolume();
  
  // Worldを返却
  // 
  return physWorld;
}
