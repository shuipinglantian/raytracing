#pragma once

#include <string>

#include <agz-utils/graphics_api/gl/keyboard.h>
#include <agz-utils/graphics_api/gl/mouse.h>

AGZ_GL_BEGIN

struct windowclose_event_t  { };
struct windowfocus_event_t  { bool has_focus; };
struct windowresize_event_t { int w, h; };

using windowclose_handler_t  = event::functional_receiver_t<windowclose_event_t>;
using windowfocus_handler_t  = event::functional_receiver_t<windowfocus_event_t>;
using windowresize_handler_t = event::functional_receiver_t<windowresize_event_t>;

using windowevent_manager_t = event::sender_t<
    windowclose_event_t,
    windowfocus_event_t,
    windowresize_event_t>;

struct windowdesc_t
{
    vec2i size        = { 640, 480 };
    std::string title = "opengl window";

    bool resizable  = true;
    bool fullscreen = false;
    bool vsync      = true;

    enum depth_stencil_format_t
    {
        d0s0,
        d24s8,
        d32s0
    };

    depth_stencil_format_t depth_stencil_format = d24s8;

    int multisamples = 0;

    bool imgui = true;
};

class windowt : public misc::uncopyable_t
{
public:

    explicit windowt(const windowdesc_t &desc, bool maximized = false);

    ~windowt();

    // imgui

    void new_imgui_frame();

    void render_imgui();

    // input device

    keyboard_t *get_keyboard() noexcept;

    mouse_t *get_mouse() noexcept;

    // window events

    void do_events();

    bool is_in_focus();

    void wait_for_focus();

    // close flag

    bool get_close_flag() const noexcept;

    void set_close_flag(bool flag) noexcept;

    // size

    void set_maximized();

    int get_framebuffer_width() const noexcept;

    int get_framebuffer_height() const noexcept;

    vec2i get_framebuffer_size() const noexcept;

    float get_framebuffer_w_over_h() const noexcept;

    // swap chain

    void swap_buffers();

    // vsync

    bool get_vsync() const noexcept;

    void set_vsync(bool vsync) noexcept;

    // viewport

    void use_default_viewport() const;

    // events

    AGZ_GL_DECL_EVENT_MGR_HANDLER(event_mgr_, windowclose_event_t)
    AGZ_GL_DECL_EVENT_MGR_HANDLER(event_mgr_, windowfocus_event_t)
    AGZ_GL_DECL_EVENT_MGR_HANDLER(event_mgr_, windowresize_event_t)

    // internal

    bool _imgui() const noexcept;

    void _close(bool close_flag);

    void _resize();

    void _focus(bool focus);

    void _key(keycode_t keycode, bool pressed);

    void _char(uint32_t ch);

    void _mb_down(mouse_button_t button);

    void _mb_up(mouse_button_t button);

    void _wheel_scroll(int offset);

private:

    struct impl_t;

    std::unique_ptr<impl_t> impl_;

    windowevent_manager_t event_mgr_;
};

AGZ_GL_END
