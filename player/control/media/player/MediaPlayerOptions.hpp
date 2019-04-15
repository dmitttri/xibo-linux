#pragma once

#include "control/media/MediaOptions.hpp"

struct MediaPlayerOptions : public MediaOptions
{
    enum class Mute
    {
        Disable,
        Enable
    };

    enum class Loop
    {
        Disable,
        Enable
    };

    Mute muted;
    Loop looped;
    int volume;
};
