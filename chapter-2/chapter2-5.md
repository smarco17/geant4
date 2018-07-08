## 2.5. How To Specify Physics Processes
### 2.5.1 Physics Processes
物理的なプロセスは粒子がどのように物質と相互作用するかを記述する。Geant4は大きく分けて7つのプロセスを提供する。
 > 電磁気学的  
 > ハドロン  
 > 輸送  
 > 崩壊  
 > 光学的  
 > 光レプトン  
 > パラメータ表示  

 全ての物理プロセスは基底クラスであるG4VProcessを継承している。それらの仮想関数
-   AtRestDoIt
-   AlongStepDoIt
-   PostStepDoIt

とそれと対応する関数
-   AtRestGetPhysicalInteractionLength
-   AlongStepGetPhysicalInteractionLength
-   PostStepGetPhysicalInteractionLength

は継承されたクラスを実装するときに物理的なプロセスの振る舞いを記述する。これらの関数の詳細は5.2節で詳述する。

以下は簡素なプロセスのために使用されるスーパークラスである。
-   G4VAtRestProcess  
  Processes with only AtRestDoIt  
-   G4VContinuousProcess  
  Processes with only AlongStepDoIt  
-   G4VDiscreteProcess  

G4VContinuousDicreteProcessのような他の4つの仮想クラスが複雑なプロセスのために提供されている。

### 2.5.2. Managing Processes
G4ProcessManagerクラスは粒子が引き受けることのできるプロセスのリストを含んでいる。それはリストにおけるそれぞれのプロセスで有効であるDoIt関数のような、プロセスの呼び出し命令時に情報を持っている。G4ProcessManagerオブジェクトはそれぞれの粒子に付随し、G4ParticleDefinitionクラスに張り付く。

プロセスを有効にするために、それらは粒子のG4ProcessManagerに登録される。プロセス実行時の情報はAddProcess()とSetProcessOrdering()メソッドを使うことでインクルードされる。簡素なプロセスの登録のために、AddAtRestProcess(), AddContinuousProcess(), AddDiscreteProcess()メソッドは使われるだろう。

G4ProcessManagerはActiveProcess()とInActiveProcess()を使うことでランの最中にいくつかのプロセスをオン・オフにすることでできる。これらのメソッドはプロセスの登録を終えた後にのみ有効になるため、PreInitフェーズで使うことはできない。

G4VUserPhysicsListクラスは、G4ProcessManagerオブジェクトを生成し、ConstructParticle()メソッドの中で定義される全ての粒子のクラスに対して紐づける。

### 2.5.3. Specifying Physics Processes
G4VUserPhysicsListは「必須のクラス」の基底クラスであり(2.1節を見よ)、シミュレーションで求められるすべての粒子と物理プロセスは登録されなければならない。ユーザーはG4VUserPhysicsListを継承したクラスを作成し、純粋仮想関数であるConstructProcess()を実装しなければならない。

例として、もしただG4Geantinoという粒子のクラスが必要で輸送のプロセスのみが必要であるとする。COnstructProcess()メソッドは以下のように記述されるだろう。
```C++
Example 2.16.  Register processes for a geantino.

  void MyPhysicsList::ConstructProcess()
  {
    // Define transportation process
    AddTransportation();
  }
```

ここで、AddTransportation()メソッドはすべての粒子のクラスについてG4Transporationクラスを登録するためにG4VUserPhysicsListクラスが提供されている。G4Transportationクラス（とあるいはその関連のクラス）は時空間における粒子の移動を記述する。それは粒子を追跡するのに必須なクラスである。

COnstructProcess()メソッドでは、物理的なプロセスがG4ProcessManagerのそれぞれの粒子インスタンスに登録されなければならない。

プロセスの登録の一例は、G4VUserPhysicsList::AddTransportation()メソッドで与えられる。

G4ProcessManageへの登録は他のプロセスと粒子にとって複雑な手続きである、それはプロセス間の関係はいくつかのプロセスにとって重要である。登録手続きを簡略にするためにG4PhysicsListHelperが提供されている。ユーザーはプロセスの種類(すなわち、AtRest, Discrete, Continuous)もしくは命令のパラメータを気にする必要がない。

ガンマ線の電磁気学的なプロセスの一例を以下に示す。
```C++
Example 2.17.  Register processes for a gamma.

void MyPhysicsList::ConstructProcess()
{
  // Define transportation process
  AddTransportation();
  // electromagnetic processes
  ConstructEM();
}

void MyPhysicsList::ConstructEM()
{
  // Get pointer to G4PhysicsListHelper
  G4PhysicsListHelper* ph = G4PhysicsListHelper::GetPhysicsListHelper();

  //  Get pointer to gamma
  G4ParticleDefinition* particle = G4Gamma::GammaDefinition();

  // Construct and register processes for gamma
  ph->RegisterProcess(new G4PhotoElectricEffect(), particle);
  ph->RegisterProcess(new G4ComptonScattering(), particle);
  ph->RegisterProcess(new G4GammaConversion(), particle);
  ph->RegisterProcess(new G4RayleighScattering(), particle);
}
```
