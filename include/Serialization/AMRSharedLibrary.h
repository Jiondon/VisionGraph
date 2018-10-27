//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#pragma once
#if defined _WIN32 || defined __CYGWIN__
  #ifdef EXPORT_AMR
    #ifdef __GNUC__
      #define AMR_PUBLIC __attribute__ ((dllexport))
    #else
      #define AMR_PUBLIC __declspec(dllexport)
    #endif
  #else
    #define AMR_PUBLIC
  #endif
  #define AMR_LOCAL
#else
  #if __GNUC__ >= 4 && defined(EXPORT_AMR)
    #define AMR_PUBLIC __attribute__ ((visibility ("default")))
    #define AMR_LOCAL  __attribute__ ((visibility ("hidden")))
  #else
    #define AMR_PUBLIC
    #define AMR_LOCAL
  #endif
#endif
