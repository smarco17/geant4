#include "EventAction.hh"
#include "RunAction.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"

EventAction::EventAction(RunAction* runAction): G4UserEventAction(), fRunAction(runAction){}

EventAction::~EventAction(){}

void EventAction::BeginOfEventAction(const G4Event*){}

void B1EventAction::EndOfEventAction(const G4Event*){}
