#include "jpp.h"
#include "spp_api.h"

using namespace spp;

/**
 * get Juman++ version
 *
 * @access public
 * @return int
 */
int SppVersion()
{
    return SPP_VERSION;
}

/**
 * create a Spp handle
 *
 * @access public
 * @return SppHandle
 */
SppHandle SppCreate()
{
    SppHandle handle = new sentencepiece::SentencePieceProcessor;
    return handle;
}

/**
 * free a JumanPP handle
 *
 * @access public
 * @param  SppHandle handle
 * @return void
 */
void SppFree(SppHandle handle)
{
    delete static_cast<sentencepiece::SentencePieceProcessor*>(handle);
}

/**
 * free a SppStr handle
 *
 * @access public
 * @param  SppStr str
 * @return void
 */
void SppStrFree(JPStr str)
{
    if (nullptr != str->buff) {
        delete[] str->buff;
    }

    if (nullptr != str) {
        delete str;
    }
}

/**
 * load model
 *
 * @access public
 * @param  SppHandle handle
 * @param  const char* path
 * @return int
 */
int SppLoad(SppHandle handle, const char* path)
{
    sentencepiece::SentencePieceProcessor *spp = static_cast<sentencepiece::SentencePieceProcessor*>(handle);
    std::string modelpath(path);

    const auto status = spp->Load(modelpath);
    if (!status.ok()) {
        // std::cerr << status.ToString() << std::endl;
        return SPP_FALSE;
    }

    return SPP_TRUE;
}

/**
 * encode
 *
 * @access public
 * @param  SppHandle handle
 * @param  const char* word
 * @return JPStr
 */
JPStr SppEncode(SppHandle handle, const char* word)
{
    sentencepiece::SentencePieceProcessor *spp = static_cast<sentencepiece::SentencePieceProcessor*>(handle);
    std::string input(word);

    std::vector<std::string> pieces;
    spp->Encode(input, &pieces);

    nlohmann::json retj(pieces);
    std::string retstr = retj.dump();

    SPStr retval = new struct _SPStr;
    retval->len = retstr.length();
    retval->buff = new char[retval->len + 1];
    strcpy(retval->buff, retstr.c_str());

    return retval;
}
