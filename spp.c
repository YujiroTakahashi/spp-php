#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "ext/json/php_json.h"
#include "php_spp.h"
#include "main/SAPI.h"


#include "zend_exceptions.h"
#include "zend_interfaces.h"
#include "SAPI.h"

ZEND_DECLARE_MODULE_GLOBALS(spp)

/* {{{ PHP_INI
*/
PHP_INI_BEGIN()
	STD_PHP_INI_ENTRY("spp.model_dir",  NULL, PHP_INI_SYSTEM, OnUpdateString, model_dir, zend_spp_globals, spp_globals)
PHP_INI_END()
/* }}} */

/* Handlers */
static zend_object_handlers spp_object_handlers;

/* Class entries */
zend_class_entry *php_spp_sc_entry;


/* {{{ proto void spp::__construct()
 */
PHP_METHOD(spp, __construct)
{
	php_spp_object *sp_obj;
	zval *object = getThis();

	sp_obj = Z_SPP_P(object);

	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}

	sp_obj->spp = SppCreate();
}
/* }}} */

/* {{{ proto long spp::load(String filename)
 */
PHP_METHOD(spp, load)
{
	php_spp_object *sp_obj;
	zval *object = getThis();
	char *filename;
	size_t filename_len;
	zend_long res;

	sp_obj = Z_SPP_P(object);

	if (FAILURE == zend_parse_parameters_throw(ZEND_NUM_ARGS(), "s", &filename, &filename_len)) {
		return;
	}
	res = SppLoad(sp_obj->spp, filename);

	RETURN_LONG(res);
}
/* }}} */

/* {{{ proto mixed spp::encode(String word)
 */
PHP_METHOD(spp, encode)
{
	php_spp_object *sp_obj;
	zval *object = getThis();
	char *word;
	size_t word_len;
	SPStr str;

	sp_obj = Z_SPP_P(object);

	if (FAILURE == zend_parse_parameters_throw(ZEND_NUM_ARGS(), "s", &word, &word_len)) {
		return;
	}
	str = SppEncode(sp_obj->spp, (const char*)word);

	array_init(return_value);
	php_json_decode(return_value, str->buff, str->len, 1, PHP_JSON_PARSER_DEFAULT_DEPTH);
	SppStrFree(str);
}
/* }}} */

/* {{{ proto mixed spp::wakati(String word)
 */
PHP_METHOD(spp, wakati)
{
	php_spp_object *sp_obj;
	zval *object = getThis();
	char *word;
	size_t word_len;
	SPStr str;

	sp_obj = Z_SPP_P(object);

	if (FAILURE == zend_parse_parameters_throw(ZEND_NUM_ARGS(), "s", &word, &word_len)) {
		return;
	}
	str = SppWakati(sp_obj->spp, (const char*)word);
	ZVAL_STRINGL(return_value, str->buff, str->len);
	SppStrFree(str);
}
/* }}} */


/* {{{ proto mixed spp::decode(array ids)
 */
PHP_METHOD(spp, decode)
{
	php_spp_object *sp_obj;
	zval *object = getThis();
	zval *array;
	smart_str *buf;
	SPStr str;

	sp_obj = Z_SPP_P(object);

	if (FAILURE == zend_parse_parameters_throw(ZEND_NUM_ARGS(), "z", &array)) {
		return;
	}
	php_json_encode(buf, array, 0);

	str = SppDecode(sp_obj->spp, (const char*)ZSTR_VAL(buf->s));
	ZVAL_STRINGL(return_value, str->buff, str->len);
	SppStrFree(str);
}
/* }}} */

/* {{{ proto mixed spp::sampleEncode(String word)
 */
PHP_METHOD(spp, sampleEncode)
{
	php_spp_object *sp_obj;
	zval *object = getThis();
	char *word;
	size_t word_len;
	zend_long size = -1;
	double alpha = 0.2;
	SPStr str;

	sp_obj = Z_SPP_P(object);

	if (FAILURE == zend_parse_parameters_throw(ZEND_NUM_ARGS(), "s|ld", &word, &word_len, &size, &alpha)) {
		return;
	}
	str = SppSampleEncode(sp_obj->spp, (const char*)word, size, (const float)alpha);
	ZVAL_STRINGL(return_value, str->buff, str->len);
	SppStrFree(str);
}
/* }}} */

