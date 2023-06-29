valgrind                                \
    --leak-check=full                   \
    --show-reachable=yes                \
    --error-limit=no                    \
    --suppressions=./ncurses.supp       \
    --gen-suppressions=all              \
    --log-file=valgrind.log ./app