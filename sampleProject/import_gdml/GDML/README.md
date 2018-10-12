# import_gdml

  ***
  このファイルと同じ階層にあるsolids.gdmlがGDML形式のファイルでジオメトリが記述されている。
  ジオメトリは原点を中心とした一辺10[cm]の立方体の空気で満たされた世界に、1[cm]四方の水のボックスが置かれているのみである。
  ***
  
  ***
  使用方法

  ``` shell
  > mkdir GDML-build
  > cd GDML-build
  > cmake -DGeant4_DIR=/xxx/xxx/xxx ../GDML
  ...
  > make -jN
  ...
  > ./gdml run.mac
  ...

  or
  
  > ./gdml
  Idle> /run/beamOn 10
  ...
  
  ```

  ***
