## 2.4.  How to Specify Particles
G4VUserPhisicsListは2.1節で述べたように必須のユーザークラスの一つである。
このクラスではシミュレーションで用いられるすべての粒子と物理現象が定義されなければならない。
またこのクラスではカットオフパラメータも定義されなければならない。

ユーザーはG4VUserPhysicsListを継承し、以下の仮想関数を実装しなければならない。
```C++
ConstructParticle() //construct of particles  
ConstructProcess() //construct process and register them to particles  
```
ユーザーは次のデフォルトの仮想関数をオーバーライドしたいかもしれない。
```C++
SetCuts()
```
この節ではConstruct()とSetcuts()メソッドの簡単な例を示す。
ConstructPartcle()の情報は2.5節で紹介する。

### 2.4.1 Particle Definition
geant4ではシミュレーションにおいて様々な種類の粒子を提供する。

 > 電子やプロトンやガンマ線のような通常の粒子、電磁波  
 > ベクターメゾンやデルタバリオンのような寿命の短い共鳴粒子  
 > 重水素、アルファ粒子、重イオンのような核種  
 > クオーク、ダイクオーク、グルーオン  

それぞれの粒子は自身のクラスごとに代表され、G4ParicleDeifnitionクラスを継承する。
(例外：G4Ionsは全ての重粒子を表現する、詳しくは5.3節を見よ)
粒子は以下の6つのカテゴリーに分類される。

 > レプトン  
 > メゾン  
 > バリオン  
 > ボソン  
 > 短寿命  
 > イオン  

それぞれの粒子はディレクトリ /genat4/source/particle で定義されている。

#### 2.4.1.1 The G4ParticleDefinition Class
G4ParticleDefinitionクラスは名前、質量、電荷、スピン等の個々の粒子を特徴づけるプロパティを持っている。
これらのプロパティの多くは読み出し専用であり、直接書き換えることはできない。
G4ParticlePropertyTableクラスはG4ParticlePropertyDataからG4ParticlDefinitionの粒子の特性を引き出すために
用いられる。

#### 2.4.1.2 How to Access a Particle
それぞれの粒子のクラスのタイプは個々の粒子のタイプを表現するものであり、それぞれのクラスは一つのオブジェクトを持つ。
このオブジェクトはそれぞれのクラスのクラスメソッドを使うことでアクセスできる。
このルールには例外がある、5.3節を見よ。

例えばG4Electronクラスは電子を表現し、そのメンバーであるG4Electron::theInstance はそのオブジェクトのみを指す。
このオブジェクトへのポインタはクラスメソッドであるG4Electron::ElectronDefinition(), G4Electron::Definition()
を通して操作可能である。

標準で100種類以上の粒子が提供され、さまざまな物理現象の中で使われる。
それぞれの粒子クラスの固有オブジェクトは最初にポインタを得るためにクラスメソッドを呼び出すとき作成される。
粒子は動的なオブジェクトであり、物理現象の初期化時よりも前にインスタンスを生成するべきであるため、
プログラムの初期化ステップで要求されたすべての粒子クラスのクラスメソッドを例外的に呼び出さなければならない。

#### 2.4.1.3 Dictionary of particles
G4ParticleTableクラスは粒子を辞書として提供する。
以下のような便利なメソッドが提供されている。
```C++
FindParticle(G4String name);         // find the  particle by name  
FindParticle(G4int PDGencoding)      // find the particle by PDG encoding .  
```
G4ParticleDefinitionクラスはシングルトンオブジェクトとして定義され、G4ParitcleTable::GetParticleTable()メソッド
をそのポインタを提供する。
重イオンの場合、そのオブジェクトはユーザーとプロセスからの要求によって動的に生成される。
G4ParticleTableクラスは以下のようなイオンを生成するメソッドを提供する。
```C++
G4ParticleDefinition* GetIon(  G4int    atomicNumber,
                               G4int    atomicMass,
                               G4double   excitationEnergy);
```
粒子は構築の最中に自動的に登録される。ユーザーには粒子を登録すること以上のことをする権限はない。

