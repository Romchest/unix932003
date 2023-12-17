#!/bin/bash -e

CUR_DIR="$PWD"

E_NO_FILE=1
E_PERM_DENIED=13
E_INV_ARG=22

if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <src_file>"
    exit $E_INV_ARG
fi

SRC_FILE="$1"

if [ ! -f "$SRC_FILE" ]; then
    echo "File <$SRC_FILE> not found."
    exit $E_NO_FILE
fi

if [ ! -r "$SRC_FILE" ]; then
    echo "Permission denied for <$SRC_FILE>."
    exit $E_PERM_DENIED
fi

TMP_DIR=$(mktemp -d)

exit_handler() {
    rm -rf "$TMP_DIR"
}

trap exit_handler EXIT SIGHUP SIGINT SIGQUIT SIGPIPE SIGTERM

DST_FILE=$(grep -o "&Output: [a-zA-Z0-9_]*\.out" "$SRC_FILE" | sed 's/.*: \(.*\)/\1/')

if [ -z "$DST_FILE" ]; then
    echo "Comment '\$Output: <filename>.out' not found in source file."
    exit $E_INV_ARG
fi

cp "$SRC_FILE" "$TMP_DIR"
cd "$TMP_DIR"

case "$SRC_FILE" in
    *.cpp)
        g++ "$SRC_FILE" -o "$DST_FILE" ;;
    *.c)
        gcc "$SRC_FILE" -o "$DST_FILE" ;;
    *)
        echo "Only C++ and C source files are supported."
        exit $E_INV_ARG
esac

cd "$CUR_DIR"

# if compilation fails, script exits because of -e flag
mv "$TMP_DIR/$DST_FILE" "$CUR_DIR/$DST_FILE"
echo "Compilation output: $DST_FILE"
