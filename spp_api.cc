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
    sentencepiece::SentencePieceText spt;
    std::string input(word);

    spp->Encode(input, &spt);

    int idx = 0;
    std::string surface = spt.pieces(idx).surface();
    std::string wakati(surface + ' ');
    const int size = spt.pieces_size();

    for (idx = 1; idx < size-1; idx++) {
        surface = spt.pieces(idx).surface();
        wakati.append(surface + ' ');
    }
    surface = spt.pieces(idx).surface();
    wakati.append(surface + ' ');

    SPStr retval = new struct _SPStr;
    retval->len = wakati.length();
    retval->buff = new char[retval->len +1];
    strcpy(retval->buff, wakati.c_str());

    return retval;
}

/**
 * decode
 *
 * @access public
 * @param  SppHandle handle
 * @param  const char* ids
 * @return SPStr
 */
SPStr SppDecode(SppHandle handle, const char* json, size_t len)
{
    sentencepiece::SentencePieceProcessor *spp = static_cast<sentencepiece::SentencePieceProcessor*>(handle);
    std::string strjson(json, len);
    nlohmann::json parsed = nlohmann::json::parse(strjson);

    std::vector<int> ids;
    for (auto& id : parsed) {
        ids.push_back(id);
    }

    std::string text;
    spp->Decode(ids, &text);

    SPStr retval = new struct _SPStr;
    retval->len = text.length();
    retval->buff = new char[retval->len +1];
    strcpy(retval->buff, text.c_str());

    return retval;
}

/**
 * SampleEncode
 *
 * @access public
 * @param  SppHandle handle
 * @param  const char* word
 * @param  int size
 * @param  float alpha
 * @return SPStr
 */
SPStr SppSampleEncode(SppHandle handle, const char* word, int size, float alpha)
{
    sentencepiece::SentencePieceProcessor *spp = static_cast<sentencepiece::SentencePieceProcessor*>(handle);
    sentencepiece::SentencePieceText spt;
    std::string input(word);

    spp->SampleEncode(input, size, alpha, &spt);

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


SPP_API int SppGetPieceSize(SppHandle handle)
{
    sentencepiece::SentencePieceProcessor *spp = static_cast<sentencepiece::SentencePieceProcessor*>(handle);
    return spp->GetPieceSize();
}

SPP_API int SppPieceToId(SppHandle handle, const char* word)
{
    sentencepiece::SentencePieceProcessor *spp = static_cast<sentencepiece::SentencePieceProcessor*>(handle);
    std::string piece(word);
    return spp->PieceToId(piece);
}

SPP_API SPStr SppIdToPiece(SppHandle handle, int id)
{
    sentencepiece::SentencePieceProcessor *spp = static_cast<sentencepiece::SentencePieceProcessor*>(handle);
    std::string piece = spp->IdToPiece(id);

    SPStr retval = new struct _SPStr;
    retval->len = piece.length();
    retval->buff = new char[retval->len + 1];
    strcpy(retval->buff, piece.c_str());

    return retval;
}

SPP_API int SppIsUnknown(SppHandle handle, int id)
{
    sentencepiece::SentencePieceProcessor *spp = static_cast<sentencepiece::SentencePieceProcessor*>(handle);
    if (!spp->IsUnknown(id)) {
        return SPP_FALSE;
    }
    return SPP_TRUE;
}

SPP_API int SppIsControl(SppHandle handle, int id)
{
    sentencepiece::SentencePieceProcessor *spp = static_cast<sentencepiece::SentencePieceProcessor*>(handle);
    if (!spp->IsControl(id)) {
        return SPP_FALSE;
    }
    return SPP_TRUE;
}

SPP_API int SppSetEncodeExtraOptions(SppHandle handle, const char* option)
{
    sentencepiece::SentencePieceProcessor *spp = static_cast<sentencepiece::SentencePieceProcessor*>(handle);
    std::string opt(option);
    auto stat = spp->SetDecodeExtraOptions(opt);
    if (!stat.ok()) {
        return SPP_FALSE;
    }
    return SPP_TRUE;
}
