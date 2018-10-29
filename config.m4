dnl $Id$
dnl config.m4 for extension spp

PHP_ARG_ENABLE(spp, whether to enable spp support,
dnl Make sure that the comment is aligned:
[  --enable-spp           Enable spp support])

if test "$PHP_SPP" != "no"; then
  PHP_REQUIRE_CXX()

  # --with-spp -> check with-path
  SEARCH_PATH="/usr/local /usr"
  SEARCH_FOR="/include/sentencepiece_processor.h"
  if test -r $PHP_SPP/$SEARCH_FOR; then # path given as parameter
    SPP_DIR=$PHP_SPP
  else # search default path list
    AC_MSG_CHECKING([for spp files in default path])
    for i in $SEARCH_PATH ; do
      if test -r $i/$SEARCH_FOR; then
        SPP_DIR=$i
        AC_MSG_RESULT(found in $i)
      fi
    done
  fi

  if test -z "$SPP_DIR"; then
    AC_MSG_RESULT([not found])
    AC_MSG_ERROR([Please reinstall the spp distribution, "$PHP_SPP"])
  fi

  # --with-spp -> add include path
  PHP_ADD_INCLUDE($SPP_DIR/include/spp)

  # --with-spp -> check for lib and symbol presence
  LIBNAME="spp"
  LIBSYMBOL="SPM_VERSION"

  PHP_SUBST(SPP_SHARED_LIBADD)

  PHP_ADD_LIBRARY(stdc++, 1, SPP_SHARED_LIBADD)
  PHP_ADD_LIBRARY(sentencepiece, 1, SPP_SHARED_LIBADD)
  CFLAGS="-O3 -funroll-loops"
  CXXFLAGS="-pthread -std=c++14 -O3 -funroll-loops"

  PHP_NEW_EXTENSION(spp, spp_api.cc spp.c, $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)
fi
