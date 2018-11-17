#include "SteppingAction.hh"
#include "EventAction.hh"
#include "Analysis.hh"
#include "DetectorConstruction.hh"
#include "G4Step.hh"

#include "G4LogicalVolume.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"

SteppingAction::SteppingAction(EventAction* eventAction):G4UserSteppingAction(){}

SteppingAction::~SteppingAction(){}

void SteppingAction::UserSteppingAction(const G4Step* step){
  auto analysisManager = G4AnalysisManager::Instance();

  if (!fDetector) {
    const DetectorConstruction* detectorConstruction
      = static_cast<const DetectorConstruction*>
        (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
    fDetector = detectorConstruction->GetDetector();
  }
  
  G4LogicalVolume* preStepVolume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();
  
  if(preStepVolume != fDetector) return;

  G4String particleName = step->GetTrack()->GetDynamicParticle()->GetDefinition()->GetParticleName();
  if(particleName == "gamma"){
    G4double eStep = step->GetPreStepPoint()->GetKineticEnergy();
    analysisManager->FillH1(0, eStep);
    G4cout << particleName << " --- " << G4BestUnit(eStep, "Energy") << G4endl;
  }
}

