isEmpty($$CRYPTOPP_DIR)
{
    $$CRYPTOPP_DIR = $$PWD
}

CONFIG(shared, shared | static)
{
    #DEFINES += CRYPTOPP_DLL=__export
    DEFINES += CRYPTOPP_EXPORTS
}

HEADERS += \
    $$CRYPTOPP_DIR/3way.h \
    $$CRYPTOPP_DIR/adler32.h \
    $$CRYPTOPP_DIR/aes.h \
    $$CRYPTOPP_DIR/algebra.h \
    $$CRYPTOPP_DIR/algparam.h \
    $$CRYPTOPP_DIR/arc4.h \
    $$CRYPTOPP_DIR/argnames.h \
    $$CRYPTOPP_DIR/asn.h \
    $$CRYPTOPP_DIR/authenc.h \
    $$CRYPTOPP_DIR/base32.h \
    $$CRYPTOPP_DIR/base64.h \
    $$CRYPTOPP_DIR/basecode.h \
    $$CRYPTOPP_DIR/blowfish.h \
    $$CRYPTOPP_DIR/blumshub.h \
    $$CRYPTOPP_DIR/camellia.h \
    $$CRYPTOPP_DIR/cast.h \
    $$CRYPTOPP_DIR/cbcmac.h \
    $$CRYPTOPP_DIR/ccm.h \
    $$CRYPTOPP_DIR/channels.h \
    $$CRYPTOPP_DIR/cmac.h \
    $$CRYPTOPP_DIR/config.h \
    $$CRYPTOPP_DIR/cpu.h \
    $$CRYPTOPP_DIR/crc.h \
    $$CRYPTOPP_DIR/cryptlib.h \
    $$CRYPTOPP_DIR/default.h \
    $$CRYPTOPP_DIR/des.h \
    $$CRYPTOPP_DIR/dh.h \
    $$CRYPTOPP_DIR/dh2.h \
    $$CRYPTOPP_DIR/dll.h \
    $$CRYPTOPP_DIR/dmac.h \
    $$CRYPTOPP_DIR/dsa.h \
    $$CRYPTOPP_DIR/eax.h \
    $$CRYPTOPP_DIR/ec2n.h \
    $$CRYPTOPP_DIR/eccrypto.h \
    $$CRYPTOPP_DIR/ecp.h \
    $$CRYPTOPP_DIR/elgamal.h \
    $$CRYPTOPP_DIR/emsa2.h \
    $$CRYPTOPP_DIR/eprecomp.h \
    $$CRYPTOPP_DIR/esign.h \
    $$CRYPTOPP_DIR/factory.h \
    $$CRYPTOPP_DIR/files.h \
    $$CRYPTOPP_DIR/filters.h \
    $$CRYPTOPP_DIR/fips140.h \
    $$CRYPTOPP_DIR/fltrimpl.h \
    $$CRYPTOPP_DIR/gcm.h \
    $$CRYPTOPP_DIR/gf256.h \
    $$CRYPTOPP_DIR/gf2_32.h \
    $$CRYPTOPP_DIR/gf2n.h \
    $$CRYPTOPP_DIR/gfpcrypt.h \
    $$CRYPTOPP_DIR/gost.h \
    $$CRYPTOPP_DIR/gzip.h \
    $$CRYPTOPP_DIR/hex.h \
    $$CRYPTOPP_DIR/hmac.h \
    $$CRYPTOPP_DIR/hrtimer.h \
    $$CRYPTOPP_DIR/ida.h \
    $$CRYPTOPP_DIR/idea.h \
    $$CRYPTOPP_DIR/integer.h \
    $$CRYPTOPP_DIR/iterhash.h \
    $$CRYPTOPP_DIR/lubyrack.h \
    $$CRYPTOPP_DIR/luc.h \
    $$CRYPTOPP_DIR/mars.h \
    $$CRYPTOPP_DIR/md2.h \
    $$CRYPTOPP_DIR/md4.h \
    $$CRYPTOPP_DIR/md5.h \
    $$CRYPTOPP_DIR/mdc.h \
    $$CRYPTOPP_DIR/misc.h \
    $$CRYPTOPP_DIR/modarith.h \
    $$CRYPTOPP_DIR/modes.h \
    $$CRYPTOPP_DIR/modexppc.h \
    $$CRYPTOPP_DIR/mqueue.h \
    $$CRYPTOPP_DIR/mqv.h \
    $$CRYPTOPP_DIR/nbtheory.h \
    $$CRYPTOPP_DIR/network.h \
    $$CRYPTOPP_DIR/nr.h \
    $$CRYPTOPP_DIR/oaep.h \
    $$CRYPTOPP_DIR/oids.h \
    $$CRYPTOPP_DIR/osrng.h \
    $$CRYPTOPP_DIR/panama.h \
    $$CRYPTOPP_DIR/pch.h \
    $$CRYPTOPP_DIR/pkcspad.h \
    $$CRYPTOPP_DIR/polynomi.h \
    $$CRYPTOPP_DIR/pssr.h \
    $$CRYPTOPP_DIR/pubkey.h \
    $$CRYPTOPP_DIR/pwdbased.h \
    $$CRYPTOPP_DIR/queue.h \
    $$CRYPTOPP_DIR/rabin.h \
    $$CRYPTOPP_DIR/randpool.h \
    $$CRYPTOPP_DIR/rc2.h \
    $$CRYPTOPP_DIR/rc5.h \
    $$CRYPTOPP_DIR/rc6.h \
    $$CRYPTOPP_DIR/resource.h \
    $$CRYPTOPP_DIR/rijndael.h \
    $$CRYPTOPP_DIR/ripemd.h \
    $$CRYPTOPP_DIR/rng.h \
    $$CRYPTOPP_DIR/rsa.h \
    $$CRYPTOPP_DIR/rw.h \
    $$CRYPTOPP_DIR/safer.h \
    $$CRYPTOPP_DIR/salsa.h \
    $$CRYPTOPP_DIR/seal.h \
    $$CRYPTOPP_DIR/secblock.h \
    $$CRYPTOPP_DIR/seckey.h \
    $$CRYPTOPP_DIR/seed.h \
    $$CRYPTOPP_DIR/serpent.h \
    $$CRYPTOPP_DIR/serpentp.h \
    $$CRYPTOPP_DIR/sha.h \
    $$CRYPTOPP_DIR/sha3.h \
    $$CRYPTOPP_DIR/shacal2.h \
    $$CRYPTOPP_DIR/shark.h \
    $$CRYPTOPP_DIR/simple.h \
    $$CRYPTOPP_DIR/skipjack.h \
    $$CRYPTOPP_DIR/smartptr.h \
    $$CRYPTOPP_DIR/socketft.h \
    $$CRYPTOPP_DIR/sosemanuk.h \
    $$CRYPTOPP_DIR/square.h \
    $$CRYPTOPP_DIR/stdcpp.h \
    $$CRYPTOPP_DIR/strciphr.h \
    $$CRYPTOPP_DIR/tea.h \
    $$CRYPTOPP_DIR/tiger.h \
    $$CRYPTOPP_DIR/trdlocal.h \
    $$CRYPTOPP_DIR/trunhash.h \
    $$CRYPTOPP_DIR/twofish.h \
    $$CRYPTOPP_DIR/validate.h \
    $$CRYPTOPP_DIR/vmac.h \
    $$CRYPTOPP_DIR/wait.h \
    $$CRYPTOPP_DIR/wake.h \
    $$CRYPTOPP_DIR/whrlpool.h \
    $$CRYPTOPP_DIR/winpipes.h \
    $$CRYPTOPP_DIR/words.h \
    $$CRYPTOPP_DIR/xtr.h \
    $$CRYPTOPP_DIR/xtrcrypt.h \
    $$CRYPTOPP_DIR/zdeflate.h \
    $$CRYPTOPP_DIR/zinflate.h \
    $$CRYPTOPP_DIR/zlib.h

