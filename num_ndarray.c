/*
  +----------------------------------------------------------------------+
  | PHPNUM - A PHP extension for scientific computing                    |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2016 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:  Astraeux  <astraeux@gmail.com>                              |
  +----------------------------------------------------------------------+
*/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "Zend/zend_interfaces.h"

#include "php_num.h"
#include "num_ndarray.h"

zend_class_entry *num_ndarray_ce;

zval* num_calc_shape(zval *data, zval *shape, zend_long dimension){
    zval *ret, *check_shape;
    zend_long count;
    zval *val;
    HashTable *ht;
    ht = Z_ARRVAL_P(data);
    if (Z_TYPE_P(data) == IS_ARRAY) {
        count = Z_ARR_P(data)->nNumOfElements;
        check_shape = zend_hash_index_find(Z_ARR_P(shape), dimension);
        if (check_shape != NULL && Z_LVAL_P(check_shape) != count) {
            php_error_docref(NULL, E_ERROR, "Dimensions did not match");
            return NULL;
        } else {
            add_index_long(shape, dimension, count);
        }
        ZEND_HASH_FOREACH_VAL(ht, val) {
            num_calc_shape(val, shape, dimension + 1);
        } ZEND_HASH_FOREACH_END();
    }
}

double num_operator_add(double val1, double val2) {
    return val1 + val2;
}

double num_operator_sub(double val1, double val2) {
    return val1 - val2;
}

double num_operator_mult(double val1, double val2) {
    return val1 * val2;
}

double num_operator_div(double val1, double val2) {
    return val1 / val2;
}

int num_recursive(zval *data1, zval *data2, num_func_t num_func){
    zval *val1, *val2;
    zend_ulong idx;
    HashTable *ht1, *ht2;
    if (Z_TYPE_P(data1) == IS_ARRAY) {
        ht1 = Z_ARR_P(data1);
        ht2 = Z_ARR_P(data2);
        ZEND_HASH_FOREACH_NUM_KEY_VAL(ht1, idx, val1) {
            val2 = zend_hash_index_find(ht2, idx);
            if (Z_TYPE_P(val1) == IS_ARRAY) {
                num_recursive(val1, val2, num_func);
            } else {
                convert_to_double(val1);
                convert_to_double(val2);
                ZVAL_DOUBLE(val1, num_func(Z_DVAL_P(val1), Z_DVAL_P(val2)));
            }
        } ZEND_HASH_FOREACH_END();
    }
    return SUCCESS;
}

ZEND_METHOD(num_ndarray, __construct)
{
    zval *data, shape;
    if( zend_parse_parameters(ZEND_NUM_ARGS(), "z", &data) == FAILURE ) {
        RETURN_NULL();
    }

    array_init(&shape);
    num_calc_shape(data, &shape, 0);

    zend_update_property(num_ndarray_ce, getThis(), ZEND_STRL(NUM_NDARRAY_PROPERT_DATA), data);
    zend_update_property(num_ndarray_ce, getThis(), ZEND_STRL(NUM_NDARRAY_PROPERT_SHAPE), &shape);

    RETURN_ZVAL(getThis(), 1, 0);
}

ZEND_METHOD(num_ndarray, getData)
{
    zval *data = zend_read_property(num_ndarray_ce, getThis(), ZEND_STRL(NUM_NDARRAY_PROPERT_DATA), 0, NULL);
    RETURN_ZVAL(data, 1, 0);
}

ZEND_METHOD(num_ndarray, setData)
{
    zval *data;
    if( zend_parse_parameters(ZEND_NUM_ARGS(), "z", &data) == FAILURE )
    {
        RETURN_NULL();
    }
    zend_update_property(num_ndarray_ce, getThis(), ZEND_STRL(NUM_NDARRAY_PROPERT_DATA), data);
    RETURN_TRUE;
}

ZEND_METHOD(num_ndarray, getShape)
{
    zval *shape = zend_read_property(num_ndarray_ce, getThis(), ZEND_STRL(NUM_NDARRAY_PROPERT_SHAPE), 0, NULL);
    RETURN_ZVAL(shape, 1, 0);
}

ZEND_METHOD(num_ndarray, setShape)
{
    zval *shape;
    if( zend_parse_parameters(ZEND_NUM_ARGS(), "z", &shape) == FAILURE )
    {
        RETURN_NULL();
    }
    zend_update_property(num_ndarray_ce, getThis(), ZEND_STRL(NUM_NDARRAY_PROPERT_SHAPE), shape);
    RETURN_TRUE;
}

ZEND_METHOD(num_ndarray, __toString)
{
    php_printf("__toString called\n");
    zval *data = zend_read_property(num_ndarray_ce, getThis(), ZEND_STRL(NUM_NDARRAY_PROPERT_DATA), 0, NULL);
    zval level, ret, prefix, suffix;
    ZVAL_LONG(&level, 0);
    ZVAL_STRING(&prefix, "Ndarray(");
    ZVAL_STRING(&suffix, ")\n");
    zend_call_method_with_2_params(getThis(), num_ndarray_ce, NULL, "_to_string", &ret, data, &level);
    concat_function(return_value, return_value, &prefix);
    concat_function(return_value, return_value, &ret);
    concat_function(return_value, return_value, &suffix);
}

