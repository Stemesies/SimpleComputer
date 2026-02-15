#include <console/console.h>
#include <stdio.h>

void
printHelp ()
{
  printf ("f - flags managment\n");
  printf ("   |- s - set flag\n");
  printf ("   |- r - reset registers\n");
  printf ("m - memory managment\n");
  printf ("   |- p - print memory\n");
  printf ("   |- c - print memory cell\n");
  printf ("   |- b - print detailed memory cell info\n");
  printf ("   |- s - set memory cell\n");
  printf ("   |- r - reset memory\n");
  printf ("a - set accumulator\n");
  printf ("i - set incounter\n");
  printf ("h - help menu\n");
  printf ("q - quit\n");
}

int
main ()
{

  char input = ' ';

  while (1)
    {
      printf ("\033[H\033[2J\n");
      cli_printMachineStatus ();
      printf ("_______________________________________________________________"
              "_____________________\n");

      printf ("\033[5m > \033[0m");
      mScanf ("%c", &input, break);

      switch (input)
        {
        case 'f':
          cli_flagSubdir ();
          break;
        case 'm':
          cli_memorySubdir ();
          break;
        case 'a':
          cli_setAccumulator ();
          break;
        case 'i':
          cli_setIncounter ();
          break;

        case 'h':
          printHelp ();
          break;

        case 'q':
          return 0;

        default:
          printf ("Unknown command. See 'h' for help.\n");
          break;
        }

      printf ("\033[s\033[H\n");
      cli_printMachineStatus ();
      printf ("_______________________________________________________________"
              "_____________________\n");
      printf ("\033[u");

      wait ();
    }

  return 0;
}