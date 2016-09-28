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

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "Zend/zend_interfaces.h"

#include "php_num.h"
#include "num_ndarray.h"

zend_class_entry *num_ce;

/* If you declare any globals in php_num.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(num)
*/

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

double num_max(double val1, double val2) {
    return val1 > val2 ? val1 : val2;
}

double num_min(double val1, double val2) {
    return val1 > val2 ? val2 : val1;
}

ZEND_METHOD(num, array)
{
    zval *data, ret, obj;
    if( zend_parse_parameters(ZEND_NUM_ARGS(), "z", &data) == FAILURE ) {
        RETURN_NULL();
    }
    object_init_ex(&obj, num_ndarray_ce);
    zend_call_method_with_1_params(&obj, num_ndarray_ce, NULL, "__construct", &ret, data);
    zend_update_property(num_ce, getThis(), ZEND_STRL(NUM_PROPERT_ARRAY), &ret);
    RETURN_ZVAL(&ret, 1, 0);
}

ZEND_METHOD(num_ndarray, amin)
{
    zval *ce, ret;
    ZVAL_NULL(&ret);
    if( zend_parse_parameters(ZEND_NUM_ARGS(), "z", &ce) == FAILURE ) {
        RETURN_NULL();
    }
    zval *data = zend_read_property(Z_OBJCE_P(ce), ce, ZEND_STRL(NUM_NDARRAY_PROPERT_DATA), 0, NULL);
    num_ndarray_compare_recursive(&ret, data, num_min);
    RETURN_ZVAL(&ret, 1, 0);
}

ZEND_METHOD(num_ndarray, amax)
{
    zval *ce, ret;
    ZVAL_NULL(&ret);
    if( zend_parse_parameters(ZEND_NUM_ARGS(), "z", &ce) == FAILURE ) {
        RETURN_NULL();
    }
    zval *data = zend_read_property(Z_OBJCE_P(ce), ce, ZEND_STRL(NUM_NDARRAY_PROPERT_DATA), 0, NULL);
    num_ndarray_compare_recursive(&ret, data, num_max);
    RETURN_ZVAL(&ret, 1, 0);
}

ZEND_METHOD(num_ndarray, power)
{
    zval *ce, *exponent_ce, *data, *exponent, newdata;
    if( zend_parse_parameters(ZEND_NUM_ARGS(), "zz", &ce, &exponent_ce) == FAILURE ) {
        RETURN_NULL();
    }
    data = zend_read_property(Z_OBJCE_P(ce), ce, ZEND_STRL(NUM_NDARRAY_PROPERT_DATA), 0, NULL);
    newdata = *data;
    zval_copy_ctor(&newdata);
    exponent = Z_TYPE_P(exponent_ce) == IS_OBJECT ? zend_read_property(Z_OBJCE_P(exponent_ce), exponent_ce, ZEND_STRL(NUM_NDARRAY_PROPERT_DATA), 0, NULL) : exponent_ce;
    num_ndarray_arithmetic_recursive(&newdata, exponent, pow);
    zval_ptr_dtor(data);
    RETURN_ZVAL(&newdata, 1, 0);
}

ZEND_METHOD(num_ndarray, square)
{
    zval *ce, *data, exponent, newdata;
    if( zend_parse_parameters(ZEND_NUM_ARGS(), "z", &ce) == FAILURE ) {
        RETURN_NULL();
    }
    ZVAL_DOUBLE(&exponent, 2);
    data = zend_read_property(Z_OBJCE_P(ce), ce, ZEND_STRL(NUM_NDARRAY_PROPERT_DATA), 0, NULL);
    newdata = *data;
    zval_copy_ctor(&newdata);
    num_ndarray_arithmetic_recursive(&newdata, &exponent, pow);
    zval_ptr_dtor(data);
    zval_ptr_dtor(&exponent);
    RETURN_ZVAL(&newdata, 1, 0);
}

