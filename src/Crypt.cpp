//#define DEBUG
#include "Crypt.hpp"
#ifdef DEBUG
	#include <bits/stdc++.h>
	#include <iostream>
#endif

/*Hash fuction
accept Identification code IC
return Mark Code*/
std::array<unsigned char,32>  hash (std::string IC)
{
    gpg_error_t err;
    int algo = GCRY_MD_NONE;
    unsigned char *h;
    gcry_md_hd_t hd;
    //std::string Rval="";
    //"GOSTR3411_CP", "STRIBOG256", "STRIBOG512"
    algo = gcry_md_map_name ("STRIBOG256");
    if (algo == GCRY_MD_NONE) {
    	fprintf(stderr, "HSM: Error init hash algo\n");
    	return {0};
    }
/*Create hash context*/
    err = gcry_md_open(&hd, algo, 0);
    if (err) {
    	fprintf (stderr, "HSM: LibGCrypt error %s\n", gcry_strerror (err));
        return {0};
    }
/*Sending IC to buffer*/
    gcry_md_write (hd, IC.data(), IC.length());
/*Retrieve hash value*/
    h  = gcry_md_read(hd, 0);
#ifdef DEBUG
    for (int i=0;i<32;i++)
    	fprintf(stderr,"%02hhx:", h[i]);
    fprintf(stderr,"\n");
#endif
    std::array<unsigned char,32> Rval;
    memcpy (Rval.data(),h,32);
/*Retrieve hash*/
    //for (i = 0; i < gcry_md_get_algo_dlen (algo); i++)
    // 	Rval.append((const char*)&h[i]);
   // Rval=(const  char *)h;
/*closing context*/
    gcry_md_reset(hd);
    gcry_md_close(hd);
    return Rval;
}
