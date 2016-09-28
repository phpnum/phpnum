/*
  +----------------------------------------------------------------------+
  | phpnum - A PHP extension for scientific computing                    |
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

#include "zend_smart_str.h"

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

int num_ndarray_recursive(zval *data1, zval *data2, num_func_t num_func){
    zval *val1, *val2;
    zend_ulong idx;
    HashTable *ht1, *ht2;
    if (Z_TYPE_P(data1) == IS_ARRAY) {
        ht1 = Z_ARR_P(data1);
        ht2 = Z_ARR_P(data2);
        ZEND_HASH_FOREACH_NUM_KEY_VAL(ht1, idx, val1) {
            val2 = zend_hash_index_find(ht2, idx);
            if (Z_TYPE_P(val1) == IS_ARRAY) {
                num_ndarray_recursive(val1, val2, num_func);
            } else {
                convert_to_double(val1);
                convert_to_double(val2);
                ZVAL_DOUBLE(val1, num_func(Z_DVAL_P(val1), Z_DVAL_P(val2)));
            }
        } ZEND_HASH_FOREACH_END();
    }
    return SUCCESS;
}

int num_ndarray_compare_recursive(zval *ret, zval *data, num_func_t num_func){
    zval *val;
    if (Z_TYPE_P(data) == IS_ARRAY) {
        ZEND_HASH_FOREACH_VAL(Z_ARR_P(data), val) {
            if (Z_TYPE_P(val) == IS_ARRAY) {
                num_ndarray_compare_recursive(ret, val, num_func);
            } else {
                convert_to_double(val);
                if (Z_TYPE_P(ret) == IS_NULL) {
                    ZVAL_DOUBLE(ret, Z_DVAL_P(val));
                } else {
                    ZVAL_DOUBLE(ret, num_func(Z_DVAL_P(ret), Z_DVAL_P(val)));
                }
            }
        } ZEND_HASH_FOREACH_END();
    }
    return SUCCESS;
}

int num_ndarray_self_recursive(zval *data, num_func_t_one num_func){
    zval *val, tmp;
    zend_ulong idx;
    if (Z_TYPE_P(data) == IS_ARRAY) {
        ZEND_HASH_FOREACH_NUM_KEY_VAL(Z_ARR_P(data), idx, val) {
            if (Z_TYPE_P(val) == IS_ARRAY) {
                tmp = *val;
                zval_copy_ctor(&tmp);
                add_index_zval(data, idx, &tmp);
                num_ndarray_self_recursive(&tmp, num_func);
            } else {
                convert_to_double(val);
                ZVAL_DOUBLE(val, num_func(Z_DVAL_P(val)));
            }
        } ZEND_HASH_FOREACH_END();
    }
    zval_ptr_dtor(&tmp);
    return SUCCESS;
}

int num_ndarray_arithmetic_recursive(zval *data1, zval *data2, num_func_t num_func){
    zval *val1, *val2, tmp;
    zend_ulong idx;
    HashTable *ht1, *ht2;
    if (Z_TYPE_P(data1) == IS_ARRAY) {
        ht1 = Z_ARR_P(data1);
        if (Z_TYPE_P(data2) == IS_ARRAY) {
            ht2 = Z_ARR_P(data2);
            ZEND_HASH_FOREACH_NUM_KEY_VAL(ht1, idx, val1) {
                val2 = zend_hash_index_find(ht2, idx);
                if (Z_TYPE_P(val1) == IS_ARRAY) {
                    tmp = *val1;
                    zval_copy_ctor(&tmp);
                    add_index_zval(data1, idx, &tmp);
                    num_ndarray_arithmetic_recursive(&tmp, val2, num_func);
                } else {
                    convert_to_double(val1);
                    convert_to_double(val2);
                    ZVAL_DOUBLE(val1, num_func(Z_DVAL_P(val1), Z_DVAL_P(val2)));
                }
            } ZEND_HASH_FOREACH_END();
        } else {
            ZEND_HASH_FOREACH_NUM_KEY_VAL(ht1, idx, val1) {
                if (Z_TYPE_P(val1) == IS_ARRAY) {
                    tmp = *val1;
                    zval_copy_ctor(&tmp);
                    add_index_zval(data1, idx, &tmp);
                    num_ndarray_arithmetic_recursive(&tmp, data2, num_func);
                } else {
                    convert_to_double(val1);
                    convert_to_double(data2);
                    ZVAL_DOUBLE(val1, num_func(Z_DVAL_P(val1), Z_DVAL_P(data2)));
                }
            } ZEND_HASH_FOREACH_END();
        }
    }
    zval_ptr_dtor(&tmp);
    return SUCCESS;
}

zend_string *num_ndarray_to_string(zval *data, zend_long level){
    zend_string *space, *ret;
    zval *first, *val, tmp;
    smart_str output = {0};
    HashPosition pointer = 0;
    HashTable *ht;
    zend_ulong idx;
    zend_string *delim;
    delim = zend_string_init(ZEND_STRL(","), 0);
    if (Z_TYPE_P(data) != IS_ARRAY) {
        return zend_string_init(ZEND_STRL(Z_STRVAL_P(data)), 0);
    }
    space = level == 0 ? zend_string_init(ZEND_STRL(""), 0) : strpprintf(0, "%*c", level, ' ');
    ht = Z_ARRVAL_P(data);
    first = zend_hash_get_current_data_ex(ht, &pointer);
    if (Z_TYPE_P(first) == IS_ARRAY) {
        smart_str_sets(&output, ZSTR_VAL(space));
        smart_str_appends(&output, "[\n");
        ZEND_HASH_FOREACH_NUM_KEY_VAL(ht, idx, val) {
            ret = num_ndarray_to_string(val, level + 2);
            smart_str_appends(&output, ZSTR_VAL(ret));
            if (idx + 1 < zend_array_count(ht)) {
                smart_str_appends(&output, ",\n");
            } else {
                smart_str_appends(&output, "\n");
                smart_str_appends(&output, ZSTR_VAL(space));
                smart_str_appends(&output, "]");
            }
        } ZEND_HASH_FOREACH_END();
    } else {
        smart_str_appends(&output, ZSTR_VAL(space));
        smart_str_appends(&output, "[");
        php_implode(delim, data, &tmp);
        smart_str_appends(&output, Z_STRVAL(tmp));
        smart_str_appends(&output, "]");
    }
    zval_ptr_dtor(first);
    return output.s;
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

ZEND_METHOD(num_ndarray, __toString)
{
    zend_string *ret;
    smart_str output = {0};
    zval *data = zend_read_property(num_ndarray_ce, getThis(), ZEND_STRL(NUM_NDARRAY_PROPERT_DATA), 0, NULL);
    ret = num_ndarray_to_string(data, 0);
    smart_str_appends(&output, "array(");
    smart_str_appends(&output, ZSTR_VAL(ret));
    smart_str_appends(&output, ")\n");
    smart_str_0(&output);
    RETURN_STRING(ZSTR_VAL(output.s));
}

ZEND_METHOD(num_ndarray, getData)
{
    zval *data = zend_read_property(num_ndarray_ce, getThis(), ZEND_STRL(NUM_NDARRAY_PROPERT_DATA), 0, NULL);
    RETURN_ZVAL(data, 1, 0);
}

ZEND_METHOD(num_ndarray, getShape)
{
    zval *shape = zend_read_property(num_ndarray_ce, getThis(), ZEND_STRL(NUM_NDARRAY_PROPERT_SHAPE), 0, NULL);
    RETURN_ZVAL(shape, 1, 0);
}

ZEND_METHOD(num_ndarray, getNdim)
{
    zval *shape = zend_read_property(num_ndarray_ce, getThis(), ZEND_STRL(NUM_NDARRAY_PROPERT_SHAPE), 0, NULL);
    RETURN_LONG(zend_array_count(Z_ARRVAL_P(shape)));
}

ZEND_METHOD(num_ndarray, getSize)
{
    zval *shape = zend_read_property(num_ndarray_ce, getThis(), ZEND_STRL(NUM_NDARRAY_PROPERT_SHAPE), 0, NULL);
    zval *val;
    HashTable *ht;
    zend_ulong size = 1;
    ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(shape), val) {
        size *= Z_LVAL_P(val);
    } ZEND_HASH_FOREACH_END();
    RETURN_LONG(size);
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
    num_ndarray_recursive(data1, data2, num_operator_add);
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
    num_ndarray_recursive(data1, data2, num_operator_sub);
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
    num_ndarray_recursive(data1, data2, num_operator_mult);
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
    num_ndarray_recursive(data1, data2, num_operator_div);
    RETURN_ZVAL(self, 1, 0);
}

zend_function_entry num_ndarray_methods[]=
{
    ZEND_ME(num_ndarray, __construct, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
    ZEND_ME(num_ndarray, __toString, NULL, ZEND_ACC_PUBLIC )
    ZEND_ME(num_ndarray, getData, NULL, ZEND_ACC_PUBLIC)
    ZEND_ME(num_ndarray, getShape, NULL, ZEND_ACC_PUBLIC)
    ZEND_ME(num_ndarray, getNdim, NULL, ZEND_ACC_PUBLIC)
    ZEND_ME(num_ndarray, getSize, NULL, ZEND_ACC_PUBLIC)
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
    INIT_CLASS_ENTRY(ce, "NumNdarray", num_ndarray_methods);
    num_ndarray_ce = zend_register_internal_class(&ce);
    zend_declare_property_null(num_ndarray_ce, ZEND_STRL("_data"), ZEND_ACC_PUBLIC);
    zend_declare_property_null(num_ndarray_ce, ZEND_STRL("_shape"), ZEND_ACC_PUBLIC);

	return SUCCESS;
}
/* }}} */