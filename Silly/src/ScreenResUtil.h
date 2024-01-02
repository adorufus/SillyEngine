#pragma once
#include <iostream>

#ifdef __APPLE__
#include <CoreGraphics/CoreGraphics.h>
#endif

#ifdef __WINDOWS__
#include <Windows.h>
#endif

struct Resolution {
    int width;
    int height;
};

class ScreenResUtil
{
public:
    static Resolution getScreenRes() {
        Resolution screenRes = {0, 0};

#ifdef __APPLE__

        CGDirectDisplayID displayID = kCGDirectMainDisplay;
        CGRect displayBounds = CGDisplayBounds(displayID);

        if (!CGRectIsNull(displayBounds)) {
            screenRes.width = static_cast<int>(CGRectGetWidth(displayBounds));
            screenRes.height = static_cast<int>(CGRectGetHeight(displayBounds));
        }

#endif
#ifdef __WINDOWS__
        screenRes.width = 800;
        screenRes.height = 600;
#endif // __WINDOWS__


        return screenRes;
    }
};
