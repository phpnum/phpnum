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

int call_user_method(zval *obj, zend_class_entry *obj_ce, zval func, zval *retval, uint32_t params_count, zval params[]){ 
    HashTable *function_table; 

    if(obj) { 
        function_table = &Z_OBJCE_P(obj)->function_table;
    }else{
        function_table = (CG(function_table));
    }

    zend_fcall_info fci;  
    fci.size = sizeof(fci);  
    fci.function_table = function_table;  
    fci.object =  obj ? Z_OBJ_P(obj) : NULL;;
    fci.function_name = func;   
    fci.retval = retval;  
    fci.param_count = params_count;  
    fci.params = params;  
    fci.no_separation = 1;  
    fci.symbol_table = NULL;  

    int result;
    result = zend_call_function(&fci, NULL TSRMLS_CC);         //函数调用结束。  

    if (result == FAILURE) {
        zend_printf("call user method error\n");
    }
}

/* If you declare any globals in php_num.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(num)
*/

ZEND_METHOD(num, ndarray)
{
    zval *data, ret, obj;
    if( zend_parse_parameters(ZEND_NUM_ARGS(), "z", &data) == FAILURE ) {
        RETURN_NULL();
    }
    object_init_ex(&obj, num_ndarray_ce);
    zend_call_method_with_1_params(&obj, num_ndarray_ce, NULL, "__construct", &ret, data);
    RETURN_ZVAL(&ret, 1, 0);
}

static zend_function_entry num_methods[]=
{
    ZEND_ME(num, ndarray, NULL, ZEND_ACC_PUBLIC)
    ZEND_FE_END
};

PHP_MINIT_FUNCTION(num)
{
    zend_class_entry ce;
    INIT_CLASS_ENTRY(ce, "Num", num_methods);
    zend_register_internal_class(&ce TSRMLS_CC);
    NUM_STARTUP(ndarray);
    //NUM_STARTUP(shape);
    
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
