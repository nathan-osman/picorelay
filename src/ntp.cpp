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

#include "lwip/dns.h"
#include "lwip/udp.h"
#include "pico/cyw43_arch.h"

#include "config.h"

static void ntpUdpRecvCallback(
    void *arg,
    struct udp_pcb *pcb,
    struct pbuf *p,
    const ip_addr_t *addr,
    u16_t port
)
{
    //...
}

static void ntpDnsFoundCallback(
    const char *name, const ip_addr_t *ipaddr, void *callback_arg
)
{
    if (ipaddr) {
        printf("Resolved to %s\n", ipaddr_ntoa(ipaddr));
    }
}

bool ntpSet()
{
    // Create the pcb
    struct udp_pcb *pcb = udp_new_ip_type(IPADDR_TYPE_ANY);
    if (!pcb) {
        printf("ERROR: failed to create pcb\n");
        return false;
    }

    // Set the callback for receiving packets
    udp_recv(pcb, ntpUdpRecvCallback, NULL);

    // Lookup the address of the NTP server
    printf("Looking up %s...\n", NTP_SERVER);
    cyw43_arch_lwip_begin();
    int err = dns_gethostbyname(NTP_SERVER, NULL, ntpDnsFoundCallback, NULL);
    cyw43_arch_lwip_end();

    return true;
}
