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
G4VUserPhysicsListは「必須のクラス」の基底クラスであり、
