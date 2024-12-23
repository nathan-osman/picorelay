/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2024 Nathan Osman
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#include "pico/cyw43_arch.h"

#include "config.h"

bool wlanInitialize()
{
    // Initialize the Wi-Fi hardware
    printf("Initializing Wi-Fi hardware...\n");
    if (cyw43_arch_init()) {
        printf("ERROR: failed to initialize Wi-Fi hardware\n");
        return false;
    }

    // Enable station mode
    cyw43_arch_enable_sta_mode();

    // Set the hostname
    printf("Setting hostname to \"%s\"\n", WLAN_HOSTNAME);
    netif_set_hostname(&cyw43_state.netif[0], WLAN_HOSTNAME);

    // Attempt to connect to the network
    printf("Connecting to %s...\n", WLAN_SSID);
    while (cyw43_arch_wifi_connect_timeout_ms(
        WLAN_SSID, WLAN_PSK, CYW43_AUTH_WPA2_AES_PSK, WLAN_TIMEOUT
    )) {
        printf("ERROR: failed to connect within timeout\n");
    }

    // Print the human-readable IP address
    printf(
        "Connected! Obtained IP address %s\n",
        ipaddr_ntoa(&cyw43_state.netif[0].ip_addr)
    );

    return true;
}
