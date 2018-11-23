#include "DetectorConstruction.hh"
#include "ActionInitialization.hh"
#include "PhysicsList.hh"

#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"
#else
#include "G4RunManager.hh"
#endif

#include "G4UImanager.hh"
#include "FTFP_BERT.hh"
#include "G4StepLimiterPhysics.hh"

#include "Randomize.hh"

#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

int main(int argc, char** argv){
  G4UIExecutive* ui = 0;
  if(argc == 1) ui = new G4UIExecutive(argc, argv);

  G4Random::setTheEngine(new CLHEP::RanecuEngine);

#ifdef G4MULTITHREADED  
  G4MTRunManager* runManager = new G4MTRunManager;
#else
  G4RunManager* runManager = new G4RunManager;
#endif

  runManager->SetUserInitialization(new DetectorConstruction());

  // G4VModularPhysicsList* physicsList = new FTFP_BERT;
  // physicsList->RegisterPhysics(new G4StepLimiterPhysics());
  // runManager->SetUserInitialization(physicsList);
  runManager->SetUserInitialization(new PhysicsList());
    
  runManager->SetUserInitialization(new ActionInitialization());
  
  G4VisManager* visManager = new G4VisExecutive;
  
  visManager->Initialize();
  G4UImanager* UImanager = G4UImanager::GetUIpointer();
  if(!ui){ 
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    UImanager->ApplyCommand(command + fileName);
  }else{ 
    UImanager->ApplyCommand("/control/execute init_vis.mac");
    /*
    if (ui->IsGUI()) {
      UImanager->ApplyCommand("/control/execute init_vis.mac");
    }
    */

  ui->SessionStart();
  delete ui;
  }

  delete visManager;
  delete runManager;
}