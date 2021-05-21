//region fastio
#include <unistd.h>
// ToDo: Change buffer size. ll?
const int BUFFER_SIZE_IN = 1e7;
const int BUFFER_SIZE_OUT = 1e7;
const int int_width_out = 9; // use ll for higher vals
char input[BUFFER_SIZE_IN];
char output[BUFFER_SIZE_OUT];
int inPtr = 0;
int outPtr = 0;

inline int readInt() {
    char c;
    int o = 0;
    while (c = input[inPtr++], '0' <= c) {
        o = 10 * o + c - '0';
    }
    return o;
}

inline void writeInt(int c) {
    int e = int_width_out;
    while (c) { output[outPtr + e] = (c % 10) + '0';e--;c /= 10; }
    e++;
    while (e--) output[outPtr + e] = ' ';
    output[outPtr + int_width_out+1] = '\n';
    outPtr += int_width_out+2;
}
inline void writeInt0(int c) {
    if (c == 0) {
        output[outPtr++] = '0';
        output[outPtr++] = '\n';
        return;
    }
    writeInt(c);
}
inline void writeIntNeg(int c) {
    if (c < 0) output[outPtr++] = '-';
    writeInt0(c);
}

inline void read() { read(STDIN_FILENO, input, BUFFER_SIZE_IN); }
inline void write() { output[outPtr] = '\00';write(STDOUT_FILENO, output, outPtr); }
//endregion fastio