ZEND_METHOD(num_ndarray, _to_string)
{
    zval *data, *level, *first, output, tmp, *row, ret, *val, function, params[2], spaces;
    HashPosition pointer = 0;
    HashTable *ht;
    ulong idx;
    zend_string *delim;
    delim = zend_string_init(ZEND_STRL(","), 0);

    if( zend_parse_method_parameters(ZEND_NUM_ARGS(), NULL, "z|z", &data, &level) == FAILURE ) {
        RETURN_NULL();
    }
    if (Z_TYPE_P(data) != IS_ARRAY) {
        RETURN_ZVAL(data, 1, 0);
    }

    ZVAL_STRING(&params[0], "  ");
    ZVAL_LONG(&params[1], Z_LVAL_P(level));
    ZVAL_STRING(&function, "str_repeat");
    call_user_function(EG(function_table), NULL, &function, &spaces, 2, params);
    ZVAL_STRING(&output, "");

    ht = Z_ARRVAL_P(data);
    first = zend_hash_get_current_data_ex(ht, &pointer);
    if (Z_TYPE_P(first) == IS_ARRAY) {
        ZVAL_STRING(&output, Z_STRVAL(spaces));
        ZVAL_STRING(&tmp, "[\n");
        concat_function(&output, &output, &tmp);
        Z_LVAL_P(level) += 1;
        ZEND_HASH_FOREACH_NUM_KEY_VAL(ht, idx, val) {
            zend_call_method_with_2_params(getThis(), num_ndarray_ce, NULL, "_to_string", &ret, val, level);
            concat_function(&output, &output, &ret);
            if (idx + 1 < zend_array_count(ht)) {
                ZVAL_STRING(&tmp, ",\n");
            } else {
                ZVAL_STRING(&tmp, "\n");
                concat_function(&output, &output, &tmp);
                concat_function(&output, &output, &spaces);
                ZVAL_STRING(&tmp, "]");
            }
            concat_function(&output, &output, &tmp);
        } ZEND_HASH_FOREACH_END();
    } else {
        concat_function(&output, &output, &spaces);
        ZVAL_STRING(&tmp, "[");
        concat_function(&output, &output, &tmp);
        php_implode(delim, data, return_value);
        tmp = *return_value;
        concat_function(&output, &output, &tmp);
        ZVAL_STRING(&tmp, "]");
        concat_function(&output, &output, &tmp);
    }
    zval_ptr_dtor(&tmp);
    RETURN_STRING(Z_STRVAL(output));
}

ZEND_METHOD(num_ndarray, add)
{
    zval *ce, compare;
    zval *self = getThis();
    if( zend_parse_parameters(ZEND_NUM_ARGS(), "z", &ce) == FAILURE ) {
        RETURN_NULL();
    }
    zval *shape1 = zend_read_property(num_ndarray_ce, self, ZEND_STRL(NUM_NDARRAY_PROPERT_SHAPE), 0, NULL);
    zval *shape2 = zend_read_property(Z_OBJCE_P(ce), ce, ZEND_STRL(NUM_NDARRAY_PROPERT_SHAPE), 0, NULL);
    compare_function(&compare, shape1, shape2);
    if (Z_LVAL(compare) != 0) {
        php_error_docref(NULL, E_ERROR, "Operands could not be broadcast together with shapes");
        RETURN_NULL();
    }
    zval *data1 = zend_read_property(num_ndarray_ce, self, ZEND_STRL(NUM_NDARRAY_PROPERT_DATA), 0, NULL);
    zval *data2 = zend_read_property(Z_OBJCE_P(ce), ce, ZEND_STRL(NUM_NDARRAY_PROPERT_DATA), 0, NULL);
    num_recursive(data1, data2, num_operator_add);
    RETURN_ZVAL(self, 1, 0);
}

ZEND_METHOD(num_ndarray, sub)
{
    zval *ce, compare;
    zval *self = getThis();
    if( zend_parse_parameters(ZEND_NUM_ARGS(), "z", &ce) == FAILURE ) {
        RETURN_NULL();
    }
    zval *shape1 = zend_read_property(num_ndarray_ce, self, ZEND_STRL(NUM_NDARRAY_PROPERT_SHAPE), 0, NULL);
    zval *shape2 = zend_read_property(Z_OBJCE_P(ce), ce, ZEND_STRL(NUM_NDARRAY_PROPERT_SHAPE), 0, NULL);
    compare_function(&compare, shape1, shape2);
    if (Z_LVAL(compare) != 0) {
        php_error_docref(NULL, E_ERROR, "Operands could not be broadcast together with shapes");
        RETURN_NULL();
    }
    zval *data1 = zend_read_property(num_ndarray_ce, self, ZEND_STRL(NUM_NDARRAY_PROPERT_DATA), 0, NULL);
    zval *data2 = zend_read_property(Z_OBJCE_P(ce), ce, ZEND_STRL(NUM_NDARRAY_PROPERT_DATA), 0, NULL);
    num_recursive(data1, data2, num_operator_sub);
    RETURN_ZVAL(self, 1, 0);
}

