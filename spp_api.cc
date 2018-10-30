#include "spp_api.h"
#include "sentencepiece.pb.h"

/**
 * get SentencePieceProcessor version
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
 * free a SentencePieceProcessor handle
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
void SppStrFree(SPStr str)
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
 * @return SPStr
 */
SPStr SppEncode(SppHandle handle, const char* word)
{
    sentencepiece::SentencePieceProcessor *spp = static_cast<sentencepiece::SentencePieceProcessor*>(handle);
    sentencepiece::SentencePieceText spt;
    std::string input(word);

    spp->Encode(input, &spt);

    int row = 0;
    nlohmann::json retj;
    for (const auto &piece : spt.pieces()) {
        retj[row]["begin"]   = piece.begin();
        retj[row]["end"]     = piece.end();
        retj[row]["piece"]   = piece.piece();
        retj[row]["surface"] = piece.surface();
        retj[row]["id"]      = piece.id();
        row++;
    }

    std::string retstr = retj.dump();
    SPStr retval = new struct _SPStr;
    retval->len = retstr.length();
    retval->buff = new char[retval->len + 1];
    strcpy(retval->buff, retstr.c_str());

    return retval;
}

/**
 * encode
 *
 * @access public
 * @param  SppHandle handle
 * @param  const char* word
 * @return SPStr
 */
SPStr SppWakati(SppHandle handle, const char* word)
{
    sentencepiece::SentencePieceProcessor *spp = static_cast<sentencepiece::SentencePieceProcessor*>(handle);
    std::string input(word);

    std::vector<std::string> pieces;
    spp->Encode(input, &pieces);

    std::size_t idx = 0;
    std::string piece(pieces[idx].substr(3) + ' '); // (U+2581) trim
    std::size_t size = pieces.size();

    for (idx = 1; idx < size-1; idx++) {
        piece = piece + pieces[idx] + ' ';
    }
    piece = piece + pieces[idx];

    SPStr retval = new struct _SPStr;

    retval->len = piece.length();
    retval->buff = new char[retval->len +1];

    strcpy(retval->buff, piece.c_str());

    return retval;
}
