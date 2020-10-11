/*
 * MIT License
 * Copyright (c) 2020 _VIFEXTech
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#include <stdio.h>
#include "lv_anim/lv_anim.h"
#include "windows.h"

/*简易进度条*/
typedef struct {
    char buf[64];
    uint16_t value;
}progress_t;

/*进度条对象*/
static progress_t progress;

static void progress_anim_test();
static void progress_set_value(progress_t* prg, uint16_t value, char c);
static void progress_anim_exec_cb(void* obj, int16_t value);
static void progress_anim_ready_cb(lv_anim_t* a);

int main()
{
    /*初始化动画库*/
    lv_anim_core_init();

    /*创建进度条动画*/
    progress_anim_test();

    while (1)
    {
        /*每20ms执行一次动画任务*/
        static uint32_t lastTime = 0;
        if (lv_tick_elaps(lastTime) >= 20)
        {
            lv_anim_task();
        }
        
        /*时间基准*/
        lv_tick_inc(1);

        Sleep(1);
    }

    return 0;
}

/**
  * @brief  进度条动画测试
  * @param  无
  * @retval 无
  */
static void progress_anim_test()
{
    lv_anim_t a;

    /* INITIALIZE AN ANIMATION
    *-----------------------*/
    lv_anim_init(&a);

    /* MANDATORY SETTINGS
     *------------------*/

     /*Set the "animator" function*/
    lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t)progress_anim_exec_cb);

    /*Set the "animator" function*/
    lv_anim_set_var(&a, &progress);

    /*Length of the animation [ms]*/
    lv_anim_set_time(&a, 1000);

    /*Set start and end values. E.g. 0, 150*/
    lv_anim_set_values(&a, 0, 1000);

    /* OPTIONAL SETTINGS
     *------------------*/

     /*Time to wait before starting the animation [ms]*/
    lv_anim_set_delay(&a, 0);

    /*Create a path*/
    lv_anim_path_t path;
    lv_anim_path_init(&path);
    lv_anim_path_set_cb(&path, lv_anim_path_ease_out);

    /*Set the path in an animation*/
    lv_anim_set_path(&a, &path);

    /*Set a callback to call when animation is ready.*/
    lv_anim_set_ready_cb(&a, progress_anim_ready_cb);

    /*Set a callback to call when animation is started (after delay).*/
    lv_anim_set_start_cb(&a, progress_anim_ready_cb);

    /*Play the animation backward too with this duration. Default is 0 (disabled) [ms]*/
    lv_anim_set_playback_time(&a, 1000);

    /*Delay before playback. Default is 0 (disabled) [ms]*/
    lv_anim_set_playback_delay(&a, 0);

    /*Number of repetitions. Default is 1.  LV_ANIM_REPEAT_INFINIT for infinite repetition*/
    lv_anim_set_repeat_count(&a, LV_ANIM_REPEAT_INFINITE);

    /*Delay before repeat. Default is 0 (disabled) [ms]*/
    lv_anim_set_repeat_delay(&a, 0);

    /* START THE ANIMATION
     *------------------*/
    lv_anim_start(&a);                             /*Start the animation*/
}

/**
  * @brief  设置进度条的数值
  * @param  value:进度条的值（0~1000）
  * @param  c:进度条填充字符
  * @retval 无
  */
static void progress_set_value(progress_t* prg, uint16_t value, char c)
{
    if (value > 1000) value = 1000;
    uint16_t pos = value * (sizeof(prg->buf) - 1) / 1000;

    memset(prg->buf, ' ', sizeof(prg->buf));

    //buf[pos] = '+';
    memset(prg->buf, c, pos);

    prg->buf[sizeof(prg->buf) - 1] = '\0';
    printf("%s\r\n", prg->buf);
}

/**
  * @brief  进度条动画回调
  * @param  obj:对象地址
  * @param  value:设置的值
  * @retval 无
  */
static void progress_anim_exec_cb(void* obj, int16_t value)
{
    progress_set_value((progress_t*)obj, value, '+');
}

/**
  * @brief  进度条动画就绪事件回调
  * @param  a:动画控制器地址
  * @retval 无
  */
static void progress_anim_ready_cb(lv_anim_t* a)
{
    //printf("anim ready cb, act_time = %d\r\n", a->act_time);
}


