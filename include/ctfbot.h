#ifndef CTFBOT_H
#define CTFBOT_H
#include <sqlite3.h>
#include <stddef.h>
#define CTF_MAX_TEXT 256
typedef struct { sqlite3 *db; } ctf_ctx;
typedef struct { long long id; char user[64]; char kind[32]; char prompt[CTF_MAX_TEXT]; char answer_hash[65]; int points; int solved; } ctf_challenge;
int ctf_open(ctf_ctx *ctx, const char *path);
void ctf_close(ctf_ctx *ctx);
int ctf_start(ctf_ctx *ctx, const char *user, const char *kind, ctf_challenge *out);
int ctf_active(ctf_ctx *ctx, const char *user, ctf_challenge *out);
int ctf_submit(ctf_ctx *ctx, const char *user, const char *answer, int *awarded);
int ctf_reset(ctf_ctx *ctx, const char *user, const char *kind, ctf_challenge *out);
int ctf_profile(ctf_ctx *ctx, const char *user, int *score, int *solves);
int ctf_leaderboard(ctf_ctx *ctx, char *buf, size_t n);
void ctf_sha256(const char *s, char out[65]);
#endif
