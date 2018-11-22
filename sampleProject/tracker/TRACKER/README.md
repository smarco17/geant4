# template
  
  ***
  使用方法

  ``` shell
  > mkdir TRACKER-build
  > cd TRACKER-build
  > cmake -DGeant4_DIR=/xxx/xxx/xxx ../TRACKER
  ...
  > make -jN
  ...
  > ./TRACKER run.mac
  ...

  or
  
  > ./TRACKER
  Idle> /run/beamOn 10000
  ...

  and

  > root -l data.C
  
  ```

  ***
