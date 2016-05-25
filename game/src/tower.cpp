#include <iostream>

#include "game.h"

#include <ijengine/canvas.h>
#include <ijengine/engine.h>
#include <ijengine/texture.h>

#include "tower.h"

SoMTD::Tower::Tower(std::string texture_name, unsigned id, int x, int y) :
    m_id(id),
    m_x(x),
    m_y(y),
    m_start(-1),
    m_priority(0)
{
    m_texture = ijengine::resources::get_texture(texture_name);
    ijengine::event::register_listener(this);
}

SoMTD::Tower::~Tower()
{
    ijengine::event::unregister_listener(this);
}

bool
SoMTD::Tower::on_event(const ijengine::GameEvent&)
{
    return false;
}

void
SoMTD::Tower::draw_self(ijengine::Canvas *canvas, unsigned, unsigned)
{
    const int myw = 100;
    const int myh = 81;

    std::pair<int, int> p = screen_coordinates(m_x, m_y, myw, myh);
    int x_pos = p.first;
    int y_pos = p.second;
    // printf("x_pos: %d, y_pos: %d\n", x_pos, y_pos);

    // x0 = half of window width, the coeficient for the isometry
    int x0 = 1024/2;
    // canvas->draw(m_texture.get(), x_pos+x0-((m_y+m_x)*11), y_pos-(11*(m_x-m_y)));

    canvas->draw(m_texture.get(), x_pos+x0 - myw/2, -myh/2+y_pos-11*(m_y)-11*(m_x));
    // canvas->draw(m_texture.get(), x_pos + x0 - myw/2, y_pos - myh/2);
}

void
SoMTD::Tower::update_self(unsigned, unsigned)
{
}

std::pair<int, int>
SoMTD::Tower::screen_coordinates(int map_x, int map_y, int tw, int th)
{
    int xs = (map_x - map_y) * (tw / 2);
    int ys = (map_x + map_y) * (th / 2);

    return std::pair<int, int>(xs, ys);
}
