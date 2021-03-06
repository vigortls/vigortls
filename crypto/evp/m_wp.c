#include <openssl/evp.h>
#include <openssl/objects.h>
#include <openssl/x509.h>
#include <openssl/whrlpool.h>

#include "evp_locl.h"

static int init(EVP_MD_CTX *ctx)
{
    return WHIRLPOOL_Init(ctx->md_data);
}

static int update(EVP_MD_CTX *ctx, const void *data, size_t count)
{
    return WHIRLPOOL_Update(ctx->md_data, data, count);
}

static int final(EVP_MD_CTX *ctx, uint8_t *md)
{
    return WHIRLPOOL_Final(md, ctx->md_data);
}

static const EVP_MD whirlpool_md = {
    .type = NID_whirlpool,
    .md_size = WHIRLPOOL_DIGEST_LENGTH,
    .init = init,
    .update = update,
    .final = final,
    .required_pkey_type = {
        0, 0, 0, 0,
    },
    .block_size = WHIRLPOOL_BBLOCK / 8,
    .ctx_size = sizeof(EVP_MD *) + sizeof(WHIRLPOOL_CTX),
};

const EVP_MD *EVP_whirlpool(void)
{
    return (&whirlpool_md);
}
