## 9.2 Analysis Manager Classes
分析マネージャークラスはg4toolsへの単一のインターフェースを提供し、サポートされた形式(ROOT, AIDA XML, CSV)でのg4toolsの使用方法の差異をなくしている。

分析マネジャークラスはそれぞれのサポートされた出力形式で利用可能である。

- G4CsvAnalysisManager
- G4RootAnalysisManager
- G4XmlAnalysisManager

使用の簡単のため、それぞれの分析マネジャーは全ての機能への完全なアクセスを提供する。そのためより複雑な設計を通してそれは実装されている。

マネージャークラスはシングルトンで設計されている。ユーザーのコードは希望するマネージャーの唯一のインスタンスへのポインタへアクセスすることになるだろう。そのマネージャーはユーザーのコードから生成・消去する必要がある。すべてのオブジェクトは分析マネジャーを通じて生成され、マネージャーによって自動的に消去されている。g4tollsのオブジェクトと同様に分析マネージャーの具体的なタイプは専用のインクルードファイルをインクルードすることで選択された名前空間に隠されている。このことは以下の一般的な種類を通じ、ユーザーに全ての出力技術を使用することを可能にしている。

- G4AnalysisManger: the public analysis interface
- G4AnaH1[2,3]: one[two,three]-dimensional histogram
- G4AnaP1[2]: one[two]-dimensional profile
- G4Ntuple: ntuple

G4AnalysisManagerの機能に加え、ヒストグラムの生成やそれらのプロパティを決めるためのGeant4UIコマンドも実装されている。

### 9.2.1 Analysis Manager
Geant4で解析をするためには、分析マネージャのインスタンスを生成しなければならない。分析マネージャーのオブジェクトはG4AnalysisManager::Instance()の最初の呼び出しによって生成され、次の呼び出しで分析マネージャーのオブジェクトへのポインタを提供する。クライアントのコードは、私たちの例のRunActionのデストラクタおいてされていること、すなわちオブジェクトの消去に対して責任を負う。

basic 例B4から抜粋した分析マネージャーの生成のコードの一例を以下に示す。
```C++
#include "B4Analysis.hh"  
>   
> B4RunAction::B4RunAction()  
>  : G4UserRunAction()  
> {  
// Create analysis manager  
auto analysisManager = G4AnalysisanalysisManagerager::Instance();  
analysisManager->SetVerboseLevel(1);  
analysisManager->SetFirstHistoId(1);  
}
B4RunAction::~B4RunAction()
{
delete G4AnalysisManager::Instance();  
}
```
必須ではないが、分析マネージャーをユーザーのRunActionのコンストラクタで生成し、デストラクタで消去することをお勧めする。このことはマルチスレッドでのシミュレーションの振る舞いを保証するものである。出力形式の選択が行われているB4Analysis.hhにおいて、出力形式の特定のコードは隠されている。

```C++
#ifndef B4Analysis_h  
#define B4Analysis_h 1  
#include "g4root.hh"  
//#include "g4xml.hh"  
//#include "g4csv.hh"  
#endif  
```
情報の表示のレベルは、SetVerboseLevel(G4 int)によって設定することができる。デフォルトは0で4までサポートされている。

詳細のレベルはUIコマンドを通じても設定することができる。

### 9.2.2. Files handling
分析マネージャーは一度に位置ファイルしか取り扱うことができない。以下にbasicの例B4から抜粋されたファイルをオープニング、クロージングする一例を示す。
```C++
#include "B4Analysis.hh"  
void B4RunAction::BeginOfRunAction(const G4Run* run)  
{  
// Get analysis manager  
auto analysisManager = G4AnalysisanalysisManagerager::Instance();  
// Open an output file  
analysisManager->OpenFile("B4");  
}  
void B4RunAction::EndOfRunAction(const G4Run* aRun)  
{  
// Save histograms  
auto analysisManager = G4AnalysisanalysisManagerager::Instance();  
analysisManager->Write();  
analysisManager->CloseFile();  
}  

```
