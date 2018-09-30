#include "RunAction.hh"
#include "PrimaryGeneratorAction.hh"
#include "DetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4Run.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

RunAction::RunAction():G4UserRunAction(){}

RunAction::~RunAction(){}

void RunAction::BeginOfRunAction(const G4Run*){
  // inform the runManager to save random number seed
  G4RunManager::GetRunManager()->SetRandomNumberStore(false);
}

void RunAction::EndOfRunAction(const G4Run* run){
  // Run conditions
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

  // Print
  if (IsMaster()) G4cout << G4endl << "--------------------End of Global Run-----------------------";
  else G4cout << G4endl << "--------------------End of Local Run------------------------";
}