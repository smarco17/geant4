#include "SteppingAction.hh"
#include "EventAction.hh"

#include "G4Step.hh"


SteppingAction::SteppingAction(EventAction* eventAction):G4UserSteppingAction(){}

SteppingAction::~SteppingAction(){}

void SteppingAction::UserSteppingAction(const G4Step* step){}