#### 2.4.1.4 Constructing particle
ConstructParticle()はユーザーが要求するすべての粒子のクラスメソッドの中で呼び出されるべき純粋仮想関数である。
＊注意
ユーザーはシミュレーションで用いる重イオンを除く「全ての種類の粒子ついて」定義しなければならない。
全ての粒子とは一次粒子だけでなく、物理過程で生成される二次粒子も含む。

例として、プロトンとジアンティーノが必要であるとしよう。
ジアンティーノは全ての物質と相互作用しない仮想的な粒子である。
ConstructParticle()メソッドを以下のように実装する。
```C++
Example 2.14.  Construct a proton and a geantino.  
 void MyPhysicsList::ConstructParticle()  
 {   
   G4Proton::ProtonDefinition();  
   G4Geantino::GeantinoDefinition();  
 }  
```
geant4ではあまりにも多くの粒子が事前に定義されているため、このメソッドですべての粒子を定義するのは厄介である。
もしgeant4の粒子カテゴリーにおいてすべての粒子が欲しいならば、6つの便利なクラスがある。
 > G4BosonConstructor  
 > G4LeptonConstructor  
 > G4MesonConstructor  
 > G4BarionConstructor  
 > G4IonConstructor  
 > G4ShortlivedConstructor  

ExN05PhysicsListの一例は以下のようになっている。

```C++
Example 2.15.  Construct all leptons.  
void ExN05PhysicsList::ConstructLeptons()  
{  
  // Construct all leptons  
  G4LeptonConstructor pConstructor;  
  pConstructor.ConstructParticle();  
}  
```
### 2.4.2 Range Cuts
赤外発散を避けるため、いくつかの電磁気的な過程では二次粒子が生成されない閾値が求められる。
この要求のため、ガンマ線、電子、ポジトロンは閾値を要求される。
この閾値は距離またはカットオフレンジとして定義されなければならず、個々の物質で内部的にエネルギーへ変換される。
閾値のレンジは初期化段階でG4VUserPhysicsListクラスのSetCuts()メソッドを用いて定義しなければならない。
5.5節ではそれらについて詳細を記述する。

#### 2.4.2.1 Setting the cuts
閾値の生成はG4VUserPhysicsListクラスの仮想関数であるSetCuts()で定義される。
粒子、物質のプロセスの生成は、SetCuts()の呼び出しにの下で実行される。G4RunManagerは通常のアプリケーションの一連の流れをアン利するものである。

このレンジカットはそれぞれの物質・粒子に対してスレッショルドエネルギーに変換されるため、スレッショルドエネルギーを持つ粒子は、レンジカット距離移動したのちに止まる（または破棄される）。スレッショルドエネルギーは簡単な計算式によって計算されている。

上限は10GeVに設定されているのに注意せよ。もし、それよりも高いエネルギーに設定したいのなら、/cuts/setMaxCutEnergy のUIコマンドで変更できる。

「レンジ固有のカット値」という考え方は、Geant4の重要な特徴の一つであり、カット値をコヒーレントな手法で取り扱うために使用されている。多くのアプリケーションにとってユーザーはただ一つのカット値を設定すればよく、ガンマ線・電子・ポジトロン・プロトンに対してのみ適用すればよい。

SetCuts()メソッドのデフォルトの機能は、すべての粒子の種類に固有のレンジカットオフ値として、defaultCutValueを提供する。このdefaultCutValueはデフォルトで1.0mmに設定されている。ユーザーはSetDefaultValue()によって変更することができる。UIコマンドの/run/setCutではインタラクティブに変更することができる。

注意:イベントループの最中に変更してはならない。しかしランの間には変更できるだろう。

またガンマ線、電子・陽電子に対して SetCutValue()メソッドによって異なる異なるレンジカットを設定することも可能である。(UIコマンドでは、/run/setCutForAGivenParticle コマンドで設定可能である。)しかし、ユーザーは結果のアウトプット（特にエネルギ－損失）に注意しなければならない、なぜならGeant4プロセスは「レンジ固有のカット値」の考えの下で設計されているからである。

Geant4のバージョン5.1から、幾何学的な領域に対してもスレッショルド値を定義することができるようになった。この新しい機能は5.5節で詳述する。