ZEND_METHOD(num_ndarray, mult)
{
    zval *ce, compare;
    zval *self = getThis();
    if( zend_parse_parameters(ZEND_NUM_ARGS(), "z", &ce) == FAILURE ) {
        RETURN_NULL();
    }
    zval *shape1 = zend_read_property(num_ndarray_ce, self, ZEND_STRL(NUM_NDARRAY_PROPERT_SHAPE), 0, NULL);
    zval *shape2 = zend_read_property(Z_OBJCE_P(ce), ce, ZEND_STRL(NUM_NDARRAY_PROPERT_SHAPE), 0, NULL);
    compare_function(&compare, shape1, shape2);
    if (Z_LVAL(compare) != 0) {
        php_error_docref(NULL, E_ERROR, "Operands could not be broadcast together with shapes");
        RETURN_NULL();
    }
    zval *data1 = zend_read_property(num_ndarray_ce, self, ZEND_STRL(NUM_NDARRAY_PROPERT_DATA), 0, NULL);
    zval *data2 = zend_read_property(Z_OBJCE_P(ce), ce, ZEND_STRL(NUM_NDARRAY_PROPERT_DATA), 0, NULL);
    num_recursive(data1, data2, num_operator_mult);
    RETURN_ZVAL(self, 1, 0);
}

ZEND_METHOD(num_ndarray, div)
{
    zval *ce, compare;
    zval *self = getThis();
    if( zend_parse_parameters(ZEND_NUM_ARGS(), "z", &ce) == FAILURE ) {
        RETURN_NULL();
    }
    zval *shape1 = zend_read_property(num_ndarray_ce, self, ZEND_STRL(NUM_NDARRAY_PROPERT_SHAPE), 0, NULL);
    zval *shape2 = zend_read_property(Z_OBJCE_P(ce), ce, ZEND_STRL(NUM_NDARRAY_PROPERT_SHAPE), 0, NULL);
    compare_function(&compare, shape1, shape2);
    if (Z_LVAL(compare) != 0) {
        php_error_docref(NULL, E_ERROR, "Operands could not be broadcast together with shapes");
        RETURN_NULL();
    }
    zval *data1 = zend_read_property(num_ndarray_ce, self, ZEND_STRL(NUM_NDARRAY_PROPERT_DATA), 0, NULL);
    zval *data2 = zend_read_property(Z_OBJCE_P(ce), ce, ZEND_STRL(NUM_NDARRAY_PROPERT_DATA), 0, NULL);
    num_recursive(data1, data2, num_operator_div);
    RETURN_ZVAL(self, 1, 0);
}

zend_function_entry num_ndarray_methods[]=
{
    ZEND_ME(num_ndarray, __construct, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
    ZEND_ME(num_ndarray, getData, NULL, ZEND_ACC_PUBLIC)
    ZEND_ME(num_ndarray, setData, NULL, ZEND_ACC_PROTECTED)
    ZEND_ME(num_ndarray, getShape, NULL, ZEND_ACC_PUBLIC)
    ZEND_ME(num_ndarray, setShape, NULL, ZEND_ACC_PROTECTED)
    ZEND_ME(num_ndarray, __toString, NULL, ZEND_ACC_PUBLIC )
    ZEND_ME(num_ndarray, _to_string, NULL, ZEND_ACC_PROTECTED)
    ZEND_ME(num_ndarray, add, NULL, ZEND_ACC_PUBLIC)
    ZEND_ME(num_ndarray, sub, NULL, ZEND_ACC_PUBLIC)
    ZEND_ME(num_ndarray, mult, NULL, ZEND_ACC_PUBLIC)
    ZEND_ME(num_ndarray, div, NULL, ZEND_ACC_PUBLIC)
    ZEND_FE_END
};

/** {{{ NUM_STARTUP_FUNCTION
*/
NUM_STARTUP_FUNCTION(ndarray)
{
    zend_class_entry ce;
    INIT_CLASS_ENTRY(ce, "Num_Ndarray", num_ndarray_methods);
    num_ndarray_ce = zend_register_internal_class(&ce);
    zend_declare_property_null(num_ndarray_ce, ZEND_STRL("_data"), ZEND_ACC_PUBLIC);
    zend_declare_property_null(num_ndarray_ce, ZEND_STRL("_shape"), ZEND_ACC_PUBLIC);

	return SUCCESS;
}
/* }}} */