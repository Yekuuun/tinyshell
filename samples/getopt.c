/**
 * A base program testing how to use getopt for command arguments parsing.
 * Link : https://www.gnu.org/software/libc/manual/html_node/Example-of-Getopt.html
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

extern int optind, optopt;
extern char* optarg;

int main(int argc, char **argv) {
    int opt;

    while ((opt = getopt(argc, argv, "ab:c")) != -1) {
        switch (opt) {
            case 'a':
                printf("Option a\n");
                break;
            case 'b':
                printf("Option b with value: %s\n", optarg);
                break;
            case 'c':
                printf("Option c\n");
                break;
            case '?':
                if (optopt == 'b' || optopt == 'c')
                    fprintf(stderr, "Option -%c requires an argument.\n", optopt);
                else if (isprint(optopt))
                    fprintf(stderr, "Unknown option '-%c'.\n", optopt);
                else
                    fprintf(stderr, "Unknown option character '\\x%x'.\n", optopt);
                return 1;
            default:
                return 1;
        }
    }

    for (int i = optind; i < argc; i++) {
        printf("Argument restant: %s\n", argv[i]);
    }

    return 0;
}
