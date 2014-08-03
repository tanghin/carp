#include <getopt.h>

#include "carp.h"
#include "carp_lexer.h"

int main (int argc, char **argv) {
  static struct option long_options[] = {
    {"version", 0, 0, 'v'},
    {"license", 0, 0, 'l'},
  };

  // flags
  carp_option opts = {0, 0, 0, 0};
  // endflags

  int c;
  int option_index = 0;
  while ((c = getopt_long(argc, argv, "vl", long_options, &option_index)) != -1) {
    int this_option_optind = optind ? optind : 1;
    switch (c) {
    case 0:
      printf("option %s", long_options[option_index].name);
      if (optarg)
	printf(" with arg %s", optarg);
      puts("");
      break;

    case 'v':
      opts.version = 1;
      break;

    case 'l':
      opts.license = 1;
      break;

    case 'w':
      opts.warranty = 1;
      break;

    case 'c':
      opts.conditions = 1;
      break;

    default:
      printf("?? getopt returned character code 0%o ??\n", c);
    }

    if (optind < argc) {
      printf("non-option argv elements: ");
      while (optind < argc)
	printf("%s ", argv[optind++]);
      puts("");
    }
  }

  if (options.version)
    carp_print_version();

  if (options.license)
    carp_print_license();

  if (options.warranty)
    carp_print_warranty();

  if (options.conditions)
    carp_print_conditions();

  /*
  char *fn = argv[1];
  if (fn == NULL) {
    fprintf(stderr, "No filename given.\n");
    exit(1);
  }

  carp_tok *tokens = carp_lex_tokenize(fn);
  if (tokens == NULL) {
    fprintf(stderr, "Something went wrong with tokenization.\n");
    exit(1);
  }

  carp_machine_state m;
  carp_lex_lex(&m, tokens);
  carp_vm_run(&m);
  carp_vm_cleanup(&m);*/

  return 0;
}

void carp_print_version () {
  printf("carp %1.1f\n", CARP_VERSION);
}

void carp_print_license () {
  puts("carp  Copyright (C) 2014  Maxwell Bernstein\
    This program comes with ABSOLUTELY NO WARRANTY; for details type `carp -w'.\
    This is free software, and you are welcome to redistribute it\
    under certain conditions; type `carp -c' for details.");
}

void carp_print_warranty () {
  puts("THERE IS NO WARRANTY FOR THE PROGRAM, TO THE EXTENT PERMITTED BY APPLICABLE LAW. EXCEPT WHEN OTHERWISE STATED IN WRITING THE COPYRIGHT HOLDERS AND/OR OTHER PARTIES PROVIDE THE PROGRAM “AS IS” WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. THE ENTIRE RISK AS TO THE QUALITY AND PERFORMANCE OF THE PROGRAM IS WITH YOU. SHOULD THE PROGRAM PROVE DEFECTIVE, YOU ASSUME THE COST OF ALL NECESSARY SERVICING, REPAIR OR CORRECTION.");
}

void carp_print_conditions () {
  puts("See LICENSE.txt or http://www.gnu.org/licenses/gpl-3.0.txt");
}