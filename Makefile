# name of your application
APPLICATION = LwM2M

# If no BOARD is found in the environment, use this default:
BOARD ?= native

# This has to be the absolute path to the RIOT base directory:
RIOTBASE ?= $(CURDIR)/../..

# Comment this out to disable code in RIOT that does safety checking
# which is not needed in a production environment but helps in the
# development process:
DEVELHELP ?= 1

# Change this to 0 show compiler invocation lines by default:
QUIET ?= 1



FEATURES_REQUIRED += cpp
#USEMODULE += cpp11-compat

CXXEXFLAGS += -fno-exceptions -fno-rtti

#CXXFLAGS += -Imbed-client/source/ -Imbed-coap/source -Imbed-client-coap/source 
CFLAGS += -Imbed-client/ -Imbed-coap/mbed-coap/ -Imbed-coap/source/include/ -IUtil/Include -Imbed-trace/
CFLAGS += -Wno-missing-field-initializers -Wno-deprecated -Wno-unused-parameter
CFLAGS += -Isal-stack-nanostack-eventloop/nanostack-event-loop -Ins-hal-pal

DIRS += mbed-client/source
DIRS += mbed-coap/source
DIRS += mbed-client/mbed-client-coap/source
DIRS += mbed-client/mbed-client-riot/source
DIRS += Util
DIRS += sal-stack-nanostack-eventloop/source
DIRS += ns-hal-pal

USEMODULE += gnrc_netdev_default
USEMODULE += auto_init_gnrc_netif
USEMODULE += gnrc_udp
USEMODULE += gnrc_ipv6_default
USEMODULE += gnrc_sock
USEMODULE += sock_udp
USEMODULE += xtimer
USEMODULE += sema


USEMODULE += M2M
USEMODULE += COAP
USEMODULE += MCOAP
USEMODULE += M2MRIOT
USEMODULE += M2MUTIL
USEMODULE += M2MEventLoop
USEMODULE += M2MHAL


LINKFLAGS += "-Wl,--print-memory-usage"

include $(RIOTBASE)/Makefile.include
