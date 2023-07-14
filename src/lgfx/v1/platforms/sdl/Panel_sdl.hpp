/*----------------------------------------------------------------------------/
  Lovyan GFX - Graphics library for embedded devices.

Original Source:
 https://github.com/lovyan03/LovyanGFX/

Licence:
 [FreeBSD](https://github.com/lovyan03/LovyanGFX/blob/master/license.txt)

Author:
 [lovyan03](https://twitter.com/lovyan03)

Contributors:
 [ciniml](https://github.com/ciniml)
 [mongonta0716](https://github.com/mongonta0716)
 [tobozo](https://github.com/tobozo)

Porting for SDL:
 [imliubo](https://github.com/imliubo)
/----------------------------------------------------------------------------*/
#pragma once

#include "common.hpp"
#if defined (SDL_h_)
#include "../../panel/Panel_FrameBufferBase.hpp"
#include "../../misc/range.hpp"
#include "../../Touch.hpp"

namespace lgfx
{
 inline namespace v1
 {
  struct Panel_sdl;
  struct monitor_t
  {
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_Texture* texture = nullptr;
    Panel_sdl* panel = nullptr;
    int scaling_x = 1;
    int scaling_y = 1;
    bool touched = false;
    int touch_x, touch_y;
  };
//----------------------------------------------------------------------------

  struct Touch_sdl : public ITouch
  {
    bool init(void) override { return true; }
    void wakeup(void) override {}
    void sleep(void) override {}
    bool isEnable(void) override { return true; };
    uint_fast8_t getTouchRaw(touch_point_t* tp, uint_fast8_t count) override { return 0; }
  };

//----------------------------------------------------------------------------

  struct Panel_sdl : public Panel_FrameBufferBase
  {
  public:
    Panel_sdl(void);
    virtual ~Panel_sdl(void);

    bool init(bool use_reset) override;

    color_depth_t setColorDepth(color_depth_t depth) override;

    void display(uint_fast16_t x, uint_fast16_t y, uint_fast16_t w, uint_fast16_t h) override;

    // void setInvert(bool invert) override {}

    uint_fast8_t getTouchRaw(touch_point_t* tp, uint_fast8_t count) override;

    void setWindowTitle(const char* title);
    void setScaling(uint_fast8_t scaling_x, uint_fast8_t scaling_y);

    static void sdl_event_handler(void);
    void sdl_invalidate(void) { _last_msec = 0; }

  protected:
    uint32_t _last_msec;
    const char* _window_title = "LGFX Simulator";

    void sdl_create(monitor_t * m);
    void sdl_update(void);
    static void sdl_update_handler(void);

    touch_point_t _touch_point;
    monitor_t monitor;

    void _rotate_pixelcopy(uint_fast16_t& x, uint_fast16_t& y, uint_fast16_t& w, uint_fast16_t& h, pixelcopy_t* param, uint32_t& nextx, uint32_t& nexty);
    bool initFrameBuffer(size_t width, size_t height);
    void deinitFrameBuffer(void);
  };

//----------------------------------------------------------------------------
 }
}
#endif