#include "sb_variables.h"
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

int
sb_saveToFile (char *fileName)
{

  FILE *foutput = fopen (fileName, "wb+");

  if (foutput == NULL)
    {
      printf ("Can't open or create file '%s'.\n", fileName);
      return -3;
    }

  for (int i = 0; i < MEMORY_SIZE; i++)
    {
      AssemblyCommand c = assemblyProgram[i];
      if (c.command == sc_commands && c.comment == NULL)
        continue;

      if (c.isVariable)
        {
          int sign, command, operand;
          sc_commandDecode (c.operand, &sign, &command, &operand);
          fprintf (foutput, "%02x  = %c%02x%02x ; %s\n", i,
                   sign == 1 ? '-' : '+', command, operand, c.comment);
        }
      else
        {
          fprintf (foutput, "%02x %5s %02x ; %s\n", i, c.command->command,
                   c.operand, c.comment == NULL ? "" : c.comment);
        }
    }

  fclose (foutput);
  chmod (fileName, S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH);
  return 0;
}