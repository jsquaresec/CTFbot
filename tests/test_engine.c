#include "ctfbot.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
int main(void){ctf_ctx c;assert(ctf_open(&c,":memory:")==0);char h[65];ctf_sha256("abc",h);assert(!strcmp(h,"ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad"));ctf_challenge a,b;assert(ctf_start(&c,"u1","hex",&a)==0);assert(ctf_active(&c,"u1",&b)==0);assert(a.id==b.id);assert(ctf_submit(&c,"u1","definitely-wrong",&(int){0})==1);assert(ctf_reset(&c,"u1","hex",&b)==0);assert(a.id!=b.id);int s=0,v=0;assert(ctf_profile(&c,"u1",&s,&v)==0);assert(s==0&&v==0);ctf_close(&c);puts("all engine tests passed");}
