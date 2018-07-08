# Chapter 3. Toolkit Fundamentals
## 3.1 Class Categories and Domains
### 3.1.1 What is class category?
Geant4のような多規模なソフトウェアの設計において、より小さな「機能(logical units)」に分割することが重要である。可能な限り互いに独立して「機能」を実装してしまえば、深刻な障害なく並行して開発することができる。

オブジェクト指向分析と[Grady Booch](http://geant4.web.cern.ch/geant4/UserDocumentation/UsersGuides/ForApplicationDeveloper/html/bi01.html#biblio.booch1994)の設計方法論において、クラスカテゴリーは「機能」を生成するために使用されている。logical units は「それ自身を含むようなクラスの集団であり、他の集団と密接に関係している」と定義されている(例えば、"has-a" relationship)。しかし異なるクラスカテゴリーに属するクラス同士の関係は弱く、
