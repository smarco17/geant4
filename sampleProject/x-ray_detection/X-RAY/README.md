# template
  
  ***
  使用方法

  ``` shell
  > mkdir X-RAY-build
  > cd X-RAY-build
  > cmake -DGeant4_DIR=/xxx/xxx/xxx ../X-RAY
  ...
  > make -jN
  ...
  > ./X-RAY run.mac
  ...

  or
  
  > ./X-RAY
  Idle> /run/beamOn 10000
  ...

  and

  > root -l data.C
  
  ```

  ***
