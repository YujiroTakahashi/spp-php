#ifndef PHP_SPP_H
#define PHP_SPP_H

#include "spp_api.h"

#define PHP_SPP_VERSION	"0.1.0"

extern zend_module_entry spp_module_entry;
#define phpext_spp_ptr &spp_module_entry

ZEND_BEGIN_MODULE_GLOBALS(spp)
	char *model_dir;
ZEND_END_MODULE_GLOBALS(spp)

#ifdef ZTS
# define SPP_G(v) TSRMG(spp_globals_id, zend_spp_globals *, v)
# ifdef COMPILE_DL_SPP
ZEND_TSRMLS_CACHE_EXTERN()
# endif
#else
# define SPP_G(v) (spp_globals.v)
#endif

typedef struct {
    zend_object zo;
	zval error;
    SppHandle spp;
} php_spp_object;

static inline php_spp_object *php_spp_from_obj(zend_object *obj) {
	return (php_spp_object*)((char*)(obj) - XtOffsetOf(php_spp_object, zo));
}

#define Z_SPP_P(zv) php_spp_from_obj(Z_OBJ_P((zv)))


#endif  /* PHP_SPP_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * indent-tabs-mode: t
 * End:
 */
