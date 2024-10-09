#pragma once

class GamingLauncher
{
public:
    GamingLauncher();
    ~GamingLauncher();

    virtual void launch(void) = 0;
};