ZEND_METHOD(num_ndarray, sqrt)
{
    zval *ce, *data, newdata;
    if( zend_parse_parameters(ZEND_NUM_ARGS(), "z", &ce) == FAILURE ) {
        RETURN_NULL();
    }
    data = zend_read_property(Z_OBJCE_P(ce), ce, ZEND_STRL(NUM_NDARRAY_PROPERT_DATA), 0, NULL);
    newdata = *data;
    zval_copy_ctor(&newdata);
    num_ndarray_self_recursive(&newdata, sqrt);
    zval_ptr_dtor(data);
    RETURN_ZVAL(&newdata, 1, 0);
}

ZEND_METHOD(num_ndarray, exp)
{
    zval *ce, *data, newdata;
    if( zend_parse_parameters(ZEND_NUM_ARGS(), "z", &ce) == FAILURE ) {
        RETURN_NULL();
    }
    data = zend_read_property(Z_OBJCE_P(ce), ce, ZEND_STRL(NUM_NDARRAY_PROPERT_DATA), 0, NULL);
    newdata = *data;
    zval_copy_ctor(&newdata);
    num_ndarray_self_recursive(&newdata, exp);
    zval_ptr_dtor(data);
    RETURN_ZVAL(&newdata, 1, 0);
}

ZEND_METHOD(num_ndarray, log)
{
    zval *ce, *data, newdata;
    if( zend_parse_parameters(ZEND_NUM_ARGS(), "z", &ce) == FAILURE ) {
        RETURN_NULL();
    }
    data = zend_read_property(Z_OBJCE_P(ce), ce, ZEND_STRL(NUM_NDARRAY_PROPERT_DATA), 0, NULL);
    newdata = *data;
    zval_copy_ctor(&newdata);
    num_ndarray_self_recursive(&newdata, log);
    zval_ptr_dtor(data);
    RETURN_ZVAL(&newdata, 1, 0);
}

ZEND_METHOD(num_ndarray, sin)
{
    zval *ce, *data, newdata;
    if( zend_parse_parameters(ZEND_NUM_ARGS(), "z", &ce) == FAILURE ) {
        RETURN_NULL();
    }
    data = zend_read_property(Z_OBJCE_P(ce), ce, ZEND_STRL(NUM_NDARRAY_PROPERT_DATA), 0, NULL);
    newdata = *data;
    zval_copy_ctor(&newdata);
    num_ndarray_self_recursive(&newdata, sin);
    zval_ptr_dtor(data);
    RETURN_ZVAL(&newdata, 1, 0);
}

ZEND_METHOD(num_ndarray, cos)
{
    zval *ce, *data, newdata;
    if( zend_parse_parameters(ZEND_NUM_ARGS(), "z", &ce) == FAILURE ) {
        RETURN_NULL();
    }
    data = zend_read_property(Z_OBJCE_P(ce), ce, ZEND_STRL(NUM_NDARRAY_PROPERT_DATA), 0, NULL);
    newdata = *data;
    zval_copy_ctor(&newdata);
    num_ndarray_self_recursive(&newdata, cos);
    zval_ptr_dtor(data);
    RETURN_ZVAL(&newdata, 1, 0);
}

ZEND_METHOD(num_ndarray, tan)
{
    zval *ce, *data, newdata;
    if( zend_parse_parameters(ZEND_NUM_ARGS(), "z", &ce) == FAILURE ) {
        RETURN_NULL();
    }
    data = zend_read_property(Z_OBJCE_P(ce), ce, ZEND_STRL(NUM_NDARRAY_PROPERT_DATA), 0, NULL);
    newdata = *data;
    zval_copy_ctor(&newdata);
    num_ndarray_self_recursive(&newdata, tan);
    zval_ptr_dtor(data);
    RETURN_ZVAL(&newdata, 1, 0);
}

ZEND_METHOD(num_ndarray, ceil)
{
    zval *ce, *data, newdata;
    if( zend_parse_parameters(ZEND_NUM_ARGS(), "z", &ce) == FAILURE ) {
        RETURN_NULL();
    }
    data = zend_read_property(Z_OBJCE_P(ce), ce, ZEND_STRL(NUM_NDARRAY_PROPERT_DATA), 0, NULL);
    newdata = *data;
    zval_copy_ctor(&newdata);
    num_ndarray_self_recursive(&newdata, ceil);
    zval_ptr_dtor(data);
    RETURN_ZVAL(&newdata, 1, 0);
}

