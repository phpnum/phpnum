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
   * [统计](#统计)
   * [算数运算](#算数运算)
   * [数学计算](#数学计算)

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




## 算数运算

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



## 数学计算

1. [power](#power) - 遍历计算次幂
2. [square](#square) - 遍历计算平方
3. [sqrt](#sqrt) - 遍历计算平方根
4. [exp](#exp) - 遍历计算自然常数e的次幂
5. [log](#log) - 遍历计算自然对数
6. [sin](#sin) - 遍历计算正弦值
7. [cos](#cos) - 遍历计算余弦值
8. [tan](#tan) - 遍历计算正切值
9. [ceil](#ceil) - 遍历计算向上取整
10. [floor](#floor) - 遍历计算向下取整

### power

------

_**说明**_: 遍历计算次幂

##### *参数*

base: *Object*

exponent: *Object* or *Double*

##### *返回值*

array: *Array*

##### *范例*

```
$ndarray = $num->array([[0.5, 1], [0, 2]]);
$num->power($ndarray, 3);
// returns array([[0.125, 1.0], [0.0, 8.0]])
```

### square

------

_**说明**_: 遍历计算平方

##### *参数*

ndarray: *Object*

##### *返回值*

array: *Array*

##### *范例*

```
$ndarray = $num->array([[0.5, 1], [0, 2]]);
$num->square($ndarray);
// returns array([[0.5, 1.0], [0.0, 4.0]])
```

### sqrt

------

_**说明**_: 遍历计算平方根

##### *参数*

ndarray: *Object*

##### *返回值*

array: *Array*

##### *范例*

```
$ndarray = $num->array([[0.5, 1], [0, 2]]);
$num->sqrt($ndarray);
// returns array([[0.70710678118654757, 1.0], [0.0, 1.4142135623730951]])
```

### exp

------

_**说明**_: 遍历计算自然常数e的次幂

##### *参数*

ndarray: *Object*

##### *返回值*

array: *Array*

##### *范例*

```
$ndarray = $num->array([[0.5, 1], [0, 2]]);
$num->exp($ndarray);
// returns array([[1.6487212707001282, 2.7182818284590451], [1.0, 7.3890560989306504]])
```

### log

------

_**说明**_: 遍历计算自然对数

##### *参数*

ndarray: *Object*

##### *返回值*

array: *Array*

##### *范例*

```
$ndarray = $num->array([[0.5, 1], [10, 2]]);
$num->log($ndarray);
// returns array([[-0.69314718055994529, 0.0], [2.3025850929940459, 0.69314718055994529]])
```

### sin

------

_**说明**_: 遍历计算正弦值

##### *参数*

ndarray: *Object*

##### *返回值*

array: *Array*

##### *范例*

```
$ndarray = $num->array([[0.5, 1], [0, 2]]);
$num->sin($ndarray);
// returns array([[0.47942553860420301, 0.8414709848078965], [0.0, 0.90929742682568171]])
```

### cos

------

_**说明**_: 遍历计算余弦值

##### *参数*

ndarray: *Object*

##### *返回值*

array: *Array*

##### *范例*

```
$ndarray = $num->array([[0.5, 1], [0, 2]]);
$num->cos($ndarray);
// returns array([[0.87758256189037276, 0.54030230586813977], [1.0, -0.41614683654714241]])
```

### tan

------

_**说明**_: 遍历计算正切值

##### *参数*

ndarray: *Object*

##### *返回值*

array: *Array*

##### *范例*

```
$ndarray = $num->array([[0.5, 1], [0, 2]]);
$num->tan($ndarray);
// returns array([[0.54630248984379048, 1.5574077246549023], [0.0, -2.1850398632615189]])
```

### ceil

------

_**说明**_: 遍历计算向上取整

##### *参数*

ndarray: *Object*

##### *返回值*

array: *Array*

##### *范例*

```
$ndarray = $num->array([[0.5, 1], [0, 2]]);
$num->ceil($ndarray);
// returns array([[1.0, 1.0], [0.0, 2.0]])
```

### floor

------

_**说明**_: 遍历计算向下取整

##### *参数*

ndarray: *Object*

##### *返回值*

array: *Array*

##### *范例*

```
$ndarray = $num->array([[0.5, 1], [0, 2]]);
$num->floor($ndarray);
// returns array([[0.0, 1.0], [0.0, 2.0]])
```

