# sample

## import_gdml

   Geometry Description Markup Language(GDML)によってジオメトリを記述し、それをGeant4のシミュレーションの世界へ
   組み込むためプログラム。
   templateプログラムを基本としているため、相互作用は行わないが、正しく輸送が行われていることを確認することは重要である。
   ***

## template

   空気で満たしたWorldへGeantino(相互作用しない、輸送のみ考慮された仮想粒子)を打ち込むだけの最小のプログラム。
   すべてはここから。
   ***

## neutron_moderation

   中性子が水によって減速される様子をみるため"だけ"のプログラム。
   ***

## x-ray_detection

   ターゲットにX線を照射し、ターゲットから発生するX線を"検出器"によって検出する。
   またそのエネルギースペクトルを「ROOT」によってグラフにする。
   ***