ZEND_METHOD(num_ndarray, floor)
{
    zval *ce, *data, newdata;
    if( zend_parse_parameters(ZEND_NUM_ARGS(), "z", &ce) == FAILURE ) {
        RETURN_NULL();
    }
    data = zend_read_property(Z_OBJCE_P(ce), ce, ZEND_STRL(NUM_NDARRAY_PROPERT_DATA), 0, NULL);
    newdata = *data;
    zval_copy_ctor(&newdata);
    num_ndarray_self_recursive(&newdata, floor);
    zval_ptr_dtor(data);
    RETURN_ZVAL(&newdata, 1, 0);
}

static zend_function_entry num_methods[]=
{
    ZEND_ME(num, array, NULL, ZEND_ACC_PUBLIC)
    ZEND_ME(num_ndarray, amin, NULL, ZEND_ACC_PUBLIC)
    ZEND_ME(num_ndarray, amax, NULL, ZEND_ACC_PUBLIC)
    ZEND_ME(num_ndarray, power, NULL, ZEND_ACC_PUBLIC)
    ZEND_ME(num_ndarray, square, NULL, ZEND_ACC_PUBLIC)
    ZEND_ME(num_ndarray, sqrt, NULL, ZEND_ACC_PUBLIC)
    ZEND_ME(num_ndarray, exp, NULL, ZEND_ACC_PUBLIC)
    ZEND_ME(num_ndarray, log, NULL, ZEND_ACC_PUBLIC)
    ZEND_ME(num_ndarray, sin, NULL, ZEND_ACC_PUBLIC)
    ZEND_ME(num_ndarray, cos, NULL, ZEND_ACC_PUBLIC)
    ZEND_ME(num_ndarray, tan, NULL, ZEND_ACC_PUBLIC)
    ZEND_ME(num_ndarray, ceil, NULL, ZEND_ACC_PUBLIC)
    ZEND_ME(num_ndarray, floor, NULL, ZEND_ACC_PUBLIC)
    ZEND_FE_END
};

PHP_MINIT_FUNCTION(num)
{
    zend_class_entry ce;
    INIT_CLASS_ENTRY(ce, "Num", num_methods);
    num_ce = zend_register_internal_class(&ce);
    zend_declare_property_null(num_ce, ZEND_STRL(NUM_PROPERT_ARRAY), ZEND_ACC_PUBLIC);
    NUM_STARTUP(ndarray);
    
    return SUCCESS;
}

/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(num)
{
    /* uncomment this line if you have INI entries
    UNREGISTER_INI_ENTRIES();
    */
    return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(num)
{
#if defined(COMPILE_DL_NUM) && defined(ZTS)
    ZEND_TSRMLS_CACHE_UPDATE();
#endif
    return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(num)
{
    return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(num)
{
    php_info_print_table_start();
    php_info_print_table_header(2, "num support", "enabled");
    php_info_print_table_end();

    /* Remove comments if you have entries in php.ini
    DISPLAY_INI_ENTRIES();
    */
}
/* }}} */

/* {{{ num_functions[]
 *
 * Every user visible function must have an entry in num_functions[].
 */
const zend_function_entry num_functions[] = {
    PHP_FE_END  /* Must be the last line in num_functions[] */
};
/* }}} */

/* {{{ num_module_entry
 */
zend_module_entry num_module_entry = {
    STANDARD_MODULE_HEADER,
    "num",
    num_functions,
    PHP_MINIT(num),
    PHP_MSHUTDOWN(num),
    PHP_RINIT(num),     /* Replace with NULL if there's nothing to do at request start */
    PHP_RSHUTDOWN(num), /* Replace with NULL if there's nothing to do at request end */
    PHP_MINFO(num),
    PHP_NUM_VERSION,
    STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_NUM
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif
ZEND_GET_MODULE(num)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
