//////////////////////////////////////////////////////////////////////////////
// This file is part of the Journey MMORPG client                           //
// Copyright © 2015-2016 Daniel Allendorf                                   //
//                                                                          //
// This program is free software: you can redistribute it and/or modify     //
// it under the terms of the GNU Affero General Public License as           //
// published by the Free Software Foundation, either version 3 of the       //
// License, or (at your option) any later version.                          //
//                                                                          //
// This program is distributed in the hope that it will be useful,          //
// but WITHOUT ANY WARRANTY; without even the implied warranty of           //
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the            //
// GNU Affero General Public License for more details.                      //
//                                                                          //
// You should have received a copy of the GNU Affero General Public License //
// along with this program.  If not, see <http://www.gnu.org/licenses/>.    //
//////////////////////////////////////////////////////////////////////////////
#include "Icon.h"

#include "Charset.h"

#include "nlnx/nx.hpp"

namespace jrc
{
    Icon::Icon(std::unique_ptr<Type> t, Texture tx, int16_t c)
        : type(std::move(t)), texture(tx), count(c) {

        texture.shift({ 0, 32 });
        showcount = c > -1;
        dragged = false;
    }

    Icon::Icon()
        : Icon(std::make_unique<NullType>(), {}, -1) {}

    void Icon::draw(Point<int16_t> position) const
    {
        float opacity = dragged ? 0.5f : 1.0f;
        texture.draw({ position, opacity });

        if (showcount)
        {
            static const Charset countset = { nl::nx::ui["Basic.img"]["ItemNo"], Charset::LEFT };
            int16_t tempc = dragged ? (count - 1) : count;
            std::string countstr = std::to_string(tempc);
            countset.draw(countstr, position + Point<int16_t>(0, 20));
        }
    }

    void Icon::dragdraw(Point<int16_t> cursorpos) const
    {
        if (dragged)
        {
            texture.draw({ cursorpos - cursoroffset, 0.5f });
        }
    }

    void Icon::drop_on_stage() const
    {
        type->drop_on_stage();
    }

    void Icon::drop_on_equips(Equipslot::Id eqslot) const
    {
        type->drop_on_equips(eqslot);
    }

    void Icon::drop_on_items(InventoryType::Id tab, Equipslot::Id eqslot, int16_t slot, bool equip) const
    {
        type->drop_on_items(tab, eqslot, slot, equip);
    }

    void Icon::start_drag(Point<int16_t> offset)
    {
        cursoroffset = offset;
        dragged = true;
    }

    void Icon::reset()
    {
        dragged = false;
    }

    void Icon::set_count(int16_t c)
    {
        count = c;
    }

    int16_t Icon::get_count() const
    {
        return count;
    }
}
