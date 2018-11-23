#ifndef PhysicsList_h
#define PhysicsList_h 1

#include "G4VUserPhysicsList.hh"

class PhysicsList: public G4VUserPhysicsList{
public:
  PhysicsList();
  ~PhysicsList();

  void ConstructParticle();
  void ConstructProcess();
  void SetCuts();
};

#endif
