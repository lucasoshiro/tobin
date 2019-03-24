#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

union {
    uint64_t bin;
    int64_t  val_int;
    float    val_float;
    double   val_double;
} val;

static void parse_args (int ac, char *av[]) {
    char mode = '\0';
    char *raw;
    if (ac < 2) fprintf (stderr, "Error: too few parameters\n"), exit (1);

    if (av[1][0] == '-') {
	mode = av[1][1];
	if (ac < 3) fprintf (stderr, "Error: number not specified\n"), exit (1);
	raw = av[2];
    }

    switch (mode) {
    case 'i':
	sscanf (raw, "%ld", &val.val_int);
	break;
    case 'f':
	sscanf (raw, "%f", &val.val_float);
	break;
    case 'd':
	sscanf (raw, "%lf", &val.val_double);
	break;
    default:
	fprintf (stderr, "Error: invalid option -%c\n", mode), exit (1);
    }
}

static void print_bin () {
    uint64_t b = val.bin;
    int i;

    /* Skip leading zeros */
    for (i = 0; !(b & 0x8000000000000000); i++, b <<= 1);

    for (; i < 64; i++) {
	putchar ((b & 0x8000000000000000) ? '1' : '0');
	b <<= 1;
    }

    putchar ('\n');
}

int main (int ac, char* av[]) {
    parse_args (ac, av);
    print_bin ();
    return 0;
}
