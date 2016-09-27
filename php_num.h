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

#ifndef PHP_NUM_H
#define PHP_NUM_H

#include "zend.h"

extern zend_module_entry num_module_entry;
#define phpext_num_ptr &num_module_entry

#define PHP_NUM_VERSION "0.0.1" /* Replace with version number for your extension */

#ifdef PHP_WIN32
#	define PHP_NUM_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#	define PHP_NUM_API __attribute__ ((visibility("default")))
#else
#	define PHP_NUM_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

#define NUM_STARTUP_FUNCTION(module)    ZEND_MINIT_FUNCTION(num_##module)
#define NUM_RINIT_FUNCTION(module)    ZEND_RINIT_FUNCTION(num_##module)
#define NUM_STARTUP(module)         ZEND_MODULE_STARTUP_N(num_##module)(INIT_FUNC_ARGS_PASSTHRU)
#define NUM_SHUTDOWN_FUNCTION(module)   ZEND_MSHUTDOWN_FUNCTION(num_##module)
#define NUM_SHUTDOWN(module)        ZEND_MODULE_SHUTDOWN_N(num_##module)(INIT_FUNC_ARGS_PASSTHRU)

#define max(a,b) ( ((a)>(b)) ? (a):(b) )
#define min(a,b) ( ((a)>(b)) ? (b):(a) )

#define NUM_PROPERT_ARRAY          "_array"

extern zend_class_entry *num_ce;

typedef double (*num_func_t)(double val1, double val2);
typedef double (*num_func_t_one)(double val);

double num_operator_add(double val1, double val2);
double num_operator_sub(double val1, double val2);
double num_operator_mult(double val1, double val2);
double num_operator_div(double val1, double val2);
double num_max(double val1, double val2);
double num_min(double val1, double val2);

/*
  	Declare any global variables you may need between the BEGIN
	and END macros here:

ZEND_BEGIN_MODULE_GLOBALS(num)
	zend_long  global_value;
	char *global_string;
ZEND_END_MODULE_GLOBALS(num)
*/

/* Always refer to the globals in your function as NUM_G(variable).
   You are encouraged to rename these macros something shorter, see
   examples in any other php module directory.
*/
#define NUM_G(v) ZEND_MODULE_GLOBALS_ACCESSOR(num, v)

#if defined(ZTS) && defined(COMPILE_DL_NUM)
ZEND_TSRMLS_CACHE_EXTERN()
#endif

#endif	/* PHP_NUM_H */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
