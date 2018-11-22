#include "ActionInitialization.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "RunAction.hh"

ActionInitialization::ActionInitialization():G4VUserActionInitialization(){}

ActionInitialization::~ActionInitialization(){}

void ActionInitialization::BuildForMaster() const{
  RunAction* runAction = new RunAction;
  SetUserAction(runAction);
}

void ActionInitialization::Build() const{
  SetUserAction(new PrimaryGeneratorAction);
  
  RunAction* runAction = new RunAction;
  SetUserAction(runAction);
}  
