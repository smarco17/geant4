#include "ActionInitialization.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "EventAction.hh"
#include "SteppingAction.hh"

ActionInitialization::ActionInitialization():G4VUserActionInitialization(){}

ActionInitialization::~ActionInitialization(){}

void ActionInitialization::BuildForMaster() const{
  RunAction* runAction = new RunAction;
  SetUserAction(runAction);
}

void ActionInitialization::Build() const{
  SetUserAction(new PrimaryGeneratorAction);
  SetUserAction(new runAction);
  SetUserAction(new eventAction);
  SetUserAction(new SteppingAction(eventAction));
}  
