#ifndef PhysicsList_h
#define PhysicsList_h 1

#include "G4VModularPhysicsList.hh"

class PhysicsList: public G4VModularPhysicsList{
public:
  PhysicsList();
  virtual ~PhysicsList();
  virtual void SetCuts();
};

#endif