/* {{{ proto mixed spp::getPieceSize()
 */
PHP_METHOD(spp, getPieceSize)
{
	php_spp_object *sp_obj;
	zval *object = getThis();
	zend_long size;

	sp_obj = Z_SPP_P(object);

	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}
	size = SppGetPieceSize(sp_obj->spp);
	RETURN_LONG(size);
}
/* }}} */

/* {{{ proto int spp::pieceToId(String word)
 */
PHP_METHOD(spp, pieceToId)
{
	php_spp_object *sp_obj;
	zval *object = getThis();
	char *word;
	size_t word_len;
	zend_long id;

	sp_obj = Z_SPP_P(object);

	if (FAILURE == zend_parse_parameters_throw(ZEND_NUM_ARGS(), "s", &word, &word_len)) {
		return;
	}
	id = SppPieceToId(sp_obj->spp, (const char*)word);
	RETURN_LONG(id);
}
/* }}} */

/* {{{ proto mixed spp::idToPiece(int id)
 */
PHP_METHOD(spp, idToPiece)
{
	php_spp_object *sp_obj;
	zval *object = getThis();
	zend_long id;
	SPStr str;

	sp_obj = Z_SPP_P(object);

	if (FAILURE == zend_parse_parameters_throw(ZEND_NUM_ARGS(), "l", &id)) {
		return;
	}
	str = SppIdToPiece(sp_obj->spp, id);
	ZVAL_STRINGL(return_value, str->buff, str->len);
	SppStrFree(str);
}
/* }}} */

/* {{{ proto bool spp::isUnknown(int id)
 */
PHP_METHOD(spp, isUnknown)
{
	php_spp_object *sp_obj;
	zval *object = getThis();
	zend_long id;
	int res;

	sp_obj = Z_SPP_P(object);

	if (FAILURE == zend_parse_parameters_throw(ZEND_NUM_ARGS(), "l", &id)) {
		return;
	}
	res = SppIsUnknown(sp_obj->spp, id);
	if (res == SPP_FALSE) {
		RETURN_FALSE;
	}
	RETURN_TRUE;
}
/* }}} */

/* {{{ proto bool spp::isControl(int id)
 */
PHP_METHOD(spp, isControl)
{
	php_spp_object *sp_obj;
	zval *object = getThis();
	zend_long id;
	int res;

	sp_obj = Z_SPP_P(object);

	if (FAILURE == zend_parse_parameters_throw(ZEND_NUM_ARGS(), "l", &id)) {
		return;
	}
	res = SppIsControl(sp_obj->spp, id);
	if (res == SPP_FALSE) {
		RETURN_FALSE;
	}
	RETURN_TRUE;
}
/* }}} */

/* {{{ proto bool spp::setEncodeExtraOptions(String option)
 */
PHP_METHOD(spp, setEncodeExtraOptions)
{
	php_spp_object *sp_obj;
	zval *object = getThis();
	char *opt;
	size_t opt_len;
	int res;

	sp_obj = Z_SPP_P(object);

	if (FAILURE == zend_parse_parameters_throw(ZEND_NUM_ARGS(), "s", &opt, &opt_len)) {
		return;
	}
	res = SppSetEncodeExtraOptions(sp_obj->spp, (const char*)opt);
	if (res == SPP_FALSE) {
		RETURN_FALSE;
	}
	RETURN_TRUE;
}
/* }}} */


/* {{{ arginfo */
ZEND_BEGIN_ARG_INFO(arginfo_spp_void, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_spp_word, 0, 0, 1)
	ZEND_ARG_INFO(0, word)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_spp_id, 0, 0, 1)
	ZEND_ARG_INFO(0, id)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_spp_sample, 0, 0, 1)
	ZEND_ARG_INFO(0, word)
	ZEND_ARG_INFO(0, size)
	ZEND_ARG_INFO(0, alpha)
ZEND_END_ARG_INFO()

/* }}} */


