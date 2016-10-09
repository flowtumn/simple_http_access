# simple_http_access
ログインを必要とするページを含め、それらのページにアクセスし結果を出力するプログラムです。

## build

```
git clone <this repository>
cd simple_http_access
mkdir out
cd out
cmake -DCMAKE_MODULE_PATH=../Cmake -DBOOST_ROOT=<boost_root_directory> -DBOOST_LIBRARYDIR=<boost_library_directory> -DDLIBRESSL_ROOT=<libressl_root_directory> ../
```
