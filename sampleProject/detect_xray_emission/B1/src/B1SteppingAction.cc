//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
// $Id: B1SteppingAction.cc 74483 2013-10-09 13:37:06Z gcosmo $
//
/// \file B1SteppingAction.cc
/// \brief Implementation of the B1SteppingAction class

#include "B1SteppingAction.hh"
#include "B1EventAction.hh"
#include "B1DetectorConstruction.hh"
#include "B1Analysis.hh"

#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"

#include "G4UnitsTable.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1SteppingAction::B1SteppingAction(B1EventAction* eventAction)
: G4UserSteppingAction(),
  fEventAction(eventAction),
  fScoringVolume(0)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1SteppingAction::~B1SteppingAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1SteppingAction::UserSteppingAction(const G4Step* step)
{
  auto analysisManager = G4AnalysisManager::Instance();
  //scoring volumeが定義されていない場合、改めて定義しなおす。
  //
  if (!fScoringVolume) {
    const B1DetectorConstruction* detectorConstruction
      = static_cast<const B1DetectorConstruction*>
        (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
    fScoringVolume = detectorConstruction->GetScoringVolume();
  }

  // get volume of the current step
  // ターゲーットに設定したボリュームとステップで取得したボリュームが
  // 異なる場合、エネルギーをカウントしない。
  //
  G4LogicalVolume* volume
    = step->GetPreStepPoint()->GetTouchableHandle()
      ->GetVolume()->GetLogicalVolume();

  // check if we are in scoring volume
  if (volume != fScoringVolume) return;

  G4String gamma = "gamma";
  G4String proton = "proton";
  // collect energy deposited in this step
  // G4double edepStep = step->GetTotalEnergyDeposit();
  // ステップからプリステップを経て、検出領域前面での運動エネルギーを取得する。
  //
  G4double edepStep = step->GetPreStepPoint()->GetKineticEnergy();
  G4cout << "-----Information-----" << G4endl;
  G4cout << "Type   - "
  // 粒子の名前を取得
  //
         << step->GetTrack()->GetDynamicParticle()->GetDefinition()->GetParticleName() << G4endl;
  G4cout << "Energy - "
  // G4BestUnitは適当な単位をつけてくれる。
  //
         << G4BestUnit(edepStep,"Energy") << G4endl;
  G4cout << "---------------------" << G4endl;
  fEventAction->AddEdep(edepStep);
  // id=0, 1 にデータをfill
  //
  if (step->GetTrack()->GetDynamicParticle()->GetDefinition()->GetParticleName() == gamma){
    // 粒子の名前がガンマ線だったら
    // 
    analysisManager->FillH1(0, edepStep);
  }else if(step->GetTrack()->GetDynamicParticle()->GetDefinition()->GetParticleName() == proton){
    // 粒子の名前が陽子だったら
    //
    analysisManager->FillH1(1, edepStep);
  }else{

  }

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
