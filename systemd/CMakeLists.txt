
install(FILES mcrelay@.service
    DESTINATION lib/systemd/system/
)

install(FILES mcrelay@ATAKCHAT-to-192.168.1.20  mcrelay@COTSA-to-192.168.1.20
    DESTINATION /etc/mcrelay
)

