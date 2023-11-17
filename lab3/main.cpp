#include "parent.hpp"

int main() {

    ParentRoutine(getenv("PATH_TO_CHILD"));

    exit(EXIT_SUCCESS);
}

// PATH_TO_CHILD="/home/arnemkova/OS_labs/lab3/build/child3"