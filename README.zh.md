# phpnum

[![Build Status](https://travis-ci.org/phpnum/phpnum.svg?branch=master)](https://travis-ci.org/phpnum/phpnum)

PHP科学计算扩展。灵感源自 [NumPy](https://github.com/numpy/numpy) & [NumPHP](https://github.com/NumPHP/NumPHP)。



# 文档目录
-----
1. [安装/配置](#安装配置)
   * [需求](#需求)
   * [安装](#安装)
2. [类与方法](#类与方法)
   * [基本用法](#基本用法)
   * [属性](#属性)
   * [运算](#运算)
   * [统计](#统计)

-----

# 安装/配置
-----

## 需求
- PHP 7 +

## 安装

下载phpnum最新版本，解压缩后，进入phpnum源码目录, 依次执行（其中PHP_BIN是PHP的bin目录）
~~~
$PHP_BIN/phpize
./configure --with-php-config=$PHP_BIN/php-config
make && make install
~~~

在php.ini中载入num.so，重启PHP。

# 类与方法

-----

## 基本用法

1. [Class Num](#class-num) - 创建Num对象
2. [Class NumNdarray](#class-numndarray) - 创建数组对象
3. [Printing](#printing) - 输出数组对象

### Class Num
-----
_**说明**_: 创建Num对象

##### *范例*

~~~
$num = new Num();
~~~

### Class NumNdarray
-----
_**说明**_: 创建数组对象

##### *参数*
array: *Array*

##### *返回值*

ndarray: *Object*

##### *范例*

~~~
$num = new Num();
$ndarray = $num->array([[1.0, 2, 3], [2, 3, 4]]);
~~~
### Printing
-----
_**说明**_: 输出数组对象

##### *范例*

~~~
$num = new Num();
$ndarray = $num->array([[1.0, 2, 3], [2, 3, 4]]);
echo $ndarray;
/* output: 
array([
  [1,2,3],
  [2,3,4]
])
*/
~~~



## 属性

1. [getData](#getdata) - 获取数组对象的原始数据
2. [getShape](#getshape) - 获取数组对象的各维度大小
3. [getNdim](#getndim) - 获取数组对象的维度
4. [getSize](#getsize) - 获取数组对象的元素个数

### getData
-----
_**说明**_: 获取数组对象的原始数据

##### *参数*
None

##### *返回值*
data: *Array*

##### *范例*

~~~
$num = new Num();
$ndarray = $num->array([[1.0, 2, 3], [2, 3, 4]]);
$ndarray->getData(); // returns array(array(1.0, 2, 3), array(2, 3, 4))
~~~

### getShape
-----
_**说明**_: 获取数组对象的各维度大小

##### *参数*
None

##### *返回值*
shape: *Array*

##### *范例*

~~~
$num = new Num();
$ndarray = $num->array([[1.0, 2, 3], [2, 3, 4]]);
$ndarray->getShape(); // returns array(2, 3)
~~~

### getNdim
-----
_**说明**_: 获取数组对象的维度

##### *参数*
None

##### *返回值*
ndim: *LONG*

##### *范例*

~~~
$num = new Num();
$ndarray = $num->array([[1.0, 2, 3], [2, 3, 4]]);
$ndarray->getNdim(); // returns 2
~~~

### getSize
-----
_**说明**_: 获取数组对象的元素个数

##### *参数*
None

##### *返回值*
size: *LONG*

##### *范例*

~~~
$num = new Num();
$ndarray = $num->array([[1.0, 2, 3], [2, 3, 4]]);
$ndarray->getSize(); // returns 6
~~~



## 运算

1. [add](#add) - 加上数组对象
2. [sub](#sub) - 减去数组对象
3. [mult](#mult) - 乘以数组对象
4. [div](#div) - 除以数组对象

### add
-----
_**说明**_: 加上数组对象

##### *参数*
ndarray: *Object*

##### *返回值*
ndarray: *Object*

##### *范例*

~~~
$num = new Num();
$a = $num->array([[1.0, 2, 3], [2, 3, 4]]);
$b = $num->array([[3.2, 1.5, 1], [2.5, 4, 2]]);
echo $a->add($b);
/* output:
array([
  [4.2,3.5,4],
  [4.5,7,6]
])
*/
~~~

### sub
-----
_**说明**_: 减去数组对象

##### *参数*
ndarray: *Object*

##### *返回值*
ndarray: *Object*

##### *范例*

~~~
$num = new Num();
$a = $num->array([[1.0, 2, 3], [2, 3, 4]]);
$b = $num->array([[3.2, 1.5, 1], [2.5, 4, 2]]);
echo $a->sub($b);
/* output:
array([
  [-2.2,0.5,2],
  [-0.5,-1,2]
])
*/
~~~

### mult
-----
_**说明**_: 乘以数组对象

##### *参数*
ndarray: *Object*

##### *返回值*
ndarray: *Object*

##### *范例*

~~~
$num = new Num();
$a = $num->array([[1.0, 2, 3], [2, 3, 4]]);
$b = $num->array([[3.2, 1.5, 1], [2.5, 4, 2]]);
echo $a->mult($b);
/* output:
array([
  [3.2,3,3],
  [5,12,8]
])
*/
~~~

### div
-----
_**说明**_: 除以数组对象

##### *参数*
ndarray: *Object*

##### *返回值*
ndarray: *Object*

##### *范例*

~~~
$num = new Num();
$a = $num->array([[1.0, 2, 3], [2, 3, 4]]);
$b = $num->array([[3.2, 1.5, 1], [2.5, 4, 2]]);
echo $a->div($b);
/* output:
array([
  [0.3125,1.3333333333333,3],
  [0.8,0.75,2]
])
*/
~~~



## 统计

1. [amin](#amin) - 获取数组对象的最小元素
2. [amax](#amin) - 获取数组对象的最大元素

### amin
-----
_**说明**_: 获取数组对象的最小元素

##### *参数*
ndarray: *Object*

##### *返回值*
amin: *Double*

##### *范例*

~~~
$num = new Num();
$ndarray = $num->array([[3.2, 1.5, 1], [2.5, 4, 2]]);
$num->min($ndarray); // returns 1
~~~

### amax
-----
_**说明**_: 获取数组对象的最大元素

##### *参数*
ndarray: *Object*

##### *返回值*
amax: *Double*

##### *范例*

~~~
$num = new Num();
$ndarray = $num->array([[3.2, 1.5, 1], [2.5, 4, 2]]);
$num->amax($ndarray); // returns 4
~~~