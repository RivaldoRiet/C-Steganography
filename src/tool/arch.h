//
// Created by nick on 04-12-19.
//

#ifndef SECRET_MESSAGE_ARCH_H
#define SECRET_MESSAGE_ARCH_H


namespace arch {
    enum class endian {
        little_endian,
        big_endian
    };

    endian cur_byte_order() {
        const unsigned short val
                {*reinterpret_cast<const unsigned short *>("az")};
        return val == 0x617AU ?
               endian::big_endian :
               endian::little_endian;
    }
};


#endif //SECRET_MESSAGE_ARCH_H
