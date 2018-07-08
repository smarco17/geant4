## 2.6.  How to Generate a Primary Event
### 2.6.1.  Generating Primary Events
G4VUserPrimaryGeneratorActionクラスはコンクリートクラスを継承可能な必須のクラスである。
コンクリートクラスにおいてどのように一次イベントが生成されるかを記述しなければならない。
一次粒子の実際の生成はG4VPrimaryGeneratorクラスのコンクリートクラスによってされる。
それを次の節で説明する。一次粒子を用意する方法を記したG4VUserPrimaryGenerationの  コンクリートクラスが生成された。

```C++
Example 2.18.  An example of a G4VUserPrimaryGeneratorAction concrete class using G4ParticleGun. For the usage of G4ParticleGun refer to the next subsection.

ExG4PrimaryGeneratorAction01.hh
#ifndef ExG4PrimaryGeneratorAction01_h
#define ExG4PrimaryGeneratorAction01_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ThreeVector.hh"
#include "globals.hh"

class G4ParticleGun;
class G4Event;

class ExG4PrimaryGeneratorAction01 : public G4VUserPrimaryGeneratorAction
{
  public:
    ExG4PrimaryGeneratorAction01(
      const G4String& particleName = "geantino",
      G4double energy = 1.*MeV,
      G4ThreeVector position= G4ThreeVector(0,0,0),
      G4ThreeVector momentumDirection = G4ThreeVector(0,0,1));    
    ~ExG4PrimaryGeneratorAction01();

    // methods
    virtual void GeneratePrimaries(G4Event*);

  private:
    // data members
    G4ParticleGun*  fParticleGun; //pointer a to G4 service class
};

#endif
// ExG4PrimaryGeneratorAction01.cc
#include "ExG4PrimaryGeneratorAction01.hh"

#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ExG4PrimaryGeneratorAction01::ExG4PrimaryGeneratorAction01(      
                                const G4String& particleName, 
                                G4double energy,
                                G4ThreeVector position, 
                                G4ThreeVector momentumDirection)
  : G4VUserPrimaryGeneratorAction(),
    fParticleGun(0)
{
  G4int nofParticles = 1;
  fParticleGun  = new G4ParticleGun(nofParticles);

  // default particle kinematic
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4ParticleDefinition* particle
    = particleTable->FindParticle(particleName);
  fParticleGun->SetParticleDefinition(particle);
  fParticleGun->SetParticleEnergy(energy);
  fParticleGun->SetParticlePosition(position);
  fParticleGun->SetParticleMomentumDirection(momentumDirection);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ExG4PrimaryGeneratorAction01::~ExG4PrimaryGeneratorAction01()
{
  delete fParticleGun;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ExG4PrimaryGeneratorAction01::GeneratePrimaries(G4Event* anEvent)
{
  // this function is called at the begining of event

  fParticleGun->GeneratePrimaryVertex(anEvent);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
```

#### 2.6.1.1. Selection of the generator
G4VUserPrimaryGeneratorActionのコンストラクタにおいて、初期生成器をインスタンス化する。もし必要であれば、生成器の初期条件を設定する必要がある。

例2.18において、G4ParticleGunは実際の粒子の生成器として使用するために構築されている。G4ParticleGunのメソッドは次節で詳述する。G4VUserPrimaryGeneratorActionにおいて生成した粒子生成器のオブジェクトはデストラクタで消去する必要があることに注意せよ。

#### 2.6.1.2. Generation of an Event
G4VUserPrimaryGenerationActionはgeneratePrimaries()という純粋仮想関数を持つ。このメソッドはそれぞれのイベントの最初に呼び出される。このメソッドでgeneratePrimaryVertex()メソッドを通してインスタンス化したG4VPrimaryGeneratorの具体的なクラスを呼び出さなければならない。

一つ以上の生成器、また一つの生成器を一度以上呼び出すこともできる。いくつかの生成器を組み合わせて使えば、より複雑な初期イベントを生成することができる。

### 2.6.2. G4VPrimaryGenerator
Geant4は3つのG4VPrimaryGeneratorのコンクリートクラスを提供する。これらのG4ParticleGunとG4GeneralParticleSourceの関係はここでまた議論するだろう。3つ目はG4HEPEvtInterfaceであり、それは3.6節で議論される。

#### 2.6.2.1. G4ParticleGun
G4ParticleGunはGeant4により提供される生成器である。このクラスはある運動量と方向をもった一次粒子を生成する。ランダムなソートは提供しない。G4ParticleGunのコンストラクタは

