#include "RunAction.hh"
#include "PrimaryGeneratorAction.hh"
#include "DetectorConstruction.hh"
#include "Analysis.hh"

#include "G4RunManager.hh"
#include "G4Run.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

RunAction::RunAction() : G4UserRunAction(){
  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager->CreateH1("1", "X-ray energy spectrum", 500, 0., 100*keV);
}

RunAction::~RunAction(){
  delete G4AnalysisManager::Instance();
}

void RunAction::BeginOfRunAction(const G4Run*){
  G4RunManager::GetRunManager()->SetRandomNumberStore(false);

  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager->OpenFile("data.root");
}

void RunAction::EndOfRunAction(const G4Run* run){
  auto analysisManager = G4AnalysisManager::Instance();

  const PrimaryGeneratorAction* generatorAction
  = static_cast<const PrimaryGeneratorAction*>(G4RunManager::GetRunManager()->GetUserPrimaryGeneratorAction());

  G4String runCondition;
  if (generatorAction){
    const G4ParticleGun* particleGun = generatorAction->GetParticleGun();
    runCondition += particleGun->GetParticleDefinition()->GetParticleName();
    runCondition += " of ";
    G4double particleEnergy = particleGun->GetParticleEnergy();
    runCondition += G4BestUnit(particleEnergy, "Energy");
  }

  if (IsMaster()) G4cout << G4endl << "--------------------End of Global Run-----------------------";
  else G4cout << G4endl << "--------------------End of Local Run------------------------";

  analysisManager->Write();
  analysisManager->CloseFile();
}