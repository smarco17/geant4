
#include "B1PhysicsList.hh"

#include "G4DecayPhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"
#include "G4EmStandardPhysics.hh"
#include "G4EmLowEPPhysics.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1PhysicsList::B1PhysicsList()
: G4VModularPhysicsList(){
  SetVerboseLevel(1);

  // Default physics
  RegisterPhysics(new G4DecayPhysics());

  // Radioactive decay
  RegisterPhysics(new G4RadioactiveDecayPhysics());

  // EM physics
  RegisterPhysics(new G4EmStandardPhysics());
  // RegisterPhysics(new G4EmLowEPPhysics());

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1PhysicsList::~B1PhysicsList()
{
  //
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1PhysicsList::SetCuts()
{
  G4VUserPhysicsList::SetCuts();
}
