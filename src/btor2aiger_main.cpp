/**
 *  Btor2Tools: A tool package for the BTOR format.
 *
 *  Copyright (c) 2019 Mathias Preiner.
 *
 *  All rights reserved.
 *
 *  This file is part of the Btor2Tools package.
 *  See LICENSE.txt for more information on using this software.
 */

#include <cassert>
#include <cstdarg>
#include <cstring>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "btor2aiger.h"


/*--------------------------------------------------------------------------*/

static void
print_usage ()
{
  std::cout << "Usage:" << std::endl;
  std::cout << "  btor2aiger [options] BTOR2_FILE\n" << std::endl;
  std::cout << "Options:" << std::endl;
  std::cout << "  -h,--help   Print this help and exit." << std::endl;
  std::cout << "  -a          Print in AIGER ascii format." << std::endl;
  std::cout << "  -i          Ignore AIGER errors." << std::endl;
  std::cout << std::endl;
}

static void
die (const char *fmt, ...)
{
  va_list ap;
  va_start (ap, fmt);
  fprintf (stderr, "error: ");
  vfprintf (stderr, fmt, ap);
  va_end (ap);
  fprintf (stderr, "\n");
  exit (EXIT_FAILURE);
}

int
main (int argc, char *argv[])
{
  FILE *infile     = 0;
  char *infilename = 0;
  bool ascii_mode  = false;
  bool ignore_error = false;

  for (int i = 1; i < argc; ++i)
  {
    if (!strcmp (argv[i], "-a"))
    {
      ascii_mode = true;
    }
    else if (!strcmp (argv[i], "-i"))
    {
      ignore_error = true;
    }
    else if (!strcmp (argv[i], "-h") || !strcmp (argv[i], "--help"))
    {
      print_usage ();
      return EXIT_SUCCESS;
    }
    else
    {
      if (infilename)
      {
        die ("Multiple input files specified.");
      }
      infilename = argv[i];
    }
  }

  if (!infilename)
  {
    die ("No BTOR2 input file specified.");
  }

  infile = fopen (infilename, "r");
  if (!infile)
  {
    die ("Cannot open BTOR2 input file.");
  }
  Btor2Model model;
  parse_btor2 (infile, model);
  fclose (infile);
  aiger *aig = generate_aiger (model, ascii_mode, ignore_error);

  aiger_write_to_file (
      aig, ascii_mode ? aiger_ascii_mode : aiger_binary_mode, stdout);

  aiger_reset (aig);

  return EXIT_SUCCESS;
}
