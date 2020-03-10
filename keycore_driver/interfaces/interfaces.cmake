if (KEYCORE_INTERFACE_UART)
    message(FATAL_ERROR "Uart will be supported later")
elseif (KEYCORE_INTERFACE_SPI)
    message(FATAL_ERROR "Spi will be supported later")
elseif (KEYCORE_INTERFACE_ETHERNET)
    configure_file(
        ${CMAKE_CURRENT_LIST_DIR}/ethernet/ether_info.c.in
        ${CMAKE_CURRENT_LIST_DIR}/ethernet/ether_info.c
    )
    set(INTERFACES_SOURCE_FILES 
            ethernet/keycore_ether.c
            ethernet/socket.c
            ethernet/w5500.c
            ethernet/wizchip_conf.c)
    set(INTERFACES_INCLUDE_DIRS
            ethernet)
    add_definitions(-DCONFIG_KEYCORE_INTERFACE_ETHERNET)
    
else()
    message(FATAL_ERROR "Only support: uart, spi or ethernet")
endif()












