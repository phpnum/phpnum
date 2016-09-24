# phpnum

[![Build Status](https://travis-ci.org/phpnum/phpnum.svg?branch=master)](https://travis-ci.org/phpnum/phpnum)

PHP科学计算扩展。灵感源自 [NumPy](https://github.com/numpy/numpy) & [NumPHP](https://github.com/NumPHP/NumPHP)。



# 文档目录
-----
1. [安装/配置](#installingconfiguring)
   * [需求](#requirement)
   * [安装](#installation)
2. [类和方法](#classes-and-methods)
   * [基本用法](#usage)
   * [属性](#characteristics)
   * [运算](#arithmetic-operations)
   * [统计](#statistics)

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

# 类和方法

-----

## 基本用法

1. [Num类](#class-num) - 创建Num对象
2. [NumNdarray类](#class-numndarray) - 创建N维数组对象
3. [打印输出](#printing) - 输出N维数组对象

### Class Num
-----
_**Description**_: 创建Num对象

##### *Example*

~~~
$num = new Num();
~~~

### Class NumNdarray
-----
_**Description**_: 创建N维数组对象

##### *Parameters*
array: *Array*

##### *Return value*

ndarray: *Object*

##### *Example*

~~~
$num = new Num();
$ndarray = $num->array([[1.0, 2, 3], [2, 3, 4]]);
~~~
### Printing
-----
_**Description**_: 输出N维数组对象

##### *Example*

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

1. [getData](#getdata) - 获取N维数组的原始数据
2. [getShape](#getshape) - 获取N维数组的各维度大小
3. [getNdim](#getndim) - 获取N维数组的维度
4. [getSize](#getsize) - 获取N维数组的元素个数

### getData
-----
_**Description**_: 获取N维数组的原始数据

##### *Parameters*
None

##### *Return value*
data: *Array*

##### *Example*

~~~
$num = new Num();
$ndarray = $num->array([[1.0, 2, 3], [2, 3, 4]]);
$ndarray->getData(); // returns array(array(1.0, 2, 3), array(2, 3, 4))
~~~

### getShape
-----
_**Description**_: 获取N维数组的各维度大小

##### *Parameters*
None

##### *Return value*
shape: *Array*

##### *Example*

~~~
$num = new Num();
$ndarray = $num->array([[1.0, 2, 3], [2, 3, 4]]);
$ndarray->getShape(); // returns array(2, 3)
~~~

### getNdim
-----
_**Description**_: 获取N维数组的维度

##### *Parameters*
None

##### *Return value*
ndim: *LONG*

##### *Example*

~~~
$num = new Num();
$ndarray = $num->array([[1.0, 2, 3], [2, 3, 4]]);
$ndarray->getNdim(); // returns 2
~~~

### getSize
-----
_**Description**_: 获取N维数组的元素个数

##### *Parameters*
None

##### *Return value*
size: *LONG*

##### *Example*

~~~
$num = new Num();
$ndarray = $num->array([[1.0, 2, 3], [2, 3, 4]]);
$ndarray->getSize(); // returns 6
~~~



## 运算

1. [add](#add) - 加上N维数组
2. [sub](#sub) - 减去N维数组
3. [mult](#mult) - 乘以N维数组
4. [div](#div) - 除以N维数组

### add
-----
_**Description**_: 加上N维数组

##### *Parameters*
ndarray: *Object*

##### *Return value*
ndarray: *Object*

##### *Example*

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
_**Description**_: 减去N维数组

##### *Parameters*
ndarray: *Object*

##### *Return value*
ndarray: *Object*

##### *Example*

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
_**Description**_: 乘以N维数组

##### *Parameters*
ndarray: *Object*

##### *Return value*
ndarray: *Object*

##### *Example*

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
_**Description**_: 除以N维数组

##### *Parameters*
ndarray: *Object*

##### *Return value*
ndarray: *Object*

##### *Example*

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

1. [amin](#amin) - 获取N维数组的最小元素
2. [amax](#amin) - 获取N维数组的最大元素

### amin
-----
_**Description**_: 获取N维数组的最小元素

##### *Parameters*
ndarray: *Object*

##### *Return value*
amin: *Double*

##### *Example*

~~~
$num = new Num();
$ndarray = $num->array([[3.2, 1.5, 1], [2.5, 4, 2]]);
$num->min($ndarray); // returns 1
~~~

### amax
-----
_**Description**_: 获取N维数组的最大元素

##### *Parameters*
ndarray: *Object*

##### *Return value*
amax: *Double*

##### *Example*

~~~
$num = new Num();
$ndarray = $num->array([[3.2, 1.5, 1], [2.5, 4, 2]]);
$num->amax($ndarray); // returns 4
~~~