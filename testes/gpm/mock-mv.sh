#!/bin/sh
case "$1" in
    */repos/second/.index.*)
        if [ "${GPM_TEST_FAIL_INDEX:-0}" = 1 ]; then exit 1; fi ;;
    */publish)
        if [ "${GPM_TEST_CRASH:-0}" = 1 ]; then kill -KILL "$PPID"; fi
        exit 1 ;;
    */installed/teste)
        if [ "${GPM_TEST_FAIL_REMOVE:-0}" = 1 ]; then exit 1; fi
        if [ "${GPM_TEST_CRASH_REMOVE:-0}" = 1 ]; then kill -KILL "$PPID"; exit 1; fi ;;
esac
exec /usr/bin/mv "$@"
