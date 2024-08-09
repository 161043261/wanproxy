cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pipe")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pipe")
if (DEFINED CMAKE_CXX_FLAGS_DEBUG)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")
else ()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")
    add_definitions(-DNDEBUG=1)
endif ()
if (UNIX AND NOT APPLE)
    set(NO_WERROR ON)
endif ()
set(WARN_FLAGS "-W -Wall")
if (NOT NO_WERROR)
    set(WARN_FLAGS "${WARN_FLAGS} -Werror")
endif ()
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${WARN_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${WARN_FLAGS} -Wno-deprecated -Wnon-virtual-dtor")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wpointer-arith -Wreturn-type -Wcast-qual -Wwrite-strings -Wshadow -Wcast-align -Wchar-subscripts -Wreorder")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated")

project(WANProxy VERSION 1.1)

set(SRCS
        common/thread/thread.cc
        common/time/time.cc
        common/timer/timer.cc
        common/buffer.cc
        common/log.cc
        common/count_filter.cc
        config/config.cc
        config/config_class.cc
        config/config_class_log_mask.cc
        config/config_object.cc
        config/config_type_int.cc
        config/config_type_log_level.cc
        config/config_type_pointer.cc
        config/config_type_string.cc
        config/config_type_proto.cc
        crypto/crypto_encryption.cc
        crypto/crypto_hash.cc
        crypto/crypto_mac.cc
        crypto/crypto_encryption_openssl.cc
        crypto/crypto_hash_openssl.cc
        crypto/crypto_mac_openssl.cc
        crypto/crypto_random_openssl.cc
        event/event_system.cc
        event/io_service.cc
        event/event_poll_epoll.cc
        http/http_protocol.cc
        io/net/tcp_server.cc
        io/net/udp_server.cc
        io/socket/socket.cc
        io/socket/unix_server.cc
        io/stream_handle.cc
        io/sink_filter.cc
        proxy/wanproxy.cc
        proxy/wanproxy_config.cc
        proxy/wanproxy_config_class_codec.cc
        proxy/wanproxy_config_class_interface.cc
        proxy/wanproxy_config_class_peer.cc
        proxy/wanproxy_config_class_proxy.cc
        proxy/wanproxy_config_type_codec.cc
        proxy/wanproxy_config_type_compressor.cc
        proxy/wanproxy_config_type_proxy_type.cc
        proxy/wanproxy_config_type_proxy_role.cc
        proxy/proxy_listener.cc
        proxy/proxy_connector.cc
        ssh/ssh_algorithm_negotiation.cc
        ssh/ssh_filter.cc
        ssh/ssh_protocol.cc
        ssh/ssh_session.cc
        ssh/ssh_compression.cc
        ssh/ssh_encryption.cc
        ssh/ssh_key_exchange.cc
        ssh/ssh_mac.cc
        ssh/ssh_server_host_key.cc
        xcodec/xcodec_encoder.cc
        xcodec/xcodec_decoder.cc
        xcodec/xcodec_filter.cc
        xcodec/cache/coss/xcodec_cache_coss.cc
        zlib/zlib_filter.cc
        # todo
)

add_library(wanproxy_library OBJECT ${SRCS})

set_target_properties(wanproxy_library PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

set(VPATH
        ${CMAKE_SOURCE_DIR}/common/thread
        ${CMAKE_SOURCE_DIR}/common/time
        ${CMAKE_SOURCE_DIR}/common/timer
        ${CMAKE_SOURCE_DIR}/common
        ${CMAKE_SOURCE_DIR}/config
        ${CMAKE_SOURCE_DIR}/crypto
        ${CMAKE_SOURCE_DIR}/event
        ${CMAKE_SOURCE_DIR}/http
        ${CMAKE_SOURCE_DIR}/io/net
        ${CMAKE_SOURCE_DIR}/io/socket
        ${CMAKE_SOURCE_DIR}/io
        ${CMAKE_SOURCE_DIR}/proxy
        ${CMAKE_SOURCE_DIR}/ssh
        ${CMAKE_SOURCE_DIR}/xcodec
        ${CMAKE_SOURCE_DIR}/xcodec/cache/coss
        ${CMAKE_SOURCE_DIR}/zlib)

set(SRCS_io_socket
        config_class_address.cc
        config_type_address_family.cc)

include_directories(${VPATH})

add_executable(wanproxy ${SRCS})

add_library()

target_link_libraries(wanproxy
        z
        pthread
        uuid
        crypto
        rt
        boost_filesystem
        boost_system)
