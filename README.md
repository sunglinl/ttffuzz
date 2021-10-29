# TTFFuzz
TTFFuzz 实验版本基于项目 [FormatFuzzer](https://github.com/uds-se/FormatFuzzer) 和 [TinyAFL](https://github.com/linhlhq/TinyAFL)
对于 FormatFuzzer 的二次开发，主要支持结构树的解析和结构树生成 ttf 字体

## 实验版本说明

此版本主要提供于测试的ttf解析到结构树和通过结构树重新生成 ttf

稳定版本后续更新

## 项目的构建

```
mkdir build
cd build
cmake -G Xcode ..
cmake --build . --config Release

```
## 使用说明
```
-i in  -formatfuzztojc -T test.ttf -o out   -instrument_module  CoreText    -t 2000+ -m 800 -target_module  fuzzttf -target_method _fuzz  -nargs 1 -persist -iterations 5000 -loop -j ./in-ttfjc/test.ttf.jc  -J ./in-ttfjc/test2.ttf      -- ./fuzzttf @@

-T 输入需要解析的ttf字体

-j 输入结构树文件

-J 输出结构树生成的字体

-formatfuzztojc 控制结构树生成和解析
```

## 版权说明
TTFFuzz 是基于 Formatfuzzer 的二次开发

## Formatfuzzer 版权说明
[FormatFuzzer版权](https://github.com/uds-se/FormatFuzzer)



