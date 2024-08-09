cmake_minimum_required(VERSION 3.10)

set(PROJECT_NAME wanproxy)

project(${PROJECT_NAME})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_BUILD_TYPE Debug) # Release

if ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    add_compile_options(           -O2 -Wno-deprecated -Wnon-virtual-dtor -include common/common.h -pipe -O2 -W -Wall -Wno-system-headers -Wno-unused-parameter -Wno-switch -Wpointer-arith -Wreturn-type -Wcast-qual -Wwrite-strings -Wshadow -Wcast-align -Wchar-subscripts -Wreorder)
else ()
    add_compile_options(-DNDEBUG=1 -O0 -Wno-deprecated -Wnon-virtual-dtor -include common/common.h -pipe -O0 -W -Wall -Wno-system-headers -Wno-unused-parameter -Wno-switch -Wpointer-arith -Wreturn-type -Wcast-qual -Wwrite-strings -Wshadow -Wcast-align -Wchar-subscripts -Wreorder)
endif ()

if(NOT CMAKE_SYSTEM_NAME STREQUAL "Linux")
    add_compile_options(-Werror)
endif()

include_directories(${CMAKE_SOURCE_DIR})
set(SOURCES
        proxy/wanproxy.cc
        common/buffer.cc
        config/config.cc
        config/config_class.cc
        config/config_class_address.cc
        config/config_class_log_mask.cc
        config/config_object.cc
        config/config_type_address_family.cc
        config/config_type_int.cc
        config/config_type_log_level.cc
        config/config_type_pointer.cc
        config/config_type_proto.cc
        config/config_type_string.cc
        common/count_filter.cc
        crypto/crypto_encryption.cc
        crypto/crypto_encryption_openssl.cc
        crypto/crypto_hash.cc
        crypto/crypto_hash_openssl.cc
        crypto/crypto_mac.cc
        crypto/crypto_mac_openssl.cc
        crypto/crypto_random_openssl.cc
        event/event_poll_epoll.cc
        event/event_system.cc
        http/http_protocol.cc
        event/io_service.cc
        common/log.cc
        proxy/proxy_connector.cc
        proxy/proxy_listener.cc
        io/sink_filter.cc
        io/socket/socket.cc
        ssh/ssh_algorithm_negotiation.cc
        ssh/ssh_compression.cc
        ssh/ssh_encryption.cc
        ssh/ssh_filter.cc
        ssh/ssh_key_exchange.cc
        ssh/ssh_mac.cc
        ssh/ssh_protocol.cc
        ssh/ssh_server_host_key.cc
        ssh/ssh_session.cc
        io/stream_handle.cc
        io/net/tcp_server.cc
        common/thread/thread.cc
        common/time/time.cc
        io/net/udp_server.cc
        io/socket/unix_server.cc
        common/uuid/uuid.cc
        proxy/wanproxy_config.cc
        proxy/wanproxy_config_class_codec.cc
        proxy/wanproxy_config_class_interface.cc
        proxy/wanproxy_config_class_peer.cc
        proxy/wanproxy_config_class_proxy.cc
        proxy/wanproxy_config_type_codec.cc
        proxy/wanproxy_config_type_compressor.cc
        proxy/wanproxy_config_type_proxy_role.cc
        proxy/wanproxy_config_type_proxy_type.cc
        xcodec/cache/coss/xcodec_cache_coss.cc
        xcodec/xcodec_decoder.cc
        xcodec/xcodec_encoder.cc
        xcodec/xcodec_filter.cc
        zlib/zlib_filter.cc
)
add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} pthread uuid crypto rt z)