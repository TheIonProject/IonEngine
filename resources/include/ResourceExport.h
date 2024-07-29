#ifndef RES_EXPORT_H
#define RES_EXPORT_H

#ifdef RES_STATIC_DEFINE
#  define RES_API
#  define RES_NO_EXPORT
#else
#  ifndef RES_API
#    ifdef RES_EXPORTS
        /* We are building this library */
#      define RES_API __declspec(dllexport)
#    else
        /* We are using this library */
#      define RES_API __declspec(dllimport)
#    endif
#  endif

#  ifndef RES_NO_EXPORT
#    define RES_NO_EXPORT
#  endif
#endif

#ifndef RES_DEPRECATED
#  define RES_DEPRECATED __declspec(deprecated)
#endif

#ifndef RES_DEPRECATED_EXPORT
#  define RES_DEPRECATED_EXPORT RES_EXPORT RES_DEPRECATED
#endif

#ifndef RES_DEPRECATED_NO_EXPORT
#  define RES_DEPRECATED_NO_EXPORT RES_NO_EXPORT RES_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef RES_NO_DEPRECATED
#    define RES_NO_DEPRECATED
#  endif
#endif

#endif /* RES_EXPORT_H */
