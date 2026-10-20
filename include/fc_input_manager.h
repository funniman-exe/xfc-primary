#pragma once

namespace xfc
{
    void fc_updateControls();

    void fc_initInput();
    void fc_deinitInput();

    bool fc_checkSmartDeviceInstalled( uint8_t port );
}