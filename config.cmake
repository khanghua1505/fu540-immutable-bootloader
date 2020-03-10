################################################################################
# BASIC_CONFIG
################################################################################

################################################################################
# KEYCORE_DRIVER_CONFIG
################################################################################

# Interface configurations
#
# Note: SPI and UART will be suported later.

# set(KEYCORE_INTERFACE_UART        1)
# set(KEYCORE_INTERFACE_SPI         1)
set(KEYCORE_INTERFACE_ETHERNET    1)

if (KEYCORE_INTERFACE_UART)
    # set(KEYCORE_UART_CTRL    UART0_CTRL_ADDR)
    set(KEYCORE_UART_CTRL    UART1_CTRL_ADDR)
elseif (KEYCORE_INTERFACE_SPI)
    # set(KEYCORE_SPI_CTRL    SPI0_CTRL_ADDR)
    set(KEYCORE_SPI_CTRL    SPI0_CTRL_ADDR)
    # set(KEYCORE_SPI_CTRL    SPI0_CTRL_ADDR)
elseif (KEYCORE_INTERFACE_ETHERNET)
    # set(KEYCORE_ETHERNET_INTERNAL    1)
    set(KEYCORE_ETHERNET_W5500       1)
    
    if (KEYCORE_ETHERNET_INTERNAL)
    elseif (KEYCORE_ETHERNET_W5500)
        # set(KEYCORE_ETHER_SPI_CTRL    SPI0_CTRL_ADDR)
        set(KEYCORE_ETHER_SPI_CTRL    SPI1_CTRL_ADDR)
        # set(KEYCORE_ETHER_SPI_CTRL    SPI2_CTRL_ADDR)
        set(KEYCORE_ETHER_SPI_SS_GPIO   GPIO_CTRL_ADDR)
        set(KEYCORE_ETHER_SPI_SS_PIN    GPIO_PIN_1)
    endif()
    
    set(KEYCORE_ETHER_SOCKET             0)
    set(KEYCORE_ETHER_PORT               8080)
    set(KEYCORE_ETHER_CLIENT_IP          {10,10,10,2})
    set(KEYCORE_ETHER_SERVER_IP          {10,10,10,225})
    set(KEYCORE_ETHER_SUBNET_MASK        {255,255,255,0})
    set(KEYCORE_ETHER_DEFAULT_GATEWAY    {10,10,10,225})
    set(KEYCORE_ETHER_MAC_ADDRESS        {0xEA,0x11,0x22,0x33,0x44,0xEA})
endif()












