dnl $Id$
dnl config.m4 for extension num

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(num, for num support,
dnl Make sure that the comment is aligned:
dnl [  --with-num             Include num support])

dnl Otherwise use enable:

PHP_ARG_ENABLE(num, whether to enable num support,
Make sure that the comment is aligned:
[  --enable-num           Enable num support])

if test "$PHP_NUM" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-num -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/num.h"  # you most likely want to change this
  dnl if test -r $PHP_NUM/$SEARCH_FOR; then # path given as parameter
  dnl   NUM_DIR=$PHP_NUM
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for num files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       NUM_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$NUM_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the num distribution])
  dnl fi

  dnl # --with-num -> add include path
  dnl PHP_ADD_INCLUDE($NUM_DIR/include)

  dnl # --with-num -> check for lib and symbol presence
  dnl LIBNAME=num # you may want to change this
  dnl LIBSYMBOL=num # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $NUM_DIR/$PHP_LIBDIR, NUM_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_NUMLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong num lib version or lib not found])
  dnl ],[
  dnl   -L$NUM_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(NUM_SHARED_LIBADD)

  PHP_NEW_EXTENSION(num, num.c num_ndarray.c, $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)
fi
