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
#pragma once
#include "../../Character/Char.h"
#include "../../Graphics/Animation.h"
#include "../../Template/BoolPair.h"

#include <unordered_map>
#include <vector>

namespace jrc
{
    // Interface for skill effects.
    class SkillUseEffect
    {
    public:
        virtual ~SkillUseEffect() {}

        virtual void apply(Char& target) const = 0;

    protected:
        class Effect
        {
        public:
            Effect(nl::node src)
            {
                animation = src;
                z = src["z"];
            }

            void apply(Char& target) const
            {
                target.show_attack_effect(animation, z);
            }

        private:
            Animation animation;
            int8_t z;
        };
    };


    // No animation.
    class NoUseEffect : public SkillUseEffect
    {
    public:
        void apply(Char&) const override {}
    };


    // An effect which displays an animation over the character's position.
    class SingleUseEffect : public SkillUseEffect
    {
    public:
        SingleUseEffect(nl::node src);

        void apply(Char& target) const override;

    private:
        Effect effect;
    };


    // An effect which displays an animation over the character's position.
    // The effect changes based on wether the character uses a twohanded weapon.
    class TwoHUseEffect : public SkillUseEffect
    {
    public:
        TwoHUseEffect(nl::node src);

        void apply(Char& target) const override;

    private:
        BoolPair<Effect> effects;
    };


    // An effect which displays multiple animations over the character's position.
    class MultiUseEffect : public SkillUseEffect
    {
    public:
        MultiUseEffect(nl::node src);

        void apply(Char& target) const override;

    private:
        std::vector<Effect> effects;
    };


    // The animation changes with the character level.
    class ByLevelUseEffect : public SkillUseEffect
    {
    public:
        ByLevelUseEffect(nl::node src);

        void apply(Char& target) const override;

    private:
        std::map<uint16_t, Effect> effects;
    };


    // Use effect for Iron Body.
    class IronBodyUseEffect : public SkillUseEffect
    {
    public:
        void apply(Char& target) const override;
    };
}
