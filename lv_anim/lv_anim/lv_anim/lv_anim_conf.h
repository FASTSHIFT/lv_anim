#ifndef LV_ANIM_CONF_H
#define LV_ANIM_CONF_H

#include <stdint.h>
#include <stdlib.h>

#define LV_USE_ANIMATION 1

/** Type of the animated value*/
typedef int16_t lv_anim_value_t;

#define _lv_memcpy(dest,src,size)       memcpy(dest,src,size)
#define _lv_memcpy_small(dest,src,size) memcpy(dest,src,size)
#define _lv_memset_00(dest,size)        memset(dest,0,size)
#define lv_mem_free(ptr)                free(ptr)
#define lv_mem_alloc(ptr)               malloc(ptr)

#define LV_GC_ROOT(x) x
#define LV_ATTRIBUTE_FAST_MEM
#define LV_UNUSED(x) ((void) x)
#define LV_ASSERT_MEM(p) true
#define LV_LOG_TRACE(...)                                                                                              \
    {                                                                                                                  \
        ;                                                                                                              \
    }

#endif
