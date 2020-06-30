/*
 * Crypt.hpp
 *
 *  Created on: 11 июн. 2020 г.
 *      Author: saddam
 */

#ifndef CRYPT_HPP_
#define CRYPT_HPP_
//#include <bits/stdc++.h> #include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <gcrypt.h>
#include <string>
#include <array>

std::array<unsigned char,32>  hash (std::string IC);

#endif /* CRYPT_HPP_ */
