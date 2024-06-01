cmake_minimum_required(VERSION 3.1)

project(heapsapp)

include_directories(hashlink/src)

# LibHL
file(GLOB libhl
	hashlink/src/std/*.c
	hashlink/src/alloc.c
	hashlink/src/gc.c
)
list(REMOVE_ITEM libhl ${CMAKE_CURRENT_SOURCE_DIR}/hashlink/src/std/debug.c)

file(GLOB pcre
	hashlink/include/pcre/pcre2_auto_possess.c
	hashlink/include/pcre/pcre2_chartables.c
	hashlink/include/pcre/pcre2_compile.c
	hashlink/include/pcre/pcre2_config.c
	hashlink/include/pcre/pcre2_context.c
	hashlink/include/pcre/pcre2_convert.c
	hashlink/include/pcre/pcre2_dfa_match.c
	hashlink/include/pcre/pcre2_error.c
	hashlink/include/pcre/pcre2_extuni.c
	hashlink/include/pcre/pcre2_find_bracket.c
	hashlink/include/pcre/pcre2_jit_compile.c
	hashlink/include/pcre/pcre2_maketables.c
	hashlink/include/pcre/pcre2_match_data.c
	hashlink/include/pcre/pcre2_match.c
	hashlink/include/pcre/pcre2_newline.c
	hashlink/include/pcre/pcre2_ord2utf.c
	hashlink/include/pcre/pcre2_pattern_info.c
	hashlink/include/pcre/pcre2_script_run.c
	hashlink/include/pcre/pcre2_serialize.c
	hashlink/include/pcre/pcre2_string_utils.c
	hashlink/include/pcre/pcre2_study.c
	hashlink/include/pcre/pcre2_substitute.c
	hashlink/include/pcre/pcre2_substring.c
	hashlink/include/pcre/pcre2_tables.c
	hashlink/include/pcre/pcre2_ucd.c
	hashlink/include/pcre/pcre2_valid_utf.c
	hashlink/include/pcre/pcre2_xclass.c
)

file(GLOB mbedtls hashlink/libs/datachannel/include/mbedtls/library/*.c)

set (MBEDTLS_SRC 
		hashlink/libs/datachannel/libdatachannel/deps/mbedtls/library/aes.c
		hashlink/libs/datachannel/libdatachannel/deps/mbedtls/library/aesni.c
		hashlink/libs/datachannel/libdatachannel/deps/mbedtls/library/aria.c
		hashlink/libs/datachannel/libdatachannel/deps/mbedtls/library/asn1parse.c
		hashlink/libs/datachannel/libdatachannel/deps/mbedtls/library/asn1write.c
		hashlink/libs/datachannel/libdatachannel/deps/mbedtls/library/base64.c
		hashlink/libs/datachannel/libdatachannel/deps/mbedtls/library/bignum.c
		hashlink/libs/datachannel/libdatachannel/deps/mbedtls/library/camellia.c
		hashlink/libs/datachannel/libdatachannel/deps/mbedtls/library/ccm.c
		hashlink/libs/datachannel/libdatachannel/deps/mbedtls/library/chacha20.c
		hashlink/libs/datachannel/libdatachannel/deps/mbedtls/library/chachapoly.c
		hashlink/libs/datachannel/libdatachannel/deps/mbedtls/library/cipher.c
		hashlink/libs/datachannel/libdatachannel/deps/mbedtls/library/cipher_wrap.c
		hashlink/libs/datachannel/libdatachannel/deps/mbedtls/library/cmac.c
		hashlink/libs/datachannel/libdatachannel/deps/mbedtls/library/ctr_drbg.c
		hashlink/libs/datachannel/libdatachannel/deps/mbedtls/library/des.c
		hashlink/libs/datachannel/libdatachannel/deps/mbedtls/library/dhm.c
		hashlink/libs/datachannel/libdatachannel/deps/mbedtls/library/ecdh.c
		hashlink/libs/datachannel/libdatachannel/deps/mbedtls/library/ecdsa.c
		hashlink/libs/datachannel/libdatachannel/deps/mbedtls/library/ecjpake.c
		hashlink/libs/datachannel/libdatachannel/deps/mbedtls/library/ecp.c
		hashlink/libs/datachannel/libdatachannel/deps/mbedtls/library/ecp_curves.c
		hashlink/libs/datachannel/libdatachannel/deps/mbedtls/library/entropy.c
		hashlink/libs/datachannel/libdatachannel/deps/mbedtls/library/entropy_poll.c
		hashlink/libs/datachannel/libdatachannel/deps/mbedtls/library/error.c
		hashlink/libs/datachannel/libdatachannel/deps/mbedtls/library/gcm.c
		hashlink/libs/datachannel/libdatachannel/deps/mbedtls/library/hkdf.c
		hashlink/libs/datachannel/libdatachannel/deps/mbedtls/library/hmac_drbg.c
		hashlink/libs/datachannel/libdatachannel/deps/mbedtls/library/md.c
		hashlink/libs/datachannel/libdatachannel/deps/mbedtls/library/md5.c
		hashlink/libs/datachannel/libdatachannel/deps/mbedtls/library/memory_buffer_alloc.c
		hashlink/libs/datachannel/libdatachannel/deps/mbedtls/library/mps_reader.c
		hashlink/libs/datachannel/libdatachannel/deps/mbedtls/library/mps_trace.c
		hashlink/libs/datachannel/libdatachannel/deps/mbedtls/library/nist_kw.c
		hashlink/libs/datachannel/libdatachannel/deps/mbedtls/library/oid.c
		hashlink/libs/datachannel/libdatachannel/deps/mbedtls/library/padlock.c
		hashlink/libs/datachannel/libdatachannel/deps/mbedtls/library/pem.c
		hashlink/libs/datachannel/libdatachannel/deps/mbedtls/library/pk.c
		hashlink/libs/datachannel/libdatachannel/deps/mbedtls/library/pk_wrap.c
		hashlink/libs/datachannel/libdatachannel/deps/mbedtls/library/pkcs12.c
		hashlink/libs/datachannel/libdatachannel/deps/mbedtls/library/pkcs5.c
		hashlink/libs/datachannel/libdatachannel/deps/mbedtls/library/pkparse.c
		hashlink/libs/datachannel/libdatachannel/deps/mbedtls/library/pkwrite.c
		hashlink/libs/datachannel/libdatachannel/deps/mbedtls/library/platform.c
		hashlink/libs/datachannel/libdatachannel/deps/mbedtls/library/platform_util.c
		hashlink/libs/datachannel/libdatachannel/deps/mbedtls/library/poly1305.c
		hashlink/libs/datachannel/libdatachannel/deps/mbedtls/library/ripemd160.c
		hashlink/libs/datachannel/libdatachannel/deps/mbedtls/library/rsa.c
		hashlink/libs/datachannel/libdatachannel/deps/mbedtls/library/rsa_alt_helpers.c
		hashlink/libs/datachannel/libdatachannel/deps/mbedtls/library/sha1.c
		hashlink/libs/datachannel/libdatachannel/deps/mbedtls/library/sha256.c
		hashlink/libs/datachannel/libdatachannel/deps/mbedtls/library/sha512.c
		hashlink/libs/datachannel/libdatachannel/deps/mbedtls/library/threading.c
		hashlink/libs/datachannel/libdatachannel/deps/mbedtls/library/timing.c
		hashlink/libs/datachannel/libdatachannel/deps/mbedtls/library/version.c
		hashlink/libs/datachannel/libdatachannel/deps/mbedtls/library/version_features.c
		hashlink/libs/datachannel/libdatachannel/deps/mbedtls/library/x509.c
		hashlink/libs/datachannel/libdatachannel/deps/mbedtls/library/x509_create.c
		hashlink/libs/datachannel/libdatachannel/deps/mbedtls/library/x509_crl.c
		hashlink/libs/datachannel/libdatachannel/deps/mbedtls/library/x509_crt.c
		hashlink/libs/datachannel/libdatachannel/deps/mbedtls/library/x509_csr.c
		hashlink/libs/datachannel/libdatachannel/deps/mbedtls/library/x509write_crt.c
		hashlink/libs/datachannel/libdatachannel/deps/mbedtls/library/x509write_csr.c
	    hashlink/libs/datachannel/libdatachannel/deps/mbedtls/library/debug.c
		hashlink/libs/datachannel/libdatachannel/deps/mbedtls/library/net_sockets.c
		hashlink/libs/datachannel/libdatachannel/deps/mbedtls/library/ssl_cache.c
		hashlink/libs/datachannel/libdatachannel/deps/mbedtls/library/ssl_ciphersuites.c
		hashlink/libs/datachannel/libdatachannel/deps/mbedtls/library/ssl_cli.c
		hashlink/libs/datachannel/libdatachannel/deps/mbedtls/library/ssl_cookie.c
		hashlink/libs/datachannel/libdatachannel/deps/mbedtls/library/ssl_msg.c
		hashlink/libs/datachannel/libdatachannel/deps/mbedtls/library/ssl_srv.c
		hashlink/libs/datachannel/libdatachannel/deps/mbedtls/library/ssl_ticket.c
		hashlink/libs/datachannel/libdatachannel/deps/mbedtls/library/ssl_tls.c
		hashlink/libs/datachannel/libdatachannel/deps/mbedtls/library/ssl_tls13_keys.c
)

add_library(hl STATIC
	${pcre}
	${libhl}
	hashlink/src/std/sys_android.c
	hashlink/libs/ssl/ssl.c
)

set_target_properties(hl PROPERTIES COMPILE_DEFINITIONS "HAVE_CONFIG_H;PCRE2_CODE_UNIT_WIDTH=16")
target_include_directories(hl PRIVATE hashlink/include/pcre)
target_include_directories(hl PRIVATE hashlink/libs/datachannel/libdatachannel/deps/mbedtls/include)
target_link_libraries(hl MbedTLS log)

# FMT
set(TJ_LIB ${CMAKE_CURRENT_SOURCE_DIR}/libjpeg-turbo/obj/local/${ANDROID_ABI}/libjpeg-turbo.a)
add_custom_target(turbojpeg
	${ANDROID_NDK}/ndk-build APP_ABI=${ANDROID_ABI} APP_PLATFORM=${ANDROID_PLATFORM}
	NDK_PROJECT_PATH=./libjpeg-turbo
	WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
	BYPRODUCTS ${TJ_LIB}
)

file(GLOB fmt hashlink/libs/fmt/*.c)
file(GLOB png hashlink/include/png/*.c)
file(GLOB zlib hashlink/include/zlib/*.c)
file(GLOB vorbis hashlink/include/vorbis/*.c)
file(GLOB mikkt hashlink/include/mikktspace/*.c)
file(GLOB minimp3 hashlink/include/minimp3/*.c)

add_library(fmt.hdll STATIC
	${fmt}
	${png}
	${zlib}
	${vorbis}
	${mikkt}
)

add_dependencies(fmt.hdll turbojpeg)
file(GLOB tj_include libjpeg-turbo/jni/vendor/libjpeg-turbo/libjpeg-turbo-*)
target_link_libraries(fmt.hdll ${TJ_LIB})
target_compile_definitions(fmt.hdll PRIVATE PNG_ARM_NEON_OPT=0) # disable Neon support for now

target_include_directories(fmt.hdll PRIVATE
	hashlink/include/png
	hashlink/include/mikktspace
	hashlink/include/minimp3
	hashlink/include/vorbis
	hashlink/include/zlib
	${tj_include}
)

# SDL
add_subdirectory(sdl2)
file(GLOB sdl hashlink/libs/sdl/*.c)
add_library(sdl.hdll STATIC ${sdl})
target_include_directories(sdl.hdll PUBLIC sdl2/include)
target_link_libraries(sdl.hdll SDL2 SDL2main EGL GLESv3)

# OpenAL
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/openal-nativetools/CMakeLists.txt ${CMAKE_CURRENT_SOURCE_DIR}/openal-soft COPYONLY)
add_subdirectory(openal-soft)
file(GLOB openal hashlink/libs/openal/*.c)
add_library(openal.hdll STATIC ${openal})
target_include_directories(openal.hdll PUBLIC openal-soft/include)
target_link_libraries(openal.hdll OpenAL)

# UI
file(GLOB ui hashlink/libs/ui/ui_stub.c)
add_library(ui.hdll STATIC ${ui})

add_subdirectory(libuv)
file(GLOB libuv hashlink/libs/uv/*.c)
add_library(uv.hdll STATIC ${libuv})
target_include_directories(uv.hdll PUBLIC libuv/include)
target_link_libraries(uv.hdll uv)

# Datachannel
add_subdirectory("hashlink/libs/datachannel/libdatachannel")
set (DATACHANNEL_SRC
	"hashlink/libs/datachannel/src/datachannel.c"
)

add_library(datachannel.hdll STATIC ${DATACHANNEL_SRC})
target_include_directories(datachannel.hdll PRIVATE hashlink/src)
target_link_libraries(datachannel.hdll hl datachannel-static)


# Heaps Application
add_library(heapsapp SHARED out/main.c jni.c stb/glyphme.cpp)
target_include_directories(heapsapp PRIVATE out)
target_include_directories(heapsapp PRIVATE stb)
target_link_libraries(heapsapp hl sdl.hdll fmt.hdll openal.hdll ui.hdll uv.hdll datachannel.hdll)
