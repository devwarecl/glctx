
#ifndef __glctx_predef_hpp__
#define __glctx_predef_hpp__

#if defined(GLCTX_DYNAMIC)
#define GLCTX_API_IMPORT __declspec(dllimport)
#define GLCTX_API_EXPORT __declspec(dllexport)
#else 
#define GLCTX_API_IMPORT 
#define GLCTX_API_EXPORT 
#endif

#if defined(GLCTX_BUILD)
#define GLCTX_API GLCTX_API_EXPORT
#else 
#define GLCTX_API GLCTX_API_IMPORT
#endif

#endif