SOURCES += \
    $$CRYPTOPP_DIR/3way.cpp \
    $$CRYPTOPP_DIR/adler32.cpp \
    $$CRYPTOPP_DIR/algebra.cpp \
    $$CRYPTOPP_DIR/algparam.cpp \
    $$CRYPTOPP_DIR/arc4.cpp \
    $$CRYPTOPP_DIR/asn.cpp \
    $$CRYPTOPP_DIR/authenc.cpp \
    $$CRYPTOPP_DIR/base32.cpp \
    $$CRYPTOPP_DIR/base64.cpp \
    $$CRYPTOPP_DIR/basecode.cpp \
    $$CRYPTOPP_DIR/bfinit.cpp \
    $$CRYPTOPP_DIR/blowfish.cpp \
    $$CRYPTOPP_DIR/blumshub.cpp \
    $$CRYPTOPP_DIR/camellia.cpp \
    $$CRYPTOPP_DIR/cast.cpp \
    $$CRYPTOPP_DIR/casts.cpp \
    $$CRYPTOPP_DIR/cbcmac.cpp \
    $$CRYPTOPP_DIR/ccm.cpp \
    $$CRYPTOPP_DIR/channels.cpp \
    $$CRYPTOPP_DIR/cmac.cpp \
    $$CRYPTOPP_DIR/cpu.cpp \
    $$CRYPTOPP_DIR/crc.cpp \
    $$CRYPTOPP_DIR/cryptlib.cpp \
    $$CRYPTOPP_DIR/cryptlib_bds.cpp \
    $$CRYPTOPP_DIR/default.cpp \
    $$CRYPTOPP_DIR/des.cpp \
    $$CRYPTOPP_DIR/dessp.cpp \
    $$CRYPTOPP_DIR/dh.cpp \
    $$CRYPTOPP_DIR/dh2.cpp \
    $$CRYPTOPP_DIR/dll.cpp \
    $$CRYPTOPP_DIR/dsa.cpp \
    $$CRYPTOPP_DIR/eax.cpp \
    $$CRYPTOPP_DIR/ec2n.cpp \
    $$CRYPTOPP_DIR/eccrypto.cpp \
    $$CRYPTOPP_DIR/ecp.cpp \
    $$CRYPTOPP_DIR/elgamal.cpp \
    $$CRYPTOPP_DIR/emsa2.cpp \
    $$CRYPTOPP_DIR/eprecomp.cpp \
    $$CRYPTOPP_DIR/esign.cpp \
    $$CRYPTOPP_DIR/files.cpp \
    $$CRYPTOPP_DIR/filters.cpp \
    $$CRYPTOPP_DIR/fips140.cpp \
    $$CRYPTOPP_DIR/fipsalgt.cpp \
    $$CRYPTOPP_DIR/gcm.cpp \
    $$CRYPTOPP_DIR/gf256.cpp \
    $$CRYPTOPP_DIR/gf2_32.cpp \
    $$CRYPTOPP_DIR/gf2n.cpp \
    $$CRYPTOPP_DIR/gfpcrypt.cpp \
    $$CRYPTOPP_DIR/gost.cpp \
    $$CRYPTOPP_DIR/gzip.cpp \
    $$CRYPTOPP_DIR/hex.cpp \
    $$CRYPTOPP_DIR/hmac.cpp \
    $$CRYPTOPP_DIR/hrtimer.cpp \
    $$CRYPTOPP_DIR/ida.cpp \
    $$CRYPTOPP_DIR/idea.cpp \
    $$CRYPTOPP_DIR/integer.cpp \
    $$CRYPTOPP_DIR/iterhash.cpp \
    $$CRYPTOPP_DIR/luc.cpp \
    $$CRYPTOPP_DIR/mars.cpp \
    $$CRYPTOPP_DIR/marss.cpp \
    $$CRYPTOPP_DIR/md2.cpp \
    $$CRYPTOPP_DIR/md4.cpp \
    $$CRYPTOPP_DIR/md5.cpp \
    $$CRYPTOPP_DIR/misc.cpp \
    $$CRYPTOPP_DIR/modes.cpp \
    $$CRYPTOPP_DIR/mqueue.cpp \
    $$CRYPTOPP_DIR/mqv.cpp \
    $$CRYPTOPP_DIR/nbtheory.cpp \
    $$CRYPTOPP_DIR/network.cpp \
    $$CRYPTOPP_DIR/oaep.cpp \
    $$CRYPTOPP_DIR/osrng.cpp \
    $$CRYPTOPP_DIR/panama.cpp \
    $$CRYPTOPP_DIR/pch.cpp \
    $$CRYPTOPP_DIR/pkcspad.cpp \
    $$CRYPTOPP_DIR/polynomi.cpp \
    $$CRYPTOPP_DIR/pssr.cpp \
    $$CRYPTOPP_DIR/pubkey.cpp \
    $$CRYPTOPP_DIR/queue.cpp \
    $$CRYPTOPP_DIR/rabin.cpp \
    $$CRYPTOPP_DIR/randpool.cpp \
    $$CRYPTOPP_DIR/rc2.cpp \
    $$CRYPTOPP_DIR/rc5.cpp \
    $$CRYPTOPP_DIR/rc6.cpp \
    $$CRYPTOPP_DIR/rdtables.cpp \
    $$CRYPTOPP_DIR/rijndael.cpp \
    $$CRYPTOPP_DIR/ripemd.cpp \
    $$CRYPTOPP_DIR/rng.cpp \
    $$CRYPTOPP_DIR/rsa.cpp \
    $$CRYPTOPP_DIR/rw.cpp \
    $$CRYPTOPP_DIR/safer.cpp \
    $$CRYPTOPP_DIR/salsa.cpp \
    $$CRYPTOPP_DIR/seal.cpp \
    $$CRYPTOPP_DIR/seed.cpp \
    $$CRYPTOPP_DIR/serpent.cpp \
    $$CRYPTOPP_DIR/sha.cpp \
    $$CRYPTOPP_DIR/sha3.cpp \
    $$CRYPTOPP_DIR/shacal2.cpp \
    $$CRYPTOPP_DIR/shark.cpp \
    $$CRYPTOPP_DIR/sharkbox.cpp \
    $$CRYPTOPP_DIR/simple.cpp \
    $$CRYPTOPP_DIR/skipjack.cpp \
    $$CRYPTOPP_DIR/socketft.cpp \
    $$CRYPTOPP_DIR/sosemanuk.cpp \
    $$CRYPTOPP_DIR/square.cpp \
    $$CRYPTOPP_DIR/squaretb.cpp \
    $$CRYPTOPP_DIR/strciphr.cpp \
    $$CRYPTOPP_DIR/tea.cpp \
    $$CRYPTOPP_DIR/tftables.cpp \
    $$CRYPTOPP_DIR/tiger.cpp \
    $$CRYPTOPP_DIR/tigertab.cpp \
    $$CRYPTOPP_DIR/trdlocal.cpp \
    $$CRYPTOPP_DIR/twofish.cpp \
    $$CRYPTOPP_DIR/vmac.cpp \
    $$CRYPTOPP_DIR/wait.cpp \
    $$CRYPTOPP_DIR/wake.cpp \
    $$CRYPTOPP_DIR/whrlpool.cpp \
    $$CRYPTOPP_DIR/winpipes.cpp \
    $$CRYPTOPP_DIR/xtr.cpp \
    $$CRYPTOPP_DIR/xtrcrypt.cpp \
    $$CRYPTOPP_DIR/zdeflate.cpp \
    $$CRYPTOPP_DIR/zinflate.cpp \
    $$CRYPTOPP_DIR/zlib.cpp

win32 {


    LIBS += -lws2_32
}

unix:{

    HEADERS += \
        $$CRYPTOPP_DIR/ttmac.h \
        $$CRYPTOPP_DIR/algebra.cpp \
        $$CRYPTOPP_DIR/strciphr.cpp \
        $$CRYPTOPP_DIR/eprecomp.cpp \
        $$CRYPTOPP_DIR/eccrypto.cpp \
        $$CRYPTOPP_DIR/polynomi.cpp

    macx:{

    }else{

        SOURCES += \
            $$CRYPTOPP_DIR/gcm.cpp \
            $$CRYPTOPP_DIR/integer.cpp \
            $$CRYPTOPP_DIR/panama.cpp \
            $$CRYPTOPP_DIR/rijndael.cpp \
            $$CRYPTOPP_DIR/salsa.cpp \
            $$CRYPTOPP_DIR/sha.cpp \
            $$CRYPTOPP_DIR/sosemanuk.cpp \
            $$CRYPTOPP_DIR/ttmac.cpp \
            $$CRYPTOPP_DIR/wake.cpp \
            $$CRYPTOPP_DIR/whrlpool.cpp

    }
}
