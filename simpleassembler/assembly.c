#include <ctype.h>
#include <fcntl.h>
#include <include/mySimpleComputer.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define check(amogus) else if (strcmp (cmdstr, amogus) == 0) a

#define fatal(text...)                                                        \
  printf (text);                                                              \
  fatal++;                                                                    \
  skipLine = 1;                                                               \
  continue;

int
determineCommand (int line, char *command, char *operand, int *encoded)
{
  int command_i;
  int operand_i;

  if (strcmp (command, "=") == 0)
    {
      char s;
      int c, o;
      if (sscanf (operand, "%c%02x%02x", &s, &c, &o) != 3
          || (s != '+' && s != '-'))
        {
          printf ("%3d: Unexpected symbols in cell value\n", line);
          return -1;
        }
      switch (sc_commandEncode (s == '-', c, o, encoded))
        {
        case -2:
          printf ("%3d: command field overflow\n", line);
          return -1;
        case -3:
          printf ("%3d: operand field overflow\n", line);
          return -1;
        }
      return 0;
    }

  Command *commands = sc_getCommands ();
  for (int i = 0; i < COMMANDS_COUNT_TRUNCED; i++)
    {
      if (strcmp (command, commands[i].command) != 0)
        continue;

      command_i = commands[i].code;
      if (commands[i].operandType == OPNONE)
        {
          operand_i = 0;
        }
      else
        sscanf (operand, "%x", &operand_i);

      sc_commandEncode (0, command_i, operand_i, encoded);
      return 0;
    }
  printf ("%3d: Unknown command '%s'\n", line, command);
  return -1;
}

int
translate (int line, char *lineNumber, char *command, char *operand)
{
  int linenum;
  if (sscanf (lineNumber, "%x", &linenum) != 1)
    {
      printf ("%3d: Unexpected symbols in lineId\n", line);
      return -1;
    }
  if (line - 1 != linenum)
    {
      printf ("%3d: Invalid lineId\n", line);
      return -1;
    }

  int encoded;
  if (determineCommand (line, command, operand, &encoded) != 0)
    return -1;

  int sign, cmd, opr;
  sc_commandDecode (encoded, &sign, &cmd, &opr);
  sc_memorySet (line - 1, encoded);
  printf ("%3d: %s, %s, %s  [%c%02x%02x]\n", line, lineNumber, command,
          operand, sign == 1 ? '-' : '+', cmd, opr);
  return 0;
}

int
main (int argc, char *argv[])
{

  if (argc < 3)
    {
      printf ("Usage: trans <source> -o <output>\n");
      return -1;
    }

  FILE *file = fopen (argv[1], "r");

  if (file == NULL)
    {
      printf ("Source '%s' not found.\n", argv[1]);
      return -2;
    }

  int fatal = 0;
  int skipLine = 0;

  int line = 1;
  int pos = 0;
  char c = 0;
  char lastC = 0;

  char lineNumber[3] = "";
  char command[15] = "";
  char operand[6] = "";
  int stage = 0;
  int i = 0;

  sc_memoryInit ();
  while (1)
    {
      pos++;
      lastC = c;
      c = fgetc (file);

      if (stage < 0)
        stage = -10;

      if (c == '\n' || c == EOF)
        {
          if ((*lineNumber == '\0' || *command == '\0') && !skipLine)
            {
              printf ("%3d:%d: Unexpected line break\n", line, pos);
              fatal = 1;
              skipLine = 1;
            }

          if (!skipLine)
            {

              if (line > MEMORY_SIZE)
                {
                  printf ("%3d: Program exeeds memory size.\n", line);
                  fatal = 1;
                  break;
                }

              translate (line, lineNumber, command, operand);
            }

          line++;
          skipLine = 0;
          pos = 0;
          lastC = c;
          stage = 0;
          i = 0;
          *lineNumber = '\0';
          *command = '\0';
          *operand = '\0';

          if (c == EOF)
            break;
          continue;
        }
      if (skipLine)
        continue;

      if (isblank (c))
        {
          if (!isblank (lastC))
            {
              stage++;
              i = 0;
            }
          continue;
        }

      switch (stage)
        {
        case 0:
          if (i > 1)
            {
              fatal ("%3d:%d: Unexpected symbol '%c'\n", line, pos, c);
            }
          if (c == ';')
            {
              fatal ("%3d:%d: Expected line index\n", line, pos);
            }
          lineNumber[i++] = c;
          lineNumber[i] = '\0';
          break;
        case 1:
          if (i > 7)
            {
              fatal ("%3d:%d: Unknown command\n", line, pos - 5);
            }
          if (c == ';')
            {
              fatal ("%3d:%d: Expected command\n", line, pos);
            }
          command[i++] = c;
          command[i] = '\0';
          break;
        case 2:
          if (i == 0 && c == ';')
            {
              stage = -10;
              operand[0] = '\0';
            }
          else
            {
              if (i > 5)
                {
                  fatal ("%3d:%d: Unexpected symbol '%c'\n", line, pos, c);
                }
              operand[i++] = c;
              operand[i] = '\0';
            }
          break;

        case 3:
          if (i == 0 && c == ';')
            stage = -10;
          fatal ("%3d:%d: Unexpected symbol '%c'\n", line, pos, c);
          break;
        }
    }

  fclose (file);

  if (fatal)
    return -1;

  int foputput = open (argv[2], O_WRONLY | O_CREAT);

  if (foputput == -1)
    {
      printf ("Can't open or create file '%s'.\n", argv[2]);
      return -3;
    }

  int cell = 0;
  for (int i = 0; i < MEMORY_SIZE; i++)
    {
      sc_memoryGet (i, &cell);
      write (foputput, &cell, sizeof (int));
    }

  close (foputput);
  chmod (argv[2], S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH);

  return 0;
}