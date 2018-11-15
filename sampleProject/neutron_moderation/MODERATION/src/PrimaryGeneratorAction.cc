#include "PrimaryGeneratorAction.hh"
#include "G4RunManager.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction(): G4VUserPrimaryGeneratorAction(), fParticleGun(0){
  G4int n_particle = 1;
  fParticleGun  = new G4ParticleGun(n_particle);

  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName;
  G4ParticleDefinition* particle = particleTable->FindParticle(particleName="neutron");
  
  fParticleGun->SetParticleDefinition(particle);
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0, 0, 1));
  fParticleGun->SetParticlePosition(G4ThreeVector(0, 0, 0));
  fParticleGun->SetParticleEnergy(2.*MeV);
}

PrimaryGeneratorAction::~PrimaryGeneratorAction(){
  delete fParticleGun;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent){
  fParticleGun->GeneratePrimaryVertex(anEvent);

  G4double directionX = G4UniformRand() * 2.0 - 1.0;
  G4double directionY = G4UniformRand() * 2.0 - 1.0;
  G4double directionZ = G4UniformRand() * 2.0 - 1.0;
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(directionX, directionY, directionZ));
}