/* {{{ php_sspp_class_methods */
static zend_function_entry php_spp_class_methods[] = {
	PHP_ME(spp, __construct,  arginfo_spp_void,   ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(spp, load,         arginfo_spp_word,   ZEND_ACC_PUBLIC)
	PHP_ME(spp, encode,       arginfo_spp_word,   ZEND_ACC_PUBLIC)
	PHP_ME(spp, wakati,       arginfo_spp_word,   ZEND_ACC_PUBLIC)
	PHP_ME(spp, sampleEncode, arginfo_spp_sample, ZEND_ACC_PUBLIC)
	PHP_ME(spp, getPieceSize, arginfo_spp_void,   ZEND_ACC_PUBLIC)
	PHP_ME(spp, pieceToId,    arginfo_spp_id,     ZEND_ACC_PUBLIC)
	PHP_ME(spp, idToPiece,    arginfo_spp_id,     ZEND_ACC_PUBLIC)
	PHP_ME(spp, isUnknown,    arginfo_spp_id,     ZEND_ACC_PUBLIC)
	PHP_ME(spp, isControl,    arginfo_spp_id,     ZEND_ACC_PUBLIC)
	PHP_ME(spp, setEncodeExtraOptions, arginfo_spp_word, ZEND_ACC_PUBLIC)

	PHP_FE_END
};
/* }}} */

static void php_spp_object_free_storage(zend_object *object) /* {{{ */
{
	php_spp_object *intern = php_spp_from_obj(object);

	if (!intern) {
		return;
	}

	if (intern->spp) {
		SppFree(intern->spp);
		intern->spp = NULL;
	}

	zend_object_std_dtor(&intern->zo);
}
/* }}} */

static zend_object *php_spp_object_new(zend_class_entry *class_type) /* {{{ */
{
	php_spp_object *intern;

	/* Allocate memory for it */
	intern = ecalloc(1, sizeof(php_spp_object) + zend_object_properties_size(class_type));

	zend_object_std_init(&intern->zo, class_type);
	object_properties_init(&intern->zo, class_type);

	intern->zo.handlers = &spp_object_handlers;

	return &intern->zo;
}
/* }}} */


/* {{{ PHP_MINIT_FUNCTION
*/
PHP_MINIT_FUNCTION(spp)
{
	zend_class_entry ce;

	memcpy(&spp_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));

	/* Register Spp Class */
	INIT_CLASS_ENTRY(ce, "Spp", php_spp_class_methods);
	ce.create_object = php_spp_object_new;
	spp_object_handlers.offset = XtOffsetOf(php_spp_object, zo);
	spp_object_handlers.clone_obj = NULL;
	spp_object_handlers.free_obj = php_spp_object_free_storage;
	php_spp_sc_entry = zend_register_internal_class(&ce);

	REGISTER_INI_ENTRIES();

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
*/
PHP_MSHUTDOWN_FUNCTION(spp)
{
	UNREGISTER_INI_ENTRIES();

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
*/
PHP_MINFO_FUNCTION(spp)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "SentencePieceProcessor support", "enabled");
	php_info_print_table_row(2, "SentencePieceProcessor module version", PHP_SPP_VERSION);
	php_info_print_table_end();

	DISPLAY_INI_ENTRIES();
}
/* }}} */

/* {{{ PHP_GINIT_FUNCTION
*/
static PHP_GINIT_FUNCTION(spp)
{
	memset(spp_globals, 0, sizeof(*spp_globals));
}
/* }}} */

/* {{{ spp_module_entry
*/
zend_module_entry spp_module_entry = {
	STANDARD_MODULE_HEADER,
	"spp",
	NULL,
	PHP_MINIT(spp),
	PHP_MSHUTDOWN(spp),
	NULL,
	NULL,
	PHP_MINFO(spp),
	PHP_SPP_VERSION,
	PHP_MODULE_GLOBALS(spp),
	PHP_GINIT(spp),
	NULL,
	NULL,
	STANDARD_MODULE_PROPERTIES_EX
};
/* }}} */

#ifdef COMPILE_DL_SPP
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif
ZEND_GET_MODULE(spp)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
