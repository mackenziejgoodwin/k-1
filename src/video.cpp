#include <stdarg.h>
 
#include "video.h"
#include "c/screen.h"
#include "c/print.h"

bool                video::initialized_ = false;

video::video(colors fg, colors bg)
    : attr_(fg, bg)
{
    if (!initialized_)
      {
        ::screen_init(static_cast<EGA_COLORS>(bg), static_cast<EGA_COLORS>(fg));
        initialized_ = true;
      }
    else
      {
        ::set_fg_color(static_cast<EGA_COLORS>(fg));
        ::set_bg_color(static_cast<EGA_COLORS>(bg));
      }
}

video::~video()
{}

void                video::set_fg(colors fg)
{
    attr_.set_fg(fg);
    ::set_fg_color(static_cast<EGA_COLORS>(fg));
}

void                video::set_bg(colors bg)
{
    attr_.set_bg(bg);
    ::set_bg_color(static_cast<EGA_COLORS>(bg));
}

void                video::set_attr(colors fg, colors bg)
{
    this->set_fg(fg);
    this->set_bg(bg);
}

void                video::set_attr(const attribute& attr)
{
    attr_ = attr;
    this->set_fg(attr_.get_fg());
    this->set_bg(attr_.get_bg());
}

video::attribute    video::save_attr() const
{
    return attr_;
}

video::colors      video::get_fg() const
{
    return attr_.get_fg();
}

video::colors      video::get_bg() const
{
    return attr_.get_bg();
}

void                video::printf(const char* fmt, ...) const
{
    va_list         ap;

    va_start(ap, fmt);
    ::vprintk(fmt, ap);
    va_end(ap);
}

video&             video::operator<<(const char* string)
{
    ::print(string);
    return *this;
}

video&              video::operator<<(char c)
{
    ::putchar(c);
    return *this;
}

video&              video::operator<<(int number)
{
    ::printk("%d", number);
    return *this;
}

video&              video::operator<<(unsigned int number)
{
    return this->operator<<(static_cast<int>(number));
}

video&              video::operator<<(const void* ptr)
{
    ::printk("%x", ptr);
    return *this;
}

video&              video::operator<<(std::termination)
{
    ::putchar('\n');
    return *this;
}

video&              video::operator<<(const video::attribute& attr)
{
    this->set_attr(attr);
    return *this;
}